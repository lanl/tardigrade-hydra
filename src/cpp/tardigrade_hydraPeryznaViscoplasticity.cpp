/**
  ******************************************************************************
  * \file tardigrade-hydraPeryznaViscoplasticity.h
  ******************************************************************************
  * An implementation of peryznaViscoplasticity using the hydra framework. Used
  * as an example and as the basis for more complex models.
  ******************************************************************************
  */

#include<tardigrade_hydraPeryznaViscoplasticity.h>
#include<tardigrade_constitutive_tools.h>
#include<tardigrade_stress_tools.h>

namespace tardigradeHydra{

    namespace peryznaViscoplasticity{

        void residual::setDrivingStress( ){
            /*!
             * Set the driving stress i.e. the Cauchy stress pulled back to the
             * current configuration of the plastic configuration.
             */

            setDrivingStress( false );

        }

        void residual::setDrivingStress( const bool isPrevious ){
            /*!
             * Set the driving stress i.e. the Cauchy stress pulled back to the
             * current configuration of the plastic configuration.
             *
             * \param isPrevious: Flag for whether to compute this in the previous configuration
             */

            const floatVector *cauchyStress;

            floatVector precedingConfiguration;

            floatVector drivingStress;

            if ( isPrevious ){

                TARDIGRADE_ERROR_TOOLS_CATCH( precedingConfiguration = hydra->getPreviousPrecedingConfiguration( *getPlasticConfigurationIndex( ) ) );

                TARDIGRADE_ERROR_TOOLS_CATCH( cauchyStress = hydra->getPreviousCauchyStress( ) );

            }
            else{

                TARDIGRADE_ERROR_TOOLS_CATCH( precedingConfiguration = hydra->getPrecedingConfiguration( *getPlasticConfigurationIndex( ) ) );

                TARDIGRADE_ERROR_TOOLS_CATCH( cauchyStress = hydra->getCauchyStress( ) );

            }

            tardigradeConstitutiveTools::pullBackCauchyStress( *cauchyStress, precedingConfiguration, drivingStress );

            if ( isPrevious ){

                setPreviousDrivingStress( drivingStress );

            }
            else{

                setDrivingStress( drivingStress );

            }

        }

        void residual::setDrivingStress( const floatVector &drivingStress ){
            /*!
             * Set the driving stress i.e. the Cauchy stress pulled back to the
             * current configuration of the plastic configuration.
             * 
             * \param &drivingStress: The driving stress
             */

            _drivingStress.second = drivingStress;

            _drivingStress.first = true;

            addIterationData( &_drivingStress );

        }

        void residual::setPreviousDrivingStress( const floatVector &previousDrivingStress ){
            /*!
             * Set the previous driving stress i.e. the Cauchy stress pulled back to the
             * current configuration of the plastic configuration.
             * 
             * \param &previousDrivingStress: The previous driving stress
             */

            _previousDrivingStress.second = previousDrivingStress;

            _previousDrivingStress.first = true;

        }

        void residual::setFlowDirection( ){
            /*!
             * Set the flow direction in the current configuration of the
             * plastic configuration.
             * 
             * Current formulation is Drucker-Prager based on the potential
             * 
             * $\f g = \hat{\sigma} + A \bar{\sigma}\f$
             * 
             * where
             * 
             * $\f \hat{\sigma} = \sqrt{\frac{3}{2} \sigma_{ij}^{\text{dev}} \sigma_{ij}^{\text{dev}} }\f$
             * $\f \bar{\sigma} = \sigma_{ii}\f$
             * 
             * $\f \sigma_{ij}^{\text{dev}} = \sigma_{ij} - \frac{1}{3} \bar{\sigma} \delta_{ij}\f$
             */

            setFlowDirection( false );

        }

