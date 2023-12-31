/**
  * \file test_tardigrade-hydraLinearViscoelasticity.cpp
  * 
  * Tests for tardigrade-hydraLinearViscoelasticity
  */

#include<tardigrade_hydraLinearViscoelasticity.h>

#define BOOST_TEST_MODULE test_tardigrade-hydraLinearViscoelasticity
#include <boost/test/included/unit_test.hpp>
#include <boost/test/tools/output_test_stream.hpp>
#include<tardigrade_stress_tools.h>

typedef tardigradeErrorTools::Node errorNode; //!< Redefinition for the error node
typedef errorNode* errorOut; //!< Redefinition for a pointer to the error node
typedef tardigradeHydra::linearElasticity::floatType floatType; //!< Redefinition of the floating point type
typedef tardigradeHydra::linearElasticity::floatVector floatVector; //!< Redefinition of the vector of floating points type
typedef tardigradeHydra::linearElasticity::floatMatrix floatMatrix; //!< Redefinition of the matrix of floating points type

namespace tardigradeHydra{

    namespace unit_test{

        class hydraBaseTester{

            public:

                static void updateUnknownVector( tardigradeHydra::hydraBase &hydra, const floatVector &value ){

                    BOOST_CHECK_NO_THROW( hydra.updateUnknownVector( value ) );

                }

        };

    }

    namespace linearViscoelasticity{

        namespace unit_test{
    
            class residualTester{
    
                public:
    
                    static void runBasicGetTests( tardigradeHydra::linearViscoelasticity::residual &R ){

                        BOOST_CHECK( &R._viscoelasticISVLowerIndex == R.getViscoelasticISVLowerIndex( ) );

                        BOOST_CHECK( &R._viscoelasticISVUpperIndex == R.getViscoelasticISVUpperIndex( ) );

                        BOOST_CHECK( &R._numVolumetricViscousTerms == R.getNumVolumetricViscousTerms( ) );

                        BOOST_CHECK( &R._numIsochoricViscousTerms == R.getNumIsochoricViscousTerms( ) );

                        BOOST_CHECK( &R._Kinf == R.getKinf( ) );
    
                        BOOST_CHECK( &R._Ginf == R.getGinf( ) );
    
                        BOOST_CHECK( &R._Ks == R.getVolumetricModuli( ) );

                        BOOST_CHECK( &R._Gs == R.getIsochoricModuli( ) );

                        BOOST_CHECK( &R._volumetricTaus == R.getVolumetricTaus( ) );

                        BOOST_CHECK( &R._isochoricTaus == R.getIsochoricTaus( ) );

                        BOOST_CHECK( &R._Je.second == R.getJe( ) );

                        BOOST_CHECK( &R._Fehat.second == R.getFehat( ) );
    
                        BOOST_CHECK( &R._previousJe.second == R.getPreviousJe( ) );

                        BOOST_CHECK( &R._previousFehat.second == R.getPreviousFehat( ) );

                        BOOST_CHECK( &R._numStateVariables == R.getNumStateVariables( ) );

                        BOOST_CHECK( &R._volumetricTemperatureParameters == R.getVolumetricTemperatureParameters( ) );

                        BOOST_CHECK( &R._isochoricTemperatureParameters == R.getIsochoricTemperatureParameters( ) );

                        BOOST_CHECK( &R._volumetricRateMultiplier.second == R.getVolumetricRateMultiplier( ) );

                        BOOST_CHECK( &R._previousVolumetricRateMultiplier.second == R.getPreviousVolumetricRateMultiplier( ) );

                        BOOST_CHECK( &R._isochoricRateMultiplier.second == R.getIsochoricRateMultiplier( ) );

                        BOOST_CHECK( &R._previousIsochoricRateMultiplier.second == R.getPreviousIsochoricRateMultiplier( ) );

                        BOOST_CHECK( &R._dVolumetricRateMultiplierdT.second == R.getdVolumetricRateMultiplierdT( ) );

                        BOOST_CHECK( &R._dPreviousVolumetricRateMultiplierdPreviousT.second == R.getdPreviousVolumetricRateMultiplierdPreviousT( ) );

                        BOOST_CHECK( &R._dIsochoricRateMultiplierdT.second == R.getdIsochoricRateMultiplierdT( ) );

                        BOOST_CHECK( &R._dPreviousIsochoricRateMultiplierdPreviousT.second == R.getdPreviousIsochoricRateMultiplierdPreviousT( ) );

                        BOOST_CHECK( &R._integrationAlpha == R.getIntegrationAlpha( ) );

                        BOOST_CHECK( &R._PK2MeanStress.second == R.getPK2MeanStress( ) );

                        BOOST_CHECK( &R._PK2IsochoricStress.second == R.getPK2IsochoricStress( ) );

                        BOOST_CHECK( &R._dPK2MeanStressdFe.second == R.getdPK2MeanStressdFe( ) );

                        BOOST_CHECK( &R._dPK2MeanStressdT.second == R.getdPK2MeanStressdT( ) );

                        BOOST_CHECK( &R._dPK2IsochoricStressdFe.second == R.getdPK2IsochoricStressdFe( ) );

                        BOOST_CHECK( &R._dPK2IsochoricStressdT.second == R.getdPK2IsochoricStressdT( ) );

                        BOOST_CHECK( &R._dCauchyStressdT.second == R.getdCauchyStressdT( ) );

                        BOOST_CHECK( &R._volumetricViscoelasticStateVariables.second == R.getUpdatedVolumetricViscoelasticStateVariables( ) );

                        BOOST_CHECK( &R._isochoricViscoelasticStateVariables.second == R.getUpdatedIsochoricViscoelasticStateVariables( ) );

                    }
    
            };
    
        }

    }

}

