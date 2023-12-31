#===================================================================================================== PROJECT SETUP ===
cmake_minimum_required(VERSION 3.19)
cmake_policy(SET CMP0110 NEW)
project(tardigrade_hydra)

# Set common project paths relative to project root directory
set(CPP_SRC_PATH "src/cpp")
set(CPP_TEST_PATH "${CPP_SRC_PATH}/tests")
set(CMAKE_SRC_PATH "src/cmake")
set(ABAQUS_SRC_PATH "src/abaqus")
set(ABAQUS_TEST_PATH "${ABAQUS_SRC_PATH}/tests")
set(DOXYGEN_SRC_PATH "docs/doxygen")
set(SPHINX_SRC_PATH "docs/sphinx")
# Set the internal support libraries
set(INTERNAL_SUPPORT_LIBRARIES "tardigrade_hydraLinearElasticity" "tardigrade_hydraLinearViscoelasticity" "tardigrade_hydraThermalExpansion" "tardigrade_hydraPeryznaViscoplasticity")
set(PROJECT_SOURCE_FILES ${PROJECT_NAME}.cpp ${PROJECT_NAME}.h)
set(PROJECT_PRIVATE_HEADERS "")
foreach(package ${INTERNAL_SUPPORT_LIBRARIES})
    set(PROJECT_SOURCE_FILES ${PROJECT_SOURCE_FILES} ${package}.cpp ${package}.h)
    set(PROJECT_PRIVATE_HEADERS ${PROJECT_PRIVATE_HEADERS} ${package}.h)
endforeach(package)
set(TARDIGRADE-HYDRALINEARELASTICITY_UPSTREAM_LIBRARIES "tardigrade_constitutive_tools")
set(TARDIGRADE-HYDRALINEARVISCOELASTICITY_UPSTREAM_LIBRARIES "tardigrade_constitutive_tools" "tardigrade_stress_tools")
set(TARDIGRADE-HYDRATHERMALEXPANSION_UPSTREAM_LIBRARIES "tardigrade_constitutive_tools")
set(TARDIGRADE-HYDRAPERYZNAVISCOPLASTICITY_UPSTREAM_LIBRARIES "tardigrade_constitutive_tools" "tardigrade_stress_tools")
# Set some Abaqus integration variables
set(UMAT "${PROJECT_NAME}_umat")
set(MISSING_INTEGRATION_DEPS_MESSAGE "Abaqus integration tests will be skipped.")

# Add the cmake folder to locate project CMake module(s)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/${CMAKE_SRC_PATH}" ${CMAKE_MODULE_PATH})

# Set build type checks
string(TOLOWER "${CMAKE_BUILD_TYPE}" cmake_build_type_lower)
set(upstream_required "")
set(not_conda_test "true")
if(cmake_build_type_lower STREQUAL "release")
    set(upstream_required "REQUIRED")
elseif(cmake_build_type_lower STREQUAL "conda-test")
    set(upstream_required "REQUIRED")
    set(not_conda_test "false")
    # Find the installed project umat
    find_file(installed_umat
              "${UMAT}.o"
              PATHS "$ENV{CONDA_PREFIX}/lib64" "$ENV{CONDA_PREFIX}/lib"
              NO_CACHE
              REQUIRED)
endif()

# Get version number from Git
if(${not_conda_test} STREQUAL "true")
    find_package(Python COMPONENTS Interpreter REQUIRED)
    execute_process(COMMAND ${Python_EXECUTABLE} -m setuptools_scm
                            OUTPUT_VARIABLE ${PROJECT_NAME}_VERSION_STRING_FULL
                    OUTPUT_STRIP_TRAILING_WHITESPACE)
    if(${${PROJECT_NAME}_VERSION_STRING_FULL} STREQUAL "")
        set(${PROJECT_NAME}_VERSION 0.0.0)
    else()
         string(REGEX MATCH "[0-9]+\.[0-9]+\.[0-9]+" ${PROJECT_NAME}_VERSION ${${PROJECT_NAME}_VERSION_STRING_FULL})
    endif()
    project(${PROJECT_NAME} VERSION ${${PROJECT_NAME}_VERSION})
endif()

# Add installation directory variables
include(GNUInstallDirs)

# Make the code position independent
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Set the c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lrt")
endif()

# Enable CTest
enable_testing()