        void residual::setFlowDirection( const bool isPrevious ){
            /*!
             * Set the flow direction in the current configuration of the
             * plastic configuration.
             * 
             * Current formulation is Drucker-Prager based on the potential
             * 
             * $\f g = \hat{\sigma} + A \bar{\sigma}\f$
             * 
             * where
             * 
             * $\f \hat{\sigma} = \sqrt{\frac{3}{2} \sigma_{ij}^{\text{dev}} \sigma_{ij}^{\text{dev}} }\f$
             * $\f \bar{\sigma} = \sigma_{ii}\f$
             * 
             * $\f \sigma_{ij}^{\text{dev}} = \sigma_{ij} - \frac{1}{3} \bar{\sigma} \delta_{ij}\f$
             * 
             * \param isPrevious: Flag for whether to compute the values in the previous configuration
             */

            const floatVector *drivingStress;

            const floatVector *flowParameters;

            floatType g;

            if ( isPrevious ){

                TARDIGRADE_ERROR_TOOLS_CATCH( drivingStress = getPreviousDrivingStress( ) );

            }
            else{

                TARDIGRADE_ERROR_TOOLS_CATCH( drivingStress = getDrivingStress( ) );

            }

            TARDIGRADE_ERROR_TOOLS_CATCH( flowParameters = getFlowParameters( ) );

            floatVector dgdDrivingStress( drivingStress->size( ), 0 );

            floatVector flowDirection( drivingStress->size( ), 0 );

            TARDIGRADE_ERROR_TOOLS_CATCH_NODE_POINTER( tardigradeStressTools::druckerPragerSurface( *drivingStress, ( *flowParameters )[ 1 ], ( *flowParameters )[ 0 ], g, dgdDrivingStress, flowDirection ) );

            if ( isPrevious ){

                setPreviousFlowDirection( flowDirection );

            }
            else{

                setFlowDirection( flowDirection );

            }

        }

        void residual::setFlowDirection( const floatVector &flowDirection ){
            /*!
             * Set the flow direction in the current configuration of the
             * plastic configuration.
             * 
             * \param &flowDirection: The flow direction in the current configuration
             *     of the plastic configuration.
             */

            _flowDirection.second = flowDirection;

            _flowDirection.first = true;

            addIterationData( &_flowDirection );

        }

        void residual::setPreviousFlowDirection( const floatVector &previousFlowDirection ){
            /*!
             * Set the previous flow direction in the current configuration of the
             * plastic configuration.
             * 
             * \param &previousFlowDirection: The previous flow direction in the current
             *     configuration of the plastic configuration.
             */

            _previousFlowDirection.second = previousFlowDirection;

            _previousFlowDirection.first = true;

        }

        void residual::setYieldFunction( ){
            /*!
             * Set the value of the yield function
             */

            setYieldFunction( false );

        }

        void residual::setYieldFunction( const bool isPrevious ){
            /*!
             * Set the value of the yield function
             * 
             * \param isPrevious: Flag for whether this is the previous timestep
             */

            const floatVector* drivingStress;

            const floatVector* yieldParameters;

            floatType yieldFunction;

            if ( isPrevious ){

                TARDIGRADE_ERROR_TOOLS_CATCH( drivingStress = getPreviousDrivingStress( ) );

            }
            else{

                TARDIGRADE_ERROR_TOOLS_CATCH( drivingStress = getDrivingStress( ) );

            }

            TARDIGRADE_ERROR_TOOLS_CATCH( yieldParameters = getYieldParameters( ) );

            TARDIGRADE_ERROR_TOOLS_CATCH_NODE_POINTER( tardigradeStressTools::druckerPragerSurface( *drivingStress, ( *yieldParameters )[ 1 ], ( *yieldParameters )[ 0 ], yieldFunction ) );

            if ( isPrevious ){

                setPreviousYieldFunction( yieldFunction );

            }
            else{

                setYieldFunction( yieldFunction );

            }

        }

        void residual::setYieldFunction( const floatType &yieldFunction ){
            /*!
             * Set the value of the yield function
             */

            _yieldFunction.second = yieldFunction;

            _yieldFunction.first = true;

            addIterationData( &_yieldFunction );

        }