BOOST_AUTO_TEST_CASE( test_residual_runBasicGetTests_and_decomposeParameters ){

    class hydraBaseMock : public tardigradeHydra::hydraBase {

        public:

            using tardigradeHydra::hydraBase::hydraBase;

        private:

            virtual void setResidualClasses( ){ }

    };

    floatType time = 1.1;

    floatType deltaTime = 2.2;

    floatType temperature = 5.3;

    floatType previousTemperature = 23.4;

    floatVector deformationGradient = { 0.39293837, -0.42772133, -0.54629709,
                                        0.10262954,  0.43893794, -0.15378708,
                                        0.9615284 ,  0.36965948, -0.0381362 };

    floatVector previousDeformationGradient = { -0.21576496, -0.31364397,  0.45809941,
                                                -0.12285551, -0.88064421, -0.20391149,
                                                 0.47599081, -0.63501654, -0.64909649 };

    floatVector previousStateVariables( 2 + 31, 0 );

    floatVector parameters = { 2, 3, 123.4, 56.7, 1, 2, 293.15, 3, 4, 293.15, 23.4, 25.6, 0.1, 0.2, 12.3, 13.4, 14.5, 0.01, 10.0, 100.0 };

    unsigned int numConfigurations = 1;

    unsigned int numNonLinearSolveStateVariables = 0;

    unsigned int dimension = 3;

    unsigned int ISVlb = 2;

    unsigned int ISVub = 31;

    unsigned int numVolumetricViscousTermsAnswer = 2;

    unsigned int numIsochoricViscousTermsAnswer = 3;

    floatType KinfAnswer = 123.4;

    floatType GinfAnswer = 56.7;

    floatVector volTAnswer = { 1, 2, 293.15 };

    floatVector isoTAnswer = { 3, 4, 293.15 };

    floatVector Ks = { 23.4, 25.6 };

    floatVector KTaus = { 0.1, 0.2 };

    floatVector Gs = { 12.3, 13.4, 14.5 };

    floatVector GTaus = { 0.01, 10.0, 100.0 };

    hydraBaseMock hydra( time, deltaTime, temperature, previousTemperature, deformationGradient, previousDeformationGradient,
                         previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

    tardigradeHydra::linearViscoelasticity::residual R( &hydra, 9, parameters, ISVlb, ISVub );

    BOOST_CHECK_NO_THROW( tardigradeHydra::linearViscoelasticity::unit_test::residualTester::runBasicGetTests( R ) );

    BOOST_CHECK( tardigradeVectorTools::fuzzyEquals( ISVlb, *R.getViscoelasticISVLowerIndex( ) ) );

    BOOST_CHECK( tardigradeVectorTools::fuzzyEquals( ISVub, *R.getViscoelasticISVUpperIndex( ) ) );

    BOOST_CHECK( tardigradeVectorTools::fuzzyEquals( numVolumetricViscousTermsAnswer, *R.getNumVolumetricViscousTerms( ) ) );

    BOOST_CHECK( tardigradeVectorTools::fuzzyEquals( numIsochoricViscousTermsAnswer, *R.getNumIsochoricViscousTerms( ) ) );

    BOOST_CHECK( tardigradeVectorTools::fuzzyEquals( KinfAnswer, *R.getKinf( ) ) );

    BOOST_CHECK( tardigradeVectorTools::fuzzyEquals( GinfAnswer, *R.getGinf( ) ) );

    BOOST_CHECK( tardigradeVectorTools::fuzzyEquals( Ks, *R.getVolumetricModuli( ) ) );

    BOOST_CHECK( tardigradeVectorTools::fuzzyEquals( Gs, *R.getIsochoricModuli( ) ) );

    BOOST_CHECK( tardigradeVectorTools::fuzzyEquals( KTaus, *R.getVolumetricTaus( ) ) );

    BOOST_CHECK( tardigradeVectorTools::fuzzyEquals( GTaus, *R.getIsochoricTaus( ) ) );

    BOOST_CHECK( tardigradeVectorTools::fuzzyEquals( volTAnswer, *R.getVolumetricTemperatureParameters( ) ) );

    BOOST_CHECK( tardigradeVectorTools::fuzzyEquals( isoTAnswer, *R.getIsochoricTemperatureParameters( ) ) );

}

BOOST_AUTO_TEST_CASE( test_residual_decomposeElasticDeformation ){

    class hydraBaseMock : public tardigradeHydra::hydraBase {

        public:

            using tardigradeHydra::hydraBase::hydraBase;

        private:

            virtual void setResidualClasses( ){ }

    };

    floatType time = 1.1;

    floatType deltaTime = 2.2;

    floatType temperature = 5.3;

    floatType previousTemperature = 23.4;

    floatVector deformationGradient = { 0.39293837, -0.42772133, -0.54629709,
                                        0.10262954,  0.43893794, -0.15378708,
                                        0.9615284 ,  0.36965948, -0.0381362 };

    floatVector previousDeformationGradient = { -0.21576496, -0.31364397,  0.45809941,
                                                -0.12285551, -0.88064421, -0.20391149,
                                                 0.47599081, -0.63501654, -0.64909649 };

    floatVector previousStateVariables = { };

    floatVector parameters = { 2, 3, 123.4, 56.7, 1, 2, 293.15, 3, 4, 293.15, 23.4, 25.6, 0.1, 0.2, 12.3, 13.4, 14.5, 0.01, 10.0, 100.0 };

    unsigned int numConfigurations = 1;

    unsigned int numNonLinearSolveStateVariables = 0;

    unsigned int dimension = 3;

    unsigned int ISVlb = 2;

    unsigned int ISVub = 31;

    floatType JeAnswer = 0.2871738879785901;

    floatVector FehatAnswer = { 0.59558368, -0.64830483, -0.82803222,
                                0.15555742,  0.66530605, -0.23309781,
                                1.45740571,  0.56029945, -0.05780372 };

    hydraBaseMock hydra( time, deltaTime, temperature, previousTemperature, deformationGradient, previousDeformationGradient,
                         previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

    tardigradeHydra::linearViscoelasticity::residual R1( &hydra, 9, parameters, ISVlb, ISVub );

    tardigradeHydra::linearViscoelasticity::residual R2( &hydra, 9, parameters, ISVlb, ISVub );

    TARDIGRADE_ERROR_TOOLS_CATCH( tardigradeVectorTools::fuzzyEquals( JeAnswer, *R1.getJe( ) ) );

    TARDIGRADE_ERROR_TOOLS_CATCH( tardigradeVectorTools::fuzzyEquals( FehatAnswer, *R2.getFehat( ) ) );

}

BOOST_AUTO_TEST_CASE( test_residual_decomposePreviousElasticDeformation ){

    class hydraBaseMock : public tardigradeHydra::hydraBase {

        public:

            using tardigradeHydra::hydraBase::hydraBase;

        private:

            virtual void setResidualClasses( ){ }

    };

    floatType time = 1.1;

    floatType deltaTime = 2.2;

    floatType temperature = 5.3;

    floatType previousTemperature = 23.4;

    floatVector deformationGradient = { 0.39293837, -0.42772133, -0.54629709,
                                        0.10262954,  0.43893794, -0.15378708,
                                        0.9615284 ,  0.36965948, -0.0381362 };

    floatVector previousDeformationGradient = { -0.21576496, -0.31364397,  0.45809941,
                                                -0.12285551, -0.88064421, -0.20391149,
                                                 0.47599081, -0.63501654, -0.64909649 };

    floatVector previousStateVariables = { };

    floatVector parameters = { 2, 3, 123.4, 56.7, 1, 2, 293.15, 3, 4, 293.15, 23.4, 25.6, 0.1, 0.2, 12.3, 13.4, 14.5, 0.01, 10.0, 100.0 };

    unsigned int numConfigurations = 1;

    unsigned int numNonLinearSolveStateVariables = 0;

    unsigned int dimension = 3;

    unsigned int ISVlb = 2;

    unsigned int ISVub = 31;

    floatType JeAnswer = 0.1878206127090311;

    floatVector FehatAnswer = { -0.37676148, -0.54767451,  0.79991771,
                                -0.21452614, -1.53775117, -0.35606336,
                                 0.83115907, -1.10884443, -1.13343036 };

    hydraBaseMock hydra( time, deltaTime, temperature, previousTemperature, deformationGradient, previousDeformationGradient,
                         previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

    tardigradeHydra::linearViscoelasticity::residual R1( &hydra, 9, parameters, ISVlb, ISVub );

    tardigradeHydra::linearViscoelasticity::residual R2( &hydra, 9, parameters, ISVlb, ISVub );

    TARDIGRADE_ERROR_TOOLS_CATCH( tardigradeVectorTools::fuzzyEquals( JeAnswer, *R1.getPreviousJe( ) ) );

    TARDIGRADE_ERROR_TOOLS_CATCH( tardigradeVectorTools::fuzzyEquals( FehatAnswer, *R2.getPreviousFehat( ) ) );

}

BOOST_AUTO_TEST_CASE( test_residual_gradientsOfDecomposedElasticDeformationGradient ){

    class hydraBaseMock : public tardigradeHydra::hydraBase {

        public:

            using tardigradeHydra::hydraBase::hydraBase;

        private:

            virtual void setResidualClasses( ){ }

    };

    floatType time = 1.1;

    floatType deltaTime = 2.2;

    floatType temperature = 5.3;

    floatType previousTemperature = 23.4;

    floatVector deformationGradient = { 0.39293837, -0.42772133, -0.54629709,
                                        0.10262954,  0.43893794, -0.15378708,
                                        0.9615284 ,  0.36965948, -0.0381362 };

    floatVector previousDeformationGradient = { -0.21576496, -0.31364397,  0.45809941,
                                                -0.12285551, -0.88064421, -0.20391149,
                                                 0.47599081, -0.63501654, -0.64909649 };

    floatVector previousStateVariables = { };

    floatVector parameters = { 2, 3, 123.4, 56.7, 1, 2, 293.15, 3, 4, 293.15, 23.4, 25.6, 0.1, 0.2, 12.3, 13.4, 14.5, 0.01, 10.0, 100.0 };

    unsigned int numConfigurations = 1;

    unsigned int numNonLinearSolveStateVariables = 0;

    unsigned int dimension = 3;

    unsigned int ISVlb = 2;

    unsigned int ISVub = 31;

    hydraBaseMock hydra( time, deltaTime, temperature, previousTemperature, deformationGradient, previousDeformationGradient,
                         previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

    tardigradeHydra::linearViscoelasticity::residual R( &hydra, 9, parameters, ISVlb, ISVub );

    floatVector gradientJe( deformationGradient.size( ), 0 );

    floatMatrix gradientFehat( deformationGradient.size( ), floatVector( deformationGradient.size( ), 0 ) );

    floatType eps = 1e-6;

    for ( unsigned int i = 0; i < deformationGradient.size( ); i++ ){

        floatVector delta( deformationGradient.size( ), 0 );

        delta[ i ] = eps * std::fabs( deformationGradient[ i ] ) + eps;

        hydraBaseMock hydrap( time, deltaTime, temperature, previousTemperature, deformationGradient + delta, previousDeformationGradient,
                             previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

        hydraBaseMock hydram( time, deltaTime, temperature, previousTemperature, deformationGradient - delta, previousDeformationGradient,
                             previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );
    
        tardigradeHydra::linearViscoelasticity::residual Rp( &hydrap, 9, parameters, ISVlb, ISVub );

        tardigradeHydra::linearViscoelasticity::residual Rm( &hydram, 9, parameters, ISVlb, ISVub );

        for ( unsigned int j = 0; j < 1; j++ ){

            gradientJe[ i ] = ( ( *Rp.getJe( ) ) - ( *Rm.getJe( ) ) ) / ( 2 * delta[ i ] );

        }

        for ( unsigned int j = 0; j < deformationGradient.size( ); j++ ){

            gradientFehat[ j ][ i ] = ( ( *Rp.getFehat( ) )[ j ] - ( *Rm.getFehat( ) )[ j ] ) / ( 2 * delta[ i ] );

        }

    }

    BOOST_CHECK( tardigradeVectorTools::fuzzyEquals( gradientJe, *R.getdJedFe( ) ) );

    BOOST_CHECK( tardigradeVectorTools::fuzzyEquals( gradientFehat, *R.getdFehatdFe( ) ) );

}

BOOST_AUTO_TEST_CASE( test_residual_decomposeStateVariableVector ){

    class hydraBaseMock : public tardigradeHydra::hydraBase {

        public:

            using tardigradeHydra::hydraBase::hydraBase;

        private:

            virtual void setResidualClasses( ){ }

    };

    floatType time = 1.1;

    floatType deltaTime = 2.2;

    floatType temperature = 5.3;

    floatType previousTemperature = 23.4;

    floatVector deformationGradient = { 0.39293837, -0.42772133, -0.54629709,
                                        0.10262954,  0.43893794, -0.15378708,
                                        0.9615284 ,  0.36965948, -0.0381362 };

    floatVector previousDeformationGradient = { -0.21576496, -0.31364397,  0.45809941,
                                                -0.12285551, -0.88064421, -0.20391149,
                                                 0.47599081, -0.63501654, -0.64909649 };

    floatVector previousStateVariables = { -1, 0, 1, 2,
                                            3,  4,  5,  6,  7,  8,  9, 10, 11,
                                           12, 13, 14, 15, 16, 17, 18, 19, 20,
                                           21, 22, 23, 24, 25, 26, 27, 28, 29 };

    floatVector volumetricStateVariablesAnswer = { 1, 2 };

    floatVector isochoricStateVariablesAnswer = {  3,  4,  5,  6,  7,  8,  9, 10, 11,
                                                  12, 13, 14, 15, 16, 17, 18, 19, 20,
                                                  21, 22, 23, 24, 25, 26, 27, 28, 29 };

    floatVector parameters = { 2, 3, 123.4, 56.7, 1, 2, 293.15, 3, 4, 293.15, 23.4, 25.6, 0.1, 0.2, 12.3, 13.4, 14.5, 0.01, 10.0, 100.0 };

    unsigned int numConfigurations = 1;

    unsigned int numNonLinearSolveStateVariables = 0;

    unsigned int dimension = 3;

    unsigned int ISVlb = 2;

    unsigned int ISVub = 31;

    hydraBaseMock hydra( time, deltaTime, temperature, previousTemperature, deformationGradient, previousDeformationGradient,
                         previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

    tardigradeHydra::linearViscoelasticity::residual R( &hydra, 9, parameters, ISVlb, ISVub );

    floatVector volumetricStateVariables, isochoricStateVariables;

    BOOST_CHECK_NO_THROW( R.decomposeStateVariableVector( volumetricStateVariables,
                                                          isochoricStateVariables ) );

    TARDIGRADE_ERROR_TOOLS_CATCH( tardigradeVectorTools::fuzzyEquals( volumetricStateVariables,
                                                 volumetricStateVariablesAnswer ) );

    TARDIGRADE_ERROR_TOOLS_CATCH( tardigradeVectorTools::fuzzyEquals( isochoricStateVariables,
                                                 isochoricStateVariablesAnswer ) );

}

BOOST_AUTO_TEST_CASE( test_residual_setRateMultipliers ){

    class hydraBaseMock : public tardigradeHydra::hydraBase {

        public:

            using tardigradeHydra::hydraBase::hydraBase;

        private:

            virtual void setResidualClasses( ){ }

    };

    floatType time = 1.1;

    floatType deltaTime = 2.2;

    floatType temperature = 300.0;

    floatType previousTemperature = 310.4;

    floatVector deformationGradient = { 0.39293837, -0.42772133, -0.54629709,
                                        0.10262954,  0.43893794, -0.15378708,
                                        0.9615284 ,  0.36965948, -0.0381362 };

    floatVector previousDeformationGradient = { -0.21576496, -0.31364397,  0.45809941,
                                                -0.12285551, -0.88064421, -0.20391149,
                                                 0.47599081, -0.63501654, -0.64909649 };

    floatVector previousStateVariables = { -1, 0, 1, 2,
                                            3,  4,  5,  6,  7,  8,  9, 10, 11,
                                           12, 13, 14, 15, 16, 17, 18, 19, 20,
                                           21, 22, 23, 24, 25, 26, 27, 28, 29 };

    floatVector parameters = { 2, 3, 123.4, 56.7, 1, 100, 293.15, 2, 110, 293.15, 23.4, 25.6, 0.1, 0.2, 12.3, 13.4, 14.5, 0.01, 10.0, 100.0 };

    unsigned int numConfigurations = 1;

    unsigned int numNonLinearSolveStateVariables = 0;

    unsigned int dimension = 3;

    unsigned int ISVlb = 2;

    unsigned int ISVub = 31;

    floatType volumetricRateMultiplierAnswer = 7.457812578748434;

    floatType previousVolumetricRateMultiplierAnswer = 8.814658257473116;

    floatType isochoricRateMultiplierAnswer = 35.32015484464411;

    floatType previousIsochoricRateMultiplierAnswer = 61.973752329639055;

    hydraBaseMock hydra( time, deltaTime, temperature, previousTemperature, deformationGradient, previousDeformationGradient,
                         previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

    tardigradeHydra::linearViscoelasticity::residual R( &hydra, 9, parameters, ISVlb, ISVub );

    TARDIGRADE_ERROR_TOOLS_CATCH( tardigradeVectorTools::fuzzyEquals( volumetricRateMultiplierAnswer, *R.getVolumetricRateMultiplier( ) ) )

    TARDIGRADE_ERROR_TOOLS_CATCH( tardigradeVectorTools::fuzzyEquals( previousVolumetricRateMultiplierAnswer, *R.getPreviousVolumetricRateMultiplier( ) ) )

    TARDIGRADE_ERROR_TOOLS_CATCH( tardigradeVectorTools::fuzzyEquals( isochoricRateMultiplierAnswer, *R.getIsochoricRateMultiplier( ) ) )

    TARDIGRADE_ERROR_TOOLS_CATCH( tardigradeVectorTools::fuzzyEquals( previousIsochoricRateMultiplierAnswer, *R.getPreviousIsochoricRateMultiplier( ) ) )

}

BOOST_AUTO_TEST_CASE( test_residual_setdRateMultipliersdT ){

    class hydraBaseMock : public tardigradeHydra::hydraBase {

        public:

            using tardigradeHydra::hydraBase::hydraBase;

        private:

            virtual void setResidualClasses( ){ }

    };

    floatType time = 1.1;

    floatType deltaTime = 2.2;

    floatType temperature = 300.0;

    floatType previousTemperature = 310.4;

    floatVector deformationGradient = { 0.39293837, -0.42772133, -0.54629709,
                                        0.10262954,  0.43893794, -0.15378708,
                                        0.9615284 ,  0.36965948, -0.0381362 };

    floatVector previousDeformationGradient = { -0.21576496, -0.31364397,  0.45809941,
                                                -0.12285551, -0.88064421, -0.20391149,
                                                 0.47599081, -0.63501654, -0.64909649 };

    floatVector previousStateVariables = { -1, 0, 1, 2,
                                            3,  4,  5,  6,  7,  8,  9, 10, 11,
                                           12, 13, 14, 15, 16, 17, 18, 19, 20,
                                           21, 22, 23, 24, 25, 26, 27, 28, 29 };

    floatVector parameters = { 2, 3, 123.4, 56.7, 10, 5, 293.15, 2, 3, 293.15, 23.4, 25.6, 0.1, 0.2, 12.3, 13.4, 14.5, 0.01, 10.0, 100.0 };

    unsigned int numConfigurations = 1;

    unsigned int numNonLinearSolveStateVariables = 0;

    unsigned int dimension = 3;

    unsigned int ISVlb = 2;

    unsigned int ISVub = 31;

    floatType dVolumetricRateMultiplierdT = 0;

    floatType dPreviousVolumetricRateMultiplierdPreviousT = 0;

    floatType dIsochoricRateMultiplierdT = 0;

    floatType dPreviousIsochoricRateMultiplierdPreviousT = 0;

    hydraBaseMock hydra( time, deltaTime, temperature, previousTemperature, deformationGradient, previousDeformationGradient,
                         previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

    tardigradeHydra::linearViscoelasticity::residual R( &hydra, 9, parameters, ISVlb, ISVub );

    floatType eps = 1e-6;

    for ( unsigned int i = 0; i < 1; i++ ){

         floatVector deltas( 1, 0 );

        deltas[ i ] = eps * std::fabs( temperature ) + eps;

        hydraBaseMock hydrap( time, deltaTime, temperature + deltas[ 0 ], previousTemperature, deformationGradient, previousDeformationGradient,
                              previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

        hydraBaseMock hydram( time, deltaTime, temperature - deltas[ 0 ], previousTemperature, deformationGradient, previousDeformationGradient,
                              previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

    tardigradeHydra::linearViscoelasticity::residual Rp( &hydrap, 9, parameters, ISVlb, ISVub );

    tardigradeHydra::linearViscoelasticity::residual Rm( &hydram, 9, parameters, ISVlb, ISVub );

        dVolumetricRateMultiplierdT = ( *Rp.getVolumetricRateMultiplier( ) - *Rm.getVolumetricRateMultiplier( ) ) / ( 2 * deltas[ i ] );

        dIsochoricRateMultiplierdT = ( *Rp.getIsochoricRateMultiplier( ) - *Rm.getIsochoricRateMultiplier( ) ) / ( 2 * deltas[ i ] );

    }

    for ( unsigned int i = 0; i < 1; i++ ){

        floatVector deltas( 1, 0 );

        deltas[ i ] = eps * std::fabs( previousTemperature ) + eps;

        hydraBaseMock hydrap( time, deltaTime, temperature, previousTemperature + deltas[ 0 ], deformationGradient, previousDeformationGradient,
                              previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

        hydraBaseMock hydram( time, deltaTime, temperature, previousTemperature - deltas[ 0 ], deformationGradient, previousDeformationGradient,
                              previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

    tardigradeHydra::linearViscoelasticity::residual Rp( &hydrap, 9, parameters, ISVlb, ISVub );

    tardigradeHydra::linearViscoelasticity::residual Rm( &hydram, 9, parameters, ISVlb, ISVub );

        dPreviousVolumetricRateMultiplierdPreviousT = ( *Rp.getPreviousVolumetricRateMultiplier( ) - *Rm.getPreviousVolumetricRateMultiplier( ) ) / ( 2 * deltas[ i ] );

        dPreviousIsochoricRateMultiplierdPreviousT = ( *Rp.getPreviousIsochoricRateMultiplier( ) - *Rm.getPreviousIsochoricRateMultiplier( ) ) / ( 2 * deltas[ i ] );

    }

    TARDIGRADE_ERROR_TOOLS_CATCH( tardigradeVectorTools::fuzzyEquals( dVolumetricRateMultiplierdT, *R.getdVolumetricRateMultiplierdT( ) ) )

    TARDIGRADE_ERROR_TOOLS_CATCH( tardigradeVectorTools::fuzzyEquals( dPreviousVolumetricRateMultiplierdPreviousT, *R.getdPreviousVolumetricRateMultiplierdPreviousT( ) ) )

    TARDIGRADE_ERROR_TOOLS_CATCH( tardigradeVectorTools::fuzzyEquals( dIsochoricRateMultiplierdT, *R.getdIsochoricRateMultiplierdT( ) ) )

    TARDIGRADE_ERROR_TOOLS_CATCH( tardigradeVectorTools::fuzzyEquals( dPreviousIsochoricRateMultiplierdPreviousT, *R.getdPreviousIsochoricRateMultiplierdPreviousT( ) ) )

}

BOOST_AUTO_TEST_CASE( test_residual_getViscoelasticParameters ){

    class hydraBaseMock : public tardigradeHydra::hydraBase {

        public:

            using tardigradeHydra::hydraBase::hydraBase;

        private:

            virtual void setResidualClasses( ){ }

    };

    floatType time = 1.1;

    floatType deltaTime = 2.2;

    floatType temperature = 300.0;

    floatType previousTemperature = 310.4;

    floatVector deformationGradient = { 0.39293837, -0.42772133, -0.54629709,
                                        0.10262954,  0.43893794, -0.15378708,
                                        0.9615284 ,  0.36965948, -0.0381362 };

    floatVector previousDeformationGradient = { -0.21576496, -0.31364397,  0.45809941,
                                                -0.12285551, -0.88064421, -0.20391149,
                                                 0.47599081, -0.63501654, -0.64909649 };

    floatVector previousStateVariables = { -1, 0, 1, 2,
                                            3,  4,  5,  6,  7,  8,  9, 10, 11,
                                           12, 13, 14, 15, 16, 17, 18, 19, 20,
                                           21, 22, 23, 24, 25, 26, 27, 28, 29 };

    floatVector parameters = { 2, 3, 123.4, 56.7, 1, 100, 293.15, 2, 110, 293.15, 23.4, 25.6, 0.1, 0.2, 12.3, 13.4, 14.5, 0.01, 10.0, 100.0 };

    unsigned int numConfigurations = 1;

    unsigned int numNonLinearSolveStateVariables = 0;

    unsigned int dimension = 3;

    unsigned int ISVlb = 2;

    unsigned int ISVub = 31;

    floatVector volumetricViscoelasticParametersAnswer = { 123.4, 0.1, 0.2, 23.4, 25.6 };

    floatVector isochoricViscoelasticParametersAnswer = { 113.4, 0.01, 10.0, 100, 24.6, 26.8, 29.0 };

    hydraBaseMock hydra( time, deltaTime, temperature, previousTemperature, deformationGradient, previousDeformationGradient,
                         previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

    tardigradeHydra::linearViscoelasticity::residual R( &hydra, 9, parameters, ISVlb, ISVub );

    BOOST_CHECK( tardigradeVectorTools::fuzzyEquals( volumetricViscoelasticParametersAnswer, R.getVolumetricViscoelasticParameters( ) ) );

    BOOST_CHECK( tardigradeVectorTools::fuzzyEquals( isochoricViscoelasticParametersAnswer, R.getIsochoricViscoelasticParameters( ) ) );

}

BOOST_AUTO_TEST_CASE( test_residual_setPK2MeanStress ){

    class residualMock : public tardigradeHydra::linearViscoelasticity::residual {

        public:

            floatVector stateVariables = { 0.001, 0.002 };

            floatType Je = 1.1;

            using tardigradeHydra::linearViscoelasticity::residual::residual;

            void setJe( const floatType &Je ){

                tardigradeHydra::linearViscoelasticity::residual::setJe( Je );

            }

            void decomposeStateVariableVector( floatVector &volumetricISVs,
                                               floatVector &isochoricISVs ){

                volumetricISVs = stateVariables;

            }

        private:

            virtual void decomposeElasticDeformation( ) override {

                setJe( Je );

            }

    };

    class hydraBaseMock : public tardigradeHydra::hydraBase {

        public:

            using tardigradeHydra::hydraBase::hydraBase;

        private:

            virtual void setResidualClasses( ){ }

    };

    floatType time = 1.1;

    floatType deltaTime = 2.2;

    floatType temperature = 300.0;

    floatType previousTemperature = 320.4;

    floatVector deformationGradient = { 1.1, 0.0, 0.0,
                                        0.0, 1.0, 0.0,
                                        0.0, 0.0, 1.0 };

    floatVector previousDeformationGradient = { 1.0, 0.0, 0.0,
                                                0.0, 1.0, 0.0,
                                                0.0, 0.0, 1.0 };

    floatVector previousStateVariables = { -1, 0, 1e-3, 1e-1,
                                            3,  4,  5,  6,  7,  8,  9, 10, 11,
                                           12, 13, 14, 15, 16, 17, 18, 19, 20,
                                           21, 22, 23, 24, 25, 26, 27, 28, 29 };

    floatVector parameters = { 2, 3, 123.4, 56.7, 10.0, 5.0, 293.15, 2, 110, 293.15, 23.4, 25.6, 0.1, 0.2, 12.3, 13.4, 14.5, 0.01, 10.0, 100.0 };

    unsigned int numConfigurations = 1;

    unsigned int numNonLinearSolveStateVariables = 0;

    unsigned int dimension = 3;

    unsigned int ISVlb = 2;

    unsigned int ISVub = 31;

    floatType currentRateModifier;
    tardigradeConstitutiveTools::WLF( temperature, { parameters[ 4 ], parameters[ 5 ], 293.15 }, currentRateModifier );
    currentRateModifier = 1. / currentRateModifier;

    floatType previousRateModifier;
    tardigradeConstitutiveTools::WLF( previousTemperature, { parameters[ 4 ], parameters[ 5 ], 293.15 }, previousRateModifier );
    previousRateModifier = 1. / previousRateModifier;

    floatVector ISVs = { 1e-3, 2e-3 };
    floatVector params = { 123.4, 0.1, 0.2, 23.4, 25.6 };
    floatVector PK2MeanStressAnswer;
    floatVector updatedISVsAnswer;

    BOOST_CHECK( !tardigradeStressTools::linearViscoelasticity( 1.1, { 0.1 }, -1.1, { 0.0 }, currentRateModifier, previousRateModifier, ISVs, params, 0.5, PK2MeanStressAnswer, updatedISVsAnswer ) );

    hydraBaseMock hydra( time, deltaTime, temperature, previousTemperature, deformationGradient, previousDeformationGradient,
                         previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

    residualMock R( &hydra, 9, parameters, ISVlb, ISVub, 0.5 );

    BOOST_CHECK( tardigradeVectorTools::fuzzyEquals( PK2MeanStressAnswer[ 0 ], *R.getPK2MeanStress( ) ) );

    BOOST_CHECK( tardigradeVectorTools::fuzzyEquals( updatedISVsAnswer, *R.getUpdatedVolumetricViscoelasticStateVariables( ) ) );

}

BOOST_AUTO_TEST_CASE( test_residual_setPK2MeanStressDerivatives ){

    class residualMock : public tardigradeHydra::linearViscoelasticity::residual {

        public:

            using tardigradeHydra::linearViscoelasticity::residual::residual;

    };

    class hydraBaseMock : public tardigradeHydra::hydraBase {

        public:

            using tardigradeHydra::hydraBase::hydraBase;

        private:

            virtual void setResidualClasses( ){ }

    };

    floatType time = 1.1;

    floatType deltaTime = 2.2;

    floatType temperature = 300.0;

    floatType previousTemperature = 320.4;

    floatVector deformationGradient = { 1.1, 0.0, 0.0,
                                        0.0, 1.0, 0.0,
                                        0.0, 0.0, 1.0 };

    floatVector previousDeformationGradient = { 1.0, 0.0, 0.0,
                                                0.0, 1.0, 0.0,
                                                0.0, 0.0, 1.0 };

    floatVector previousStateVariables = { -1, 0, 1e-3, 2e-3,
                                            3,  4,  5,  6,  7,  8,  9, 10, 11,
                                           12, 13, 14, 15, 16, 17, 18, 19, 20,
                                           21, 22, 23, 24, 25, 26, 27, 28, 29 };

    floatVector parameters = { 2, 3, 123.4, 56.7, 10.0, 5.0, 293.15, 2, 110, 293.15, 23.4, 25.6, 0.1, 0.2, 12.3, 13.4, 14.5, 0.01, 10.0, 100.0 };

    unsigned int numConfigurations = 1;

    unsigned int numNonLinearSolveStateVariables = 0;

    unsigned int dimension = 3;

    unsigned int ISVlb = 2;

    unsigned int ISVub = 31;

    hydraBaseMock hydra( time, deltaTime, temperature, previousTemperature, deformationGradient, previousDeformationGradient,
                         previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

    residualMock R( &hydra, 9, parameters, ISVlb, ISVub, 0.5 );

    floatType eps = 1e-6;

    floatVector dPK2MeanStressdFe( deformationGradient.size( ), 0 );

    floatType dPK2MeanStressdT;

    for ( unsigned int i = 0; i < deformationGradient.size( ); i++ ){

        floatVector deltas( deformationGradient.size( ), 0 );

        deltas[ i ] = eps * std::fabs( deformationGradient[ i ] ) + eps;

        hydraBaseMock hydrap( time, deltaTime, temperature, previousTemperature, deformationGradient + deltas, previousDeformationGradient,
                             previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

        residualMock Rp( &hydrap, 9, parameters, ISVlb, ISVub, 0.5 );

        hydraBaseMock hydram( time, deltaTime, temperature, previousTemperature, deformationGradient - deltas, previousDeformationGradient,
                             previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

        residualMock Rm( &hydram, 9, parameters, ISVlb, ISVub, 0.5 );

        for ( unsigned int j = 0; j < 1; j++ ){

            dPK2MeanStressdFe[ i ] = ( ( *Rp.getPK2MeanStress( ) ) - ( *Rm.getPK2MeanStress( ) ) ) / ( 2 * deltas[ i ] );

        }

    }

    for ( unsigned int i = 0; i < 1; i++ ){

        floatVector deltas( 1, 0 );

        deltas[ i ] = eps * std::fabs( temperature ) + eps;

        hydraBaseMock hydrap( time, deltaTime, temperature + deltas[ 0 ], previousTemperature, deformationGradient, previousDeformationGradient,
                             previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

        residualMock Rp( &hydrap, 9, parameters, ISVlb, ISVub, 0.5 );

        hydraBaseMock hydram( time, deltaTime, temperature - deltas[ 0 ], previousTemperature, deformationGradient, previousDeformationGradient,
                             previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

        residualMock Rm( &hydram, 9, parameters, ISVlb, ISVub, 0.5 );

        for ( unsigned int j = 0; j < 1; j++ ){

            dPK2MeanStressdT = ( ( *Rp.getPK2MeanStress( ) ) - ( *Rm.getPK2MeanStress( ) ) ) / ( 2 * deltas[ i ] );

        }

    }

    BOOST_CHECK( tardigradeVectorTools::fuzzyEquals( dPK2MeanStressdFe, *R.getdPK2MeanStressdFe( ) ) );

    BOOST_CHECK( tardigradeVectorTools::fuzzyEquals( dPK2MeanStressdT, *R.getdPK2MeanStressdT( ) ) );

}

BOOST_AUTO_TEST_CASE( test_residual_setPK2IsochoricStress ){

    class residualMock : public tardigradeHydra::linearViscoelasticity::residual {

        public:

            using tardigradeHydra::linearViscoelasticity::residual::residual;

    };

    class hydraBaseMock : public tardigradeHydra::hydraBase {

        public:

            using tardigradeHydra::hydraBase::hydraBase;

        private:

            virtual void setResidualClasses( ){ }

    };

    floatType time = 1.1;

    floatType deltaTime = 2.2;

    floatType temperature = 300.0;

    floatType previousTemperature = 320.4;

    floatVector deformationGradient = { 1.1, 0.1, 0.0,
                                        0.0, 1.0, 0.0,
                                        0.0, 0.0, 1.0 };

    floatVector previousDeformationGradient = { 1.0, 0.0, 0.0,
                                                0.0, 1.0, 0.0,
                                                0.0, 0.0, 1.0 };

    floatVector previousStateVariables = { -1, 0, 1e-3, 1e-1,
                                           0, 0, 0, 0, 0, 0, 0, 0, 0,
                                           0, 0, 0, 0, 0, 0, 0, 0, 0,
                                           0, 0, 0, 0, 0, 0, 0, 0, 0 };

    floatVector parameters = { 2, 3, 123.4, 56.7, 10.0, 5.0, 293.15, 2, 3, 293.15, 23.4, 25.6, 0.1, 0.2, 12.3, 13.4, 14.5, 0.1, 1.0, 10.0 };

    unsigned int numConfigurations = 1;

    unsigned int numNonLinearSolveStateVariables = 0;

    unsigned int dimension = 3;

    unsigned int ISVlb = 2;

    unsigned int ISVub = 31;

    floatVector strain;
    BOOST_CHECK( !tardigradeConstitutiveTools::computeGreenLagrangeStrain( deformationGradient / std::pow( 1.1, 1/3.), strain ) );

    floatVector previousStrain;
    BOOST_CHECK( !tardigradeConstitutiveTools::computeGreenLagrangeStrain( previousDeformationGradient, previousStrain ) );

    floatType currentRateModifier;
    tardigradeConstitutiveTools::WLF( temperature, { parameters[ 7 ], parameters[ 8 ], 293.15 }, currentRateModifier );
    currentRateModifier = 1. / currentRateModifier;

    floatType previousRateModifier;
    tardigradeConstitutiveTools::WLF( previousTemperature, { parameters[ 7 ], parameters[ 8 ], 293.15 }, previousRateModifier );
    previousRateModifier = 1. / previousRateModifier;

    floatVector ISVs( previousStateVariables.begin( ) + ISVlb + parameters[ 0 ],
                      previousStateVariables.end( ) );
    floatVector params = { 2 * 56.7, 0.1, 1.0, 10.0, 2 * 12.3, 2 * 13.4, 2 * 14.5 };
    floatVector PK2IsochoricStressAnswer;
    floatVector updatedISVsAnswer;

    BOOST_CHECK( !tardigradeStressTools::linearViscoelasticity( 1.1, strain, -1.1, previousStrain, currentRateModifier, previousRateModifier, ISVs, params, 0.5, PK2IsochoricStressAnswer, updatedISVsAnswer ) );

    hydraBaseMock hydra( time, deltaTime, temperature, previousTemperature, deformationGradient, previousDeformationGradient,
                         previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

    residualMock R( &hydra, 9, parameters, ISVlb, ISVub, 0.5 );

    BOOST_CHECK( tardigradeVectorTools::fuzzyEquals( PK2IsochoricStressAnswer, *R.getPK2IsochoricStress( ) ) );

    BOOST_CHECK( tardigradeVectorTools::fuzzyEquals( updatedISVsAnswer, *R.getUpdatedIsochoricViscoelasticStateVariables( ) ) );

}

BOOST_AUTO_TEST_CASE( test_residual_setPK2IsochoricStressDerivatives ){

    class residualMock : public tardigradeHydra::linearViscoelasticity::residual {

        public:

            using tardigradeHydra::linearViscoelasticity::residual::residual;

    };

    class hydraBaseMock : public tardigradeHydra::hydraBase {

        public:

            using tardigradeHydra::hydraBase::hydraBase;

        private:

            virtual void setResidualClasses( ){ }

    };

    floatType time = 1.1;

    floatType deltaTime = 2.2;

    floatType temperature = 300.0;

    floatType previousTemperature = 320.4;

    floatVector deformationGradient = { 1.1, 0.1, 0.0,
                                        0.0, 1.0, 0.0,
                                        0.0, 0.0, 1.0 };

    floatVector previousDeformationGradient = { 1.0, 0.0, 0.0,
                                                0.0, 1.0, 0.0,
                                                0.0, 0.0, 1.0 };

    floatVector previousStateVariables = { -1, 0, 1e-3, 1e-1,
                                           0, 0, 0, 0, 0, 0, 0, 0, 0,
                                           0, 0, 0, 0, 0, 0, 0, 0, 0,
                                           0, 0, 0, 0, 0, 0, 0, 0, 0 };

    floatVector parameters = { 2, 3, 123.4, 56.7, 10.0, 5.0, 293.15, 2, 3, 293.15, 23.4, 25.6, 0.1, 0.2, 12.3, 13.4, 14.5, 0.1, 1.0, 10.0 };

    unsigned int numConfigurations = 1;

    unsigned int numNonLinearSolveStateVariables = 0;

    unsigned int dimension = 3;

    unsigned int ISVlb = 2;

    unsigned int ISVub = 31;

    hydraBaseMock hydra( time, deltaTime, temperature, previousTemperature, deformationGradient, previousDeformationGradient,
                         previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

    residualMock R( &hydra, 9, parameters, ISVlb, ISVub, 0.5 );

    floatType eps = 1e-6;

    floatMatrix dPK2IsochoricStressdFe( deformationGradient.size( ), floatVector( deformationGradient.size( ), 0 ) );

    floatVector dPK2IsochoricStressdT( deformationGradient.size( ), 0 );

    for ( unsigned int i = 0; i < deformationGradient.size( ); i++ ){

        floatVector deltas( deformationGradient.size( ), 0 );

        deltas[ i ] = eps * std::fabs( deformationGradient[ i ] ) + eps;

        hydraBaseMock hydrap( time, deltaTime, temperature, previousTemperature, deformationGradient + deltas, previousDeformationGradient,
                             previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

        residualMock Rp( &hydrap, 9, parameters, ISVlb, ISVub, 0.5 );

        hydraBaseMock hydram( time, deltaTime, temperature, previousTemperature, deformationGradient - deltas, previousDeformationGradient,
                             previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

        residualMock Rm( &hydram, 9, parameters, ISVlb, ISVub, 0.5 );

        for ( unsigned int j = 0; j < deformationGradient.size( ); j++ ){

            dPK2IsochoricStressdFe[ j ][ i ] = ( ( *Rp.getPK2IsochoricStress( ) )[ j ] - ( *Rm.getPK2IsochoricStress( ) )[ j ] ) / ( 2 * deltas[ i ] );

        }

    }

    for ( unsigned int i = 0; i < 1; i++ ){

        floatVector deltas( 1, 0 );

        deltas[ i ] = eps * std::fabs( temperature ) + eps;

        hydraBaseMock hydrap( time, deltaTime, temperature + deltas[ 0 ], previousTemperature, deformationGradient, previousDeformationGradient,
                             previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

        residualMock Rp( &hydrap, 9, parameters, ISVlb, ISVub, 0.5 );

        hydraBaseMock hydram( time, deltaTime, temperature - deltas[ 0 ], previousTemperature, deformationGradient, previousDeformationGradient,
                             previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

        residualMock Rm( &hydram, 9, parameters, ISVlb, ISVub, 0.5 );

        for ( unsigned int j = 0; j < deformationGradient.size( ); j++ ){

            dPK2IsochoricStressdT[ j ] = ( ( *Rp.getPK2IsochoricStress( ) )[ j ] - ( *Rm.getPK2IsochoricStress( ) )[ j ] ) / ( 2 * deltas[ i ] );

        }

    }

    BOOST_CHECK( tardigradeVectorTools::fuzzyEquals( dPK2IsochoricStressdFe, *R.getdPK2IsochoricStressdFe( ) ) );

    BOOST_CHECK( tardigradeVectorTools::fuzzyEquals( dPK2IsochoricStressdT, *R.getdPK2IsochoricStressdT( ) ) );

}

BOOST_AUTO_TEST_CASE( test_residual_setPK2Stress ){

    class residualMock : public tardigradeHydra::linearViscoelasticity::residual {

        public:

            using tardigradeHydra::linearViscoelasticity::residual::residual;

            floatType PK2MeanStress = 12.3;

            floatVector PK2IsochoricStress = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

            void setPK2MeanStress( const floatType &value ){

                tardigradeHydra::linearViscoelasticity::residual::setPK2MeanStress( value );

            }

            void setPK2IsochoricStress( const floatVector &value ){

                tardigradeHydra::linearViscoelasticity::residual::setPK2IsochoricStress( value );

            }

        private:

            virtual void setPK2MeanStress( ) override {

                setPK2MeanStress( PK2MeanStress );

            }

            virtual void setPK2IsochoricStress( ) override {

                setPK2IsochoricStress( PK2IsochoricStress );

            }

    };

    class hydraBaseMock : public tardigradeHydra::hydraBase {

        public:

            using tardigradeHydra::hydraBase::hydraBase;

        private:

            virtual void setResidualClasses( ){ }

    };

    floatType time = 1.1;

    floatType deltaTime = 2.2;

    floatType temperature = 300.0;

    floatType previousTemperature = 320.4;

    floatVector deformationGradient = { 1.1, 0.1, 0.0,
                                        0.0, 1.0, 0.0,
                                        0.0, 0.0, 1.0 };

    floatVector previousDeformationGradient = { 1.0, 0.0, 0.0,
                                                0.0, 1.0, 0.0,
                                                0.0, 0.0, 1.0 };

    floatVector previousStateVariables = { -1, 0, 1e-3, 1e-1,
                                           0, 0, 0, 0, 0, 0, 0, 0, 0,
                                           0, 0, 0, 0, 0, 0, 0, 0, 0,
                                           0, 0, 0, 0, 0, 0, 0, 0, 0 };

    floatVector parameters = { 2, 3, 123.4, 56.7, 10.0, 5.0, 293.15, 2, 3, 293.15, 23.4, 25.6, 0.1, 0.2, 12.3, 13.4, 14.5, 0.1, 1.0, 10.0 };

    unsigned int numConfigurations = 1;

    unsigned int numNonLinearSolveStateVariables = 0;

    unsigned int dimension = 3;

    unsigned int ISVlb = 2;

    unsigned int ISVub = 31;

    floatVector PK2StressAnswer = { 13.3, 2, 3, 4, 17.3, 6, 7, 8, 21.3 }; 

    hydraBaseMock hydra( time, deltaTime, temperature, previousTemperature, deformationGradient, previousDeformationGradient,
                         previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

    residualMock R( &hydra, 9, parameters, ISVlb, ISVub, 0.5 );

    BOOST_CHECK( tardigradeVectorTools::fuzzyEquals( PK2StressAnswer, *R.getPK2Stress( ) ) );

    BOOST_CHECK( tardigradeVectorTools::fuzzyEquals( tardigradeVectorTools::appendVectors( { *R.getUpdatedVolumetricViscoelasticStateVariables( ), *R.getUpdatedIsochoricViscoelasticStateVariables( ) } ),
                                           *R.getCurrentAdditionalStateVariables( ) ) );

}

BOOST_AUTO_TEST_CASE( test_residual_setPK2StressDerivatives ){

    class residualMock : public tardigradeHydra::linearViscoelasticity::residual {

        public:

            using tardigradeHydra::linearViscoelasticity::residual::residual;

    };

    class hydraBaseMock : public tardigradeHydra::hydraBase {

        public:

            using tardigradeHydra::hydraBase::hydraBase;

        private:

            virtual void setResidualClasses( ){ }

    };

    floatType time = 1.1;

    floatType deltaTime = 2.2;

    floatType temperature = 300.0;

    floatType previousTemperature = 320.4;

    floatVector deformationGradient = { 1.1, 0.1, 0.0,
                                        0.0, 1.0, 0.0,
                                        0.0, 0.0, 1.0 };

    floatVector previousDeformationGradient = { 1.0, 0.0, 0.0,
                                                0.0, 1.0, 0.0,
                                                0.0, 0.0, 1.0 };

    floatVector previousStateVariables = { -1, 0, 1e-3, 1e-1,
                                           0, 0, 0, 0, 0, 0, 0, 0, 0,
                                           0, 0, 0, 0, 0, 0, 0, 0, 0,
                                           0, 0, 0, 0, 0, 0, 0, 0, 0 };

    floatVector parameters = { 2, 3, 123.4, 56.7, 10.0, 5.0, 293.15, 2, 3, 293.15, 23.4, 25.6, 0.1, 0.2, 12.3, 13.4, 14.5, 0.1, 1.0, 10.0 };

    unsigned int numConfigurations = 1;

    unsigned int numNonLinearSolveStateVariables = 0;

    unsigned int dimension = 3;

    unsigned int ISVlb = 2;

    unsigned int ISVub = 31;

    floatMatrix dPK2StressdFe( deformationGradient.size( ), floatVector( deformationGradient.size( ), 0 ) );

    floatVector dPK2StressdT( deformationGradient.size( ), 0 );

    hydraBaseMock hydra( time, deltaTime, temperature, previousTemperature, deformationGradient, previousDeformationGradient,
                         previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

    residualMock R( &hydra, 9, parameters, ISVlb, ISVub, 0.5 );

    floatType eps = 1e-6;

    for ( unsigned int i = 0; i < deformationGradient.size( ); i++ ){

        floatVector deltas( deformationGradient.size( ), 0 );

        deltas[ i ] = eps * std::fabs( deformationGradient[ i ] ) + eps;

        hydraBaseMock hydrap( time, deltaTime, temperature, previousTemperature, deformationGradient + deltas, previousDeformationGradient,
                             previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

        residualMock Rp( &hydrap, 9, parameters, ISVlb, ISVub, 0.5 );

        hydraBaseMock hydram( time, deltaTime, temperature, previousTemperature, deformationGradient - deltas, previousDeformationGradient,
                             previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

        residualMock Rm( &hydram, 9, parameters, ISVlb, ISVub, 0.5 );

        for ( unsigned int j = 0; j < deformationGradient.size( ); j++ ){

            dPK2StressdFe[ j ][ i ] = ( ( *Rp.getPK2Stress( ) )[ j ] - ( *Rm.getPK2Stress( ) )[ j ] ) / ( 2 * deltas[ i ] );

        }

    }

    for ( unsigned int i = 0; i < 1; i++ ){

        floatVector deltas( 1, 0 );

        deltas[ i ] = eps * std::fabs( temperature ) + eps;

        hydraBaseMock hydrap( time, deltaTime, temperature + deltas[ 0 ], previousTemperature, deformationGradient, previousDeformationGradient,
                             previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

        residualMock Rp( &hydrap, 9, parameters, ISVlb, ISVub, 0.5 );

        hydraBaseMock hydram( time, deltaTime, temperature - deltas[ 0 ], previousTemperature, deformationGradient, previousDeformationGradient,
                             previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

        residualMock Rm( &hydram, 9, parameters, ISVlb, ISVub, 0.5 );

        for ( unsigned int j = 0; j < deformationGradient.size( ); j++ ){

            dPK2StressdT[ j ] = ( ( *Rp.getPK2Stress( ) )[ j ] - ( *Rm.getPK2Stress( ) )[ j ] ) / ( 2 * deltas[ i ] );

        }

    }

    BOOST_CHECK( tardigradeVectorTools::fuzzyEquals( dPK2StressdFe, *R.getdPK2StressdFe( ) ) );

    BOOST_CHECK( tardigradeVectorTools::fuzzyEquals( dPK2StressdT, *R.getdPK2StressdT( ) ) );

}

BOOST_AUTO_TEST_CASE( test_residual_setdCauchyStressdT ){

    class residualMock : public tardigradeHydra::linearViscoelasticity::residual {

        public:

            using tardigradeHydra::linearViscoelasticity::residual::residual;

    };

    class hydraBaseMock : public tardigradeHydra::hydraBase {

        public:

            using tardigradeHydra::hydraBase::hydraBase;

        private:

            virtual void setResidualClasses( ){ }

    };

    floatType time = 1.1;

    floatType deltaTime = 2.2;

    floatType temperature = 300.0;

    floatType previousTemperature = 320.4;

    floatVector deformationGradient = { 1.1, 0.1, 0.0,
                                        0.0, 1.0, 0.0,
                                        0.0, 0.0, 1.0 };

    floatVector previousDeformationGradient = { 1.0, 0.0, 0.0,
                                                0.0, 1.0, 0.0,
                                                0.0, 0.0, 1.0 };

    floatVector previousStateVariables = { -1, 0, 1e-3, 1e-1,
                                           0, 0, 0, 0, 0, 0, 0, 0, 0,
                                           0, 0, 0, 0, 0, 0, 0, 0, 0,
                                           0, 0, 0, 0, 0, 0, 0, 0, 0 };

    floatVector parameters = { 2, 3, 123.4, 56.7, 10.0, 5.0, 293.15, 2, 3, 293.15, 23.4, 25.6, 0.1, 0.2, 12.3, 13.4, 14.5, 0.1, 1.0, 10.0 };

    unsigned int numConfigurations = 1;

    unsigned int numNonLinearSolveStateVariables = 0;

    unsigned int dimension = 3;

    unsigned int ISVlb = 2;

    unsigned int ISVub = 31;

    floatMatrix dCauchyStressdF( deformationGradient.size( ), floatVector( deformationGradient.size( ), 0 ) ); // NOTE: This isn't strictly required! I'm just doing it for the warm fuzzies.

    floatVector dCauchyStressdT( deformationGradient.size( ), 0 );

    hydraBaseMock hydra( time, deltaTime, temperature, previousTemperature, deformationGradient, previousDeformationGradient,
                         previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

    residualMock R( &hydra, 9, parameters, ISVlb, ISVub, 0.5 );

    floatType eps = 1e-6;

    for ( unsigned int i = 0; i < deformationGradient.size( ); i++ ){

        floatVector deltas( deformationGradient.size( ), 0 );

        deltas[ i ] = eps * std::fabs( deformationGradient[ i ] ) + eps;

        hydraBaseMock hydrap( time, deltaTime, temperature, previousTemperature, deformationGradient + deltas, previousDeformationGradient,
                             previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

        residualMock Rp( &hydrap, 9, parameters, ISVlb, ISVub, 0.5 );

        hydraBaseMock hydram( time, deltaTime, temperature, previousTemperature, deformationGradient - deltas, previousDeformationGradient,
                             previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

        residualMock Rm( &hydram, 9, parameters, ISVlb, ISVub, 0.5 );

        for ( unsigned int j = 0; j < deformationGradient.size( ); j++ ){

            dCauchyStressdF[ j ][ i ] = ( ( *Rp.getCauchyStress( ) )[ j ] - ( *Rm.getCauchyStress( ) )[ j ] ) / ( 2 * deltas[ i ] );

        }

    }

    for ( unsigned int i = 0; i < 1; i++ ){

        floatVector deltas( 1, 0 );

        deltas[ i ] = eps * std::fabs( temperature ) + eps;

        hydraBaseMock hydrap( time, deltaTime, temperature + deltas[ 0 ], previousTemperature, deformationGradient, previousDeformationGradient,
                             previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

        residualMock Rp( &hydrap, 9, parameters, ISVlb, ISVub, 0.5 );

        hydraBaseMock hydram( time, deltaTime, temperature - deltas[ 0 ], previousTemperature, deformationGradient, previousDeformationGradient,
                             previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

        residualMock Rm( &hydram, 9, parameters, ISVlb, ISVub, 0.5 );

        for ( unsigned int j = 0; j < deformationGradient.size( ); j++ ){

            dCauchyStressdT[ j ] = ( ( *Rp.getCauchyStress( ) )[ j ] - ( *Rm.getCauchyStress( ) )[ j ] ) / ( 2 * deltas[ i ] );

        }

    }

    BOOST_CHECK( tardigradeVectorTools::fuzzyEquals( dCauchyStressdF, *R.getdCauchyStressdF( ) ) );

    BOOST_CHECK( tardigradeVectorTools::fuzzyEquals( dCauchyStressdT, *R.getdCauchyStressdT( ) ) );

}

BOOST_AUTO_TEST_CASE( test_residual_setdRdT ){

    class residualMock : public tardigradeHydra::linearViscoelasticity::residual {

        public:

            using tardigradeHydra::linearViscoelasticity::residual::residual;

    };

    class hydraBaseMock : public tardigradeHydra::hydraBase {

        public:

            using tardigradeHydra::hydraBase::hydraBase;

        private:

            virtual void setResidualClasses( ){ }

    };

    floatType time = 1.1;

    floatType deltaTime = 2.2;

    floatType temperature = 300.0;

    floatType previousTemperature = 320.4;

    floatVector deformationGradient = { 1.1, 0.1, 0.0,
                                        0.0, 1.0, 0.0,
                                        0.0, 0.0, 1.0 };

    floatVector previousDeformationGradient = { 1.0, 0.0, 0.0,
                                                0.0, 1.0, 0.0,
                                                0.0, 0.0, 1.0 };

    floatVector previousStateVariables = { -1, 0, 1e-3, 1e-1,
                                           0, 0, 0, 0, 0, 0, 0, 0, 0,
                                           0, 0, 0, 0, 0, 0, 0, 0, 0,
                                           0, 0, 0, 0, 0, 0, 0, 0, 0 };

    floatVector unknownVector = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };

    floatVector parameters = { 2, 3, 123.4, 56.7, 10.0, 5.0, 293.15, 2, 3, 293.15, 23.4, 25.6, 0.1, 0.2, 12.3, 13.4, 14.5, 0.1, 1.0, 10.0 };

    unsigned int numConfigurations = 1;

    unsigned int numNonLinearSolveStateVariables = 0;

    unsigned int dimension = 3;

    unsigned int ISVlb = 2;

    unsigned int ISVub = 31;

    floatMatrix dRdF( deformationGradient.size( ), floatVector( deformationGradient.size( ), 0 ) ); // NOTE: This isn't strictly required! I'm just doing it for the warm fuzzies.

    floatVector dRdT( deformationGradient.size( ), 0 );

    hydraBaseMock hydra( time, deltaTime, temperature, previousTemperature, deformationGradient, previousDeformationGradient,
                         previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

    tardigradeHydra::unit_test::hydraBaseTester::updateUnknownVector( hydra, unknownVector );

    residualMock R( &hydra, 9, parameters, ISVlb, ISVub, 0.5 );

    floatType eps = 1e-6;

    for ( unsigned int i = 0; i < deformationGradient.size( ); i++ ){

        floatVector deltas( deformationGradient.size( ), 0 );

        deltas[ i ] = eps * std::fabs( deformationGradient[ i ] ) + eps;

        hydraBaseMock hydrap( time, deltaTime, temperature, previousTemperature, deformationGradient + deltas, previousDeformationGradient,
                             previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

        tardigradeHydra::unit_test::hydraBaseTester::updateUnknownVector( hydrap, unknownVector );
        residualMock Rp( &hydrap, 9, parameters, ISVlb, ISVub, 0.5 );

        hydraBaseMock hydram( time, deltaTime, temperature, previousTemperature, deformationGradient - deltas, previousDeformationGradient,
                             previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

        tardigradeHydra::unit_test::hydraBaseTester::updateUnknownVector( hydram, unknownVector );
        residualMock Rm( &hydram, 9, parameters, ISVlb, ISVub, 0.5 );

        for ( unsigned int j = 0; j < deformationGradient.size( ); j++ ){

            dRdF[ j ][ i ] = ( ( *Rp.getResidual( ) )[ j ] - ( *Rm.getResidual( ) )[ j ] ) / ( 2 * deltas[ i ] );

        }

    }

    for ( unsigned int i = 0; i < 1; i++ ){

        floatVector deltas( 1, 0 );

        deltas[ i ] = eps * std::fabs( temperature ) + eps;

        hydraBaseMock hydrap( time, deltaTime, temperature + deltas[ 0 ], previousTemperature, deformationGradient, previousDeformationGradient,
                             previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

        tardigradeHydra::unit_test::hydraBaseTester::updateUnknownVector( hydrap, unknownVector );
        residualMock Rp( &hydrap, 9, parameters, ISVlb, ISVub, 0.5 );

        hydraBaseMock hydram( time, deltaTime, temperature - deltas[ 0 ], previousTemperature, deformationGradient, previousDeformationGradient,
                             previousStateVariables, parameters, numConfigurations, numNonLinearSolveStateVariables, dimension );

        tardigradeHydra::unit_test::hydraBaseTester::updateUnknownVector( hydram, unknownVector );
        residualMock Rm( &hydram, 9, parameters, ISVlb, ISVub, 0.5 );

        for ( unsigned int j = 0; j < deformationGradient.size( ); j++ ){

            dRdT[ j ] = ( ( *Rp.getResidual( ) )[ j ] - ( *Rm.getResidual( ) )[ j ] ) / ( 2 * deltas[ i ] );

        }

    }

    BOOST_CHECK( tardigradeVectorTools::fuzzyEquals( dRdF, *R.getdRdF( ) ) );

    BOOST_CHECK( tardigradeVectorTools::fuzzyEquals( dRdT, *R.getdRdT( ) ) );

}