#================================================================================================= FIND DEPENDENCIES ===
# Find eigen
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
include_directories(${EIGEN3_INCLUDE_DIR})
if(EIGEN3_FOUND)
    message(STATUS "Found Eigen3: ${EIGEN3_INCLUDE_DIR}")
endif()

# Find bash (Required for abaqus integration tests)
find_program(BASH_PROGRAM bash)
if(BASH_PROGRAM)
    message(STATUS "Found bash: ${BASH_PROGRAM}")
else()
    message(STATUS "bash not found. ${MISSING_INTEGRATION_DEPS_MESSAGE}")
endif()

# Find Abaqus (Required for abaqus integration tests)
find_program(ABAQUS_PROGRAM
             NAMES abaqus abq2022 abq2021 abq2020 abq2019 abq2018 abq2017
             # AEA path, HPC path
             HINTS /apps/abaqus/Commands /usr/projects/ea/abaqus/Commands
            )
if(ABAQUS_PROGRAM)
    message(STATUS "Found Abaqus: ${ABAQUS_PROGRAM}")
else()
    message(STATUS "Abaqus not found. ${MISSING_INTEGRATION_DEPS_MESSAGE}")
endif()

# Find related, but external, projects in installed environment
include(FetchContent)
set(upstream_packages "tardigrade_error_tools" "tardigrade_vector_tools" "tardigrade_constitutive_tools" "tardigrade_stress_tools" "tardigrade_abaqus_tools")
if(${not_conda_test} STREQUAL "false")
    # During conda-build testing, we must find the installed project files as if they were an external project
    set(upstream_packages ${upstream_packages} ${PROJECT_NAME})
endif()
foreach(package ${upstream_packages})
    string(TOUPPER "${package}" package_upper)
    find_package(${package} ${upstream_required} CONFIG)
    if(${package}_FOUND)
        message(STATUS "Found ${package}: ${${package}_DIR}")
    else()
        # Find related, but external, projects using FetchContent and building locally
        message(WARNING "Did not find an installed ${package} package. Attempting local build with FetchContent.")
        # TODO: Decide how to handle main/dev build differences. bash env variables for GIT TAG?
        FetchContent_Declare(
            ${package}
            GIT_REPOSITORY ssh://git@re-git.lanl.gov:10022/aea/material-models/${package}.git
            GIT_TAG        origin/dev
        )
        FetchContent_MakeAvailable(${package})
    endif()
endforeach(package)

#=============================================================================================== ADD PROJECT TARGETS ===
# MUST COME AFTER DEPENDENCY LOCATING
# Add project source directories
if(${not_conda_test} STREQUAL "true")
    include_directories(${CPP_SRC_PATH})
    add_subdirectory(${CPP_SRC_PATH})
endif()

# Only add tests and documentation for current project builds. Protects downstream project builds.
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # Find Boost. Required for tests
    find_package(Boost 1.53.0 REQUIRED COMPONENTS unit_test_framework)
    # Add c++ tests and docs
    add_subdirectory(${CPP_TEST_PATH})
    add_subdirectory(${ABAQUS_SRC_PATH})
    if(${not_conda_test} STREQUAL "true")
        add_subdirectory(${DOXYGEN_SRC_PATH})
        add_subdirectory(${SPHINX_SRC_PATH})
    endif()
endif()

#==================================================================================== SETUP INSTALLATION CMAKE FILES ===
if(${not_conda_test} STREQUAL "true")
    foreach(package ${PROJECT_NAME} ${UMAT})
        include(CMakePackageConfigHelpers)
        write_basic_package_version_file("${package}ConfigVersion.cmake"
                                         VERSION ${PROJECT_VERSION}
                                         COMPATIBILITY SameMajorVersion)
        configure_package_config_file(
          "${PROJECT_SOURCE_DIR}/${CMAKE_SRC_PATH}/Config.cmake.in"
          "${PROJECT_BINARY_DIR}/${package}Config.cmake"
          INSTALL_DESTINATION
          ${CMAKE_INSTALL_DATAROOTDIR}/${package}/cmake)

        # CMake won't build the targets for local builds of upstream projects
        if(cmake_build_type_lower STREQUAL release)
            install(EXPORT ${package}_Targets
                    FILE ${package}Targets.cmake
                    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${package}/cmake)
        endif()

        install(FILES "${PROJECT_BINARY_DIR}/${package}Config.cmake"
                      "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
                DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${package}/cmake)
    endforeach(package)
endif()