        void residual::setPreviousYieldFunction( const floatType &previousYieldFunction ){
            /*!
             * Set the value of the previous yield function
             */

            _previousYieldFunction.second = previousYieldFunction;

            _previousYieldFunction.first = true;

        }

        void residual::setPlasticThermalMultiplier( ){
            /*!
             * Set the plastic thermal multiplier
             */

            setPlasticThermalMultiplier( false );

        }

        void residual::setPlasticThermalMultiplier( const bool isPrevious ){
            /*!
             * Set the plastic thermal multiplier
             */

            const floatType *temperature;

            const floatVector *temperatureParameters;

            floatType plasticThermalMultiplier;

            if ( isPrevious ){

                TARDIGRADE_ERROR_TOOLS_CATCH( temperature = hydra->getPreviousTemperature( ) );

            }
            else{

                TARDIGRADE_ERROR_TOOLS_CATCH( temperature = hydra->getTemperature( ) );

            }

            TARDIGRADE_ERROR_TOOLS_CATCH( temperatureParameters = getThermalParameters( ) );

            TARDIGRADE_ERROR_TOOLS_CATCH_NODE_POINTER( tardigradeConstitutiveTools::WLF( *temperature, { ( *temperatureParameters )[ 2 ], ( *temperatureParameters )[ 0 ], ( *temperatureParameters )[ 1 ] }, plasticThermalMultiplier ) ); 

            if ( isPrevious ){

                setPreviousPlasticThermalMultiplier( plasticThermalMultiplier );

            }
            else{

                setPlasticThermalMultiplier( plasticThermalMultiplier );

            }

        }

        void residual::setPlasticThermalMultiplier( const floatType &plasticThermalMultiplier ){
            /*!
             * Set the plastic thermal multiplier
             */

            _plasticThermalMultiplier.second = plasticThermalMultiplier;

            _plasticThermalMultiplier.first = true;

            addIterationData( &_plasticThermalMultiplier );

        }

        void residual::setPreviousPlasticThermalMultiplier( const floatType &previousPlasticThermalMultiplier ){
            /*!
             * Set the previous plastic thermal multiplier
             */

            _previousPlasticThermalMultiplier.second = previousPlasticThermalMultiplier;

            _previousPlasticThermalMultiplier.first = true;

        }

        void residual::setHardeningFunction( ){
            /*!
             * Set the value of the hardening function
             */

            setHardeningFunction( false );

        }

        void residual::setHardeningFunction( const bool isPrevious ){
            /*!
             * Set the value of the hardening function
             * 
             * \param &isPrevious: Flag for whether to compute the values for the
             *     previous timestep
             */

            const floatVector *stateVariables;

            const floatVector *hardeningParameters;

            if ( isPrevious ){

                TARDIGRADE_ERROR_TOOLS_CATCH( stateVariables = getPreviousStateVariables( ) );

            }
            else{

                TARDIGRADE_ERROR_TOOLS_CATCH( stateVariables = getStateVariables( ) );

            }

            TARDIGRADE_ERROR_TOOLS_CATCH( hardeningParameters = getDragStressParameters( ) );

            floatType hardeningFunction;

            TARDIGRADE_ERROR_TOOLS_CATCH( tardigradeStressTools::linearHardening( *stateVariables, floatVector( hardeningParameters->begin( ) + 1, hardeningParameters->end( ) ), ( *hardeningParameters )[ 0 ], hardeningFunction ) );

            if ( isPrevious ){

                setPreviousHardeningFunction( hardeningFunction );

            }
            else{

                setHardeningFunction( hardeningFunction );

            }

        }

        void residual::setHardeningFunction( const floatType &hardeningFunction ){
            /*!
             * Set the hardening function
             */

            _hardeningFunction.second = hardeningFunction;

            _hardeningFunction.first = true;

            addIterationData( &_hardeningFunction );

        }

        void residual::setPreviousHardeningFunction( const floatType &previousHardeningFunction ){
            /*!
             * Set the previous hardening function
             */

            _previousHardeningFunction.second = previousHardeningFunction;

            _previousHardeningFunction.first = true;

        }

        void residual::setPlasticMultiplier( ){
            /*!
             * Set the plastic multiplier in the current configuration of the
             * plastic configuration
             */

            setPlasticMultiplier( false );

        }

        void residual::setPlasticMultiplier( const bool isPrevious ){
            /*!
             * Set the plastic multiplier in the current configuration of the
             * plastic configuration
             * 
             * \param &isPrevious: Flag for whether to compute the plastic multiplier
             *     in the previous timestep
             */

            const floatType *yieldFunction;

            const floatType *hardeningFunction;

            const floatType *plasticThermalMultiplier;

            const floatVector *peryznaParameters;

            floatType plasticMultiplier;

            if ( isPrevious ){

                TARDIGRADE_ERROR_TOOLS_CATCH( yieldFunction = getPreviousYieldFunction( ) );

                TARDIGRADE_ERROR_TOOLS_CATCH( hardeningFunction = getPreviousHardeningFunction( ) );

                TARDIGRADE_ERROR_TOOLS_CATCH( plasticThermalMultiplier = getPreviousPlasticThermalMultiplier( ) );

            }
            else{

                TARDIGRADE_ERROR_TOOLS_CATCH( yieldFunction = getYieldFunction( ) );

                TARDIGRADE_ERROR_TOOLS_CATCH( hardeningFunction = getHardeningFunction( ) );

                TARDIGRADE_ERROR_TOOLS_CATCH( plasticThermalMultiplier = getPlasticThermalMultiplier( ) );

            }

            TARDIGRADE_ERROR_TOOLS_CATCH( peryznaParameters = getPeryznaParameters( ) );

            TARDIGRADE_ERROR_TOOLS_CATCH_NODE_POINTER( tardigradeStressTools::peryznaModel( *yieldFunction, *hardeningFunction, *plasticThermalMultiplier, ( *peryznaParameters )[ 0 ], plasticMultiplier ) );

            if ( isPrevious ){

                setPreviousPlasticMultiplier( plasticMultiplier );

            }
            else{

                setPlasticMultiplier( plasticMultiplier );

            }

        }

        void residual::setPlasticMultiplier( const floatType &plasticMultiplier ){
            /*!
             * Set the plastic multiplier in the current configuration of the
             * plastic configuration
             * 
             * \param &plasticMultiplier: The plastic multiplier in the current
             *     configuration of the plastic configuration
             */

            _plasticMultiplier.second = plasticMultiplier;

            _plasticMultiplier.first = true;

            addIterationData( &_plasticMultiplier );

        }

        void residual::setPreviousPlasticMultiplier( const floatType &previousPlasticMultiplier ){
            /*!
             * Set the previous plastic multiplier in the current configuration of the
             * plastic configuration
             * 
             * \param &previousPlasticMultiplier: The previous plastic multiplier in
             *     the current configuration of the plastic configuration
             */

            _previousPlasticMultiplier.second = previousPlasticMultiplier;

            _previousPlasticMultiplier.first = true;

        }

        void residual::setVelocityGradient( ){
            /*!
             * Set the velocity gradient in the current configuration of the plastic
             * configuration
             */

            setVelocityGradient( false );

        }

        void residual::setVelocityGradient( const bool isPrevious ){
            /*!
             * Set the velocity gradient in the current configuration of the plastic
             * configuration
             * 
             * \param isPrevious: Flag for whether to compute the value at the previous
             *     timestep.
             */

            const floatType *plasticMultiplier;

            const floatVector *flowDirection;

            if ( isPrevious ){

                TARDIGRADE_ERROR_TOOLS_CATCH( plasticMultiplier = getPreviousPlasticMultiplier( ) );

                TARDIGRADE_ERROR_TOOLS_CATCH( flowDirection = getPreviousFlowDirection( ) );

                setPreviousVelocityGradient( ( *plasticMultiplier ) * ( *flowDirection ) );

            }
            else{

                TARDIGRADE_ERROR_TOOLS_CATCH( plasticMultiplier = getPlasticMultiplier( ) );

                TARDIGRADE_ERROR_TOOLS_CATCH( flowDirection = getFlowDirection( ) );

                setVelocityGradient( ( *plasticMultiplier ) * ( *flowDirection ) );

            }

        }

        void residual::setVelocityGradient( const floatVector &velocityGradient ){
            /*!
             * Set the velocity gradient in the current configuration of the plastic
             * configuration
             * 
             * \param &velocityGradient: The velocity gradient in the current
             *     configuration of the plastic configuration
             */

            _velocityGradient.second = velocityGradient;

            _velocityGradient.first = true;

            addIterationData( &_velocityGradient );

        }

        void residual::setPreviousVelocityGradient( const floatVector &previousVelocityGradient ){
            /*!
             * Set the previous velocity gradient in the current configuration of the plastic
             * configuration
             * 
             * \param &previousVelocityGradient: The velocity gradient in the current
             *     configuration of the plastic configuration
             */

            _previousVelocityGradient.second = previousVelocityGradient;

            _previousVelocityGradient.first = true;

        }

        void residual::setPlasticDeformationGradient( ){
            /*!
             * Set the plastic deformation gradient
             */

            throw "not implemented";

        }

        void residual::setPlasticDeformationGradient( const floatVector &plasticDeformationGradient ){
            /*!
             * Set the plastic deformation gradient
             *
             * \param &plasticDeformationGradient: The plastic deformation gradient
             */

            _plasticDeformationGradient.second = plasticDeformationGradient;

            _plasticDeformationGradient.first = true;

            addIterationData( &_plasticDeformationGradient );

        }

        void residual::setStateVariables( ){
            /*!
             * Set the state variables
             */

            setStateVariables( false );

        }

        void residual::setStateVariables( const bool isPrevious ){
            /*!
             * Set the state variables
             * 
             * \param isPrevious: Flag for whether the values are at the previous timestep.
             */

            const floatVector *allStateVariables;

            if ( isPrevious ){

                allStateVariables =  hydra->getPreviousNonLinearSolveStateVariables( );

            }
            else{

                allStateVariables =  hydra->getNonLinearSolveStateVariables( );

            }

            floatVector stateVariables( getStateVariableIndices( )->size( ), 0 );

            for ( auto index = getStateVariableIndices( )->begin( ); index != getStateVariableIndices( )->end( ); index++ ){

                if ( *index >= allStateVariables->size( ) ){

                    
                    std::string message = "The requested state variable is outside of the available range.\n";
                    message            += "  requested index: " + std::to_string( *index ) + "\n";
                    message            += "  total state variable number: " + std::to_string( allStateVariables->size( ) ) + "\n";

                    TARDIGRADE_ERROR_TOOLS_CATCH( throw std::runtime_error( message ) );

                }

                stateVariables[ index - getStateVariableIndices( )->begin( ) ] = ( *allStateVariables )[ *index ];

            }

            if ( isPrevious ){

                setPreviousStateVariables( stateVariables );

            }
            else{

                setStateVariables( stateVariables );

            }

        }

        void residual::setStateVariables( const floatVector &stateVariables ){
            /*!
             * Set the state variables
             * 
             * \param &stateVariables: The state variables
             */

            _stateVariables.second = stateVariables;

            _stateVariables.first = true;

            addIterationData( &_stateVariables );

        }

        void residual::setPreviousStateVariables( const floatVector &previousStateVariables ){
            /*!
             * Set the previous values of the state variables
             * 
             * \param &previousStateVariables: The previous state variables
             */

            _previousStateVariables.second = previousStateVariables;

            _previousStateVariables.first = true;

        }

        void residual::setPeryznaParameters( const floatVector &peryznaParameters ){
            /*!
             * Set the Peryzna parameters
             * 
             * \param &peryznaParameters: The Peryzna parameters
             */

            _peryznaParameters.second = peryznaParameters;

            _peryznaParameters.first = true;

        }

        void residual::setDragStressParameters( const floatVector &dragStressParameters ){
            /*!
             * Set the drag stress parameters
             * 
             * \param &dragStressParameters: The drag stress parameters
             */

            _dragStressParameters.second = dragStressParameters;

            _dragStressParameters.first = true;

        }

        void residual::setThermalParameters( const floatVector &thermalParameters ){
            /*!
             * Set the thermal parameters
             * 
             * \param &thermalParameters: The thermal parameters
             */

            _thermalParameters.second = thermalParameters;

            _thermalParameters.first = true;

        }

        void residual::setYieldParameters( const floatVector &yieldParameters ){
            /*!
             * Set the yield parameters
             * 
             * \param &yieldParameters: The yield parameters
             */

            _yieldParameters.second = yieldParameters;

            _yieldParameters.first = true;

        }

        void residual::setFlowParameters( const floatVector &flowParameters ){
            /*!
             * Set the flow parameters
             * 
             * \param &flowParameters: The flow parameters
             */

            _flowParameters.second = flowParameters;

            _flowParameters.first = true;

        }

        void residual::setMixingParameters( const floatVector &mixingParameters ){
            /*!
             * Set the mixing parameters
             * 
             * \param &mixingParameters: The mixing parameters
             */

            _mixingParameters.second = mixingParameters;

            _mixingParameters.first = true;

        }

        void residual::setResidual( ){
            /*!
             * Set the value of the residual
             * 
             * Defined as the residual's computed plastic deformation gradient minus the value stored in hydra's configurations
             * and the difference between the computed state variable's and hydra's stored values.
             */

            throw "not implemented";

        }

        void residual::setJacobian( ){
            /*!
             * Set the value of the Jacobian
             */

            throw "not implemented";

        }

        void residual::setdRdT( ){
            /*!
             * Set the derivative of the residual w.r.t. the temperature.
             */

            throw "not implemented";

        }

        void residual::setdRdF( ){
            /*!
             * Set the derivative of the residual w.r.t. the deformation gradient.
             */

            throw "not implemented";

        }

        const unsigned int* residual::getPlasticConfigurationIndex( ){
            /*!
             * Get plastic configuration index
             */

            return &_plasticConfigurationIndex;

        }

        const std::vector< unsigned int >* residual::getStateVariableIndices( ){
            /*!
             * Get state variable indices
             */

            return &_stateVariableIndices;

        }

        const floatVector* residual::getDrivingStress( ){
            /*!
             * Get the driving stress
             */

            if ( !_drivingStress.first ){

                TARDIGRADE_ERROR_TOOLS_CATCH( setDrivingStress( ) );

            }

            return &_drivingStress.second;

        }

        const floatVector* residual::getFlowDirection( ){
            /*!
             * Get the flow direction
             */

            if ( !_flowDirection.first ){

                TARDIGRADE_ERROR_TOOLS_CATCH( setFlowDirection( ) );

            }

            return &_flowDirection.second;

        }

        const floatType* residual::getYieldFunction( ){
            /*!
             * Get the value of the yield function
             */

            if ( !_yieldFunction.first ){

                TARDIGRADE_ERROR_TOOLS_CATCH( setYieldFunction( ) );

            }

            return &_yieldFunction.second;

        }

        const floatType* residual::getPlasticThermalMultiplier( ){
            /*!
             * Get the value of the plastic thermal multiplier
             */

            if ( !_plasticThermalMultiplier.first ){

                TARDIGRADE_ERROR_TOOLS_CATCH( setPlasticThermalMultiplier( ) );

            }

            return &_plasticThermalMultiplier.second;

        }

        const floatType* residual::getHardeningFunction( ){
            /*!
             * Get the value of the hardening function
             */

            if ( !_hardeningFunction.first ){

                TARDIGRADE_ERROR_TOOLS_CATCH( setHardeningFunction( ) );

            }

            return &_hardeningFunction.second;

        }

        const floatType* residual::getPlasticMultiplier( ){
            /*!
             * Get the plastic multiplier
             */

            if ( !_plasticMultiplier.first ){

                TARDIGRADE_ERROR_TOOLS_CATCH( setPlasticMultiplier( ) );

            }

            return &_plasticMultiplier.second;

        }

        const floatVector* residual::getVelocityGradient( ){
            /*!
             * Get the velocity gradient
             */

            if ( !_velocityGradient.first ){

                TARDIGRADE_ERROR_TOOLS_CATCH( setVelocityGradient( ) );

            }

            return &_velocityGradient.second;

        }

        const floatVector* residual::getPlasticDeformationGradient( ){
            /*!
             * Get the plastic deformation gradient
             */

            if ( !_plasticDeformationGradient.first ){

                TARDIGRADE_ERROR_TOOLS_CATCH( setPlasticDeformationGradient( ) );

            }

            return &_plasticDeformationGradient.second;

        }

        const floatVector* residual::getStateVariables( ){
            /*!
             * Get the state variables
             */

            if ( !_stateVariables.first ){

                TARDIGRADE_ERROR_TOOLS_CATCH( setStateVariables( ) );

            }

            return &_stateVariables.second;

        }

        const floatVector* residual::getPreviousDrivingStress( ){
            /*!
             * Get the previous driving stress
             */

            if ( !_previousDrivingStress.first ){

                TARDIGRADE_ERROR_TOOLS_CATCH( setDrivingStress( true ) );

            }

            return &_previousDrivingStress.second;

        }

        const floatVector* residual::getPreviousFlowDirection( ){
            /*!
             * Get the previous flow direction
             */

            if ( !_previousFlowDirection.first ){

                TARDIGRADE_ERROR_TOOLS_CATCH( setFlowDirection( true ) );

            }

            return &_previousFlowDirection.second;

        }

        const floatType* residual::getPreviousYieldFunction( ){
            /*!
             * Get the previous value of the yield function
             */

            if ( !_previousYieldFunction.first ){

                TARDIGRADE_ERROR_TOOLS_CATCH( setYieldFunction( true ) );

            }

            return &_previousYieldFunction.second;

        }

        const floatType* residual::getPreviousPlasticThermalMultiplier( ){
            /*!
             * Get the previous value of the plastic thermal multiplier
             */

            if ( !_previousPlasticThermalMultiplier.first ){

                TARDIGRADE_ERROR_TOOLS_CATCH( setPlasticThermalMultiplier( true ) );

            }

            return &_previousPlasticThermalMultiplier.second;

        }

        const floatType* residual::getPreviousHardeningFunction( ){
            /*!
             * Get the previous value of the hardening function
             */

            if ( !_previousHardeningFunction.first ){

                TARDIGRADE_ERROR_TOOLS_CATCH( setHardeningFunction( true ) );

            }

            return &_previousHardeningFunction.second;

        }

        const floatType* residual::getPreviousPlasticMultiplier( ){
            /*!
             * Get the previous plastic multiplier
             */

            if ( !_previousPlasticMultiplier.first ){

                TARDIGRADE_ERROR_TOOLS_CATCH( setPlasticMultiplier( true ) );

            }

            return &_previousPlasticMultiplier.second;

        }

        const floatVector* residual::getPreviousVelocityGradient( ){
            /*!
             * Get the previous velocity gradient
             */

            if ( !_previousVelocityGradient.first ){

                TARDIGRADE_ERROR_TOOLS_CATCH( setVelocityGradient( true ) );

            }

            return &_previousVelocityGradient.second;

        }

        const floatVector* residual::getPreviousStateVariables( ){
            /*!
             * Get the previous state variables
             */

            if ( !_previousStateVariables.first ){

                TARDIGRADE_ERROR_TOOLS_CATCH( setStateVariables( true ) );

            }

            return &_previousStateVariables.second;

        }

        const floatVector* residual::getPeryznaParameters( ){
            /*!
             * Get the Peryzna parameters
             */

            if ( !_peryznaParameters.first ){

                TARDIGRADE_ERROR_TOOLS_CATCH( throw std::runtime_error( "Peryzna parameters not defined but required" ) );

            }

            return &_peryznaParameters.second;

        }

        const floatVector* residual::getDragStressParameters( ){
            /*!
             * Get the drag stress parameters
             */

            if ( !_dragStressParameters.first ){

                TARDIGRADE_ERROR_TOOLS_CATCH( throw std::runtime_error( "Drag stress parameters not defined but required" ) );

            }

            return &_dragStressParameters.second;

        }

        const floatVector* residual::getThermalParameters( ){
            /*!
             * Get the thermal parameters
             */

            if ( !_thermalParameters.first ){

                TARDIGRADE_ERROR_TOOLS_CATCH( throw std::runtime_error( "Thermal parameters not defined but required" ) );

            }

            return &_thermalParameters.second;

        }

        const floatVector* residual::getYieldParameters( ){
            /*!
             * Get the yield parameters
             */

            if ( !_yieldParameters.first ){

                TARDIGRADE_ERROR_TOOLS_CATCH( throw std::runtime_error( "Yield parameters not defined but required" ) );

            }

            return &_yieldParameters.second;

        }

        const floatVector* residual::getFlowParameters( ){
            /*!
             * Get the flow parameters
             */

            if ( !_flowParameters.first ){

                TARDIGRADE_ERROR_TOOLS_CATCH( throw std::runtime_error( "Flow parameters not defined but required" ) );

            }

            return &_flowParameters.second;

        }

        const floatVector* residual::getMixingParameters( ){
            /*!
             * Get the mixing parameters
             */

            if ( !_mixingParameters.first ){

                TARDIGRADE_ERROR_TOOLS_CATCH( throw std::runtime_error( "Mixing parameters not defined but required" ) );

            }

            return &_mixingParameters.second;

        }

        void residual::decomposeParameters( const floatVector &parameters ){
            /*!
             * Decompose the incoming parameter vector
             * 
             * \param &parameters: The incoming parameter vector. We assume a
             *     Peryzna viscoplastic driving stress with a Drucker-Prager
             *     yield and flow potential surface. The parameters are
             *     [ n, q0, q1, C1, C2, Tref, Y, A, B, H ] where n is the
             *     Peryzna exponent, q0 is the initial drag stress, q1 is the
             *     drag modulus, C1, C2, and Tref are the temperature effect
             *     parameters, Y is the yield stress for the Drucker-Prager equation,
             *     A is the pressure term of the yield equation, B is the flow parameter,
             *     and H is the mixing modulus.
             */

            unsigned int expectedSize = 10;

            if ( parameters.size( ) != expectedSize ){

                std::string message = "The parameters vector is not the correct length.\n";
                message            += "  parameters: " + std::to_string( parameters.size( ) ) + "\n";
                message            += "  required:   " + std::to_string( expectedSize ) + "\n";

                TARDIGRADE_ERROR_TOOLS_CATCH( throw std::runtime_error( message ) );

            }

            setPeryznaParameters( { parameters[ 0 ] } );

            setDragStressParameters( { parameters[ 1 ], parameters[ 2 ] } );

            setThermalParameters( { parameters[ 3 ], parameters[ 4 ], parameters[ 5 ] } );

            setYieldParameters( { parameters[ 6 ], parameters[ 7 ] } );

            setFlowParameters( { 0., parameters[ 8 ] } );

            setMixingParameters( { parameters[ 9 ] } );

        }

    }

}
