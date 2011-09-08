#include "KTrackStepComputer.h"

#include "KMathODESolver.h"
#include "KMathCompositeODE.h"

#include "KSRootProcess.h"
#include "KSRootMagneticField.h"
#include "KSRootElectricField.h"
#include "KSStep.h"

#include "KTrackParticle.h"
#include "KTrackError.h"

namespace Kassiopeia
{

    KTrackStepComputer::KTrackStepComputer( KMathODESolver* anODESolver, KMathCompositeODE* aCompositeODE, KTrackParticle* anInitialParticle, Double_t* anInitialParticleData, KTrackParticle* anActiveParticle, Double_t* anActiveParticleData, KTrackParticle* aFinalParticle, Double_t* aFinalParticleData, KTrackError* anError, Double_t* anErrorData ) :
        fParent( NULL ),
        fSubProcesses(),
        fSubStepSizes(),
        fODESolver( anODESolver ),
        fODE( aCompositeODE ),
        fInitialParticle( anInitialParticle ),
        fInitialParticleData( anInitialParticleData ),
        fActiveParticle( anActiveParticle ),
        fActiveParticleData( anActiveParticleData ),
        fFinalParticle( aFinalParticle ),
        fFinalParticleData( aFinalParticleData ),
        fError( anError ),
        fErrorData( anErrorData )
    {
        fODESolver->SetODE( fODE );
        fODESolver->SetInitialConditionArea( fInitialParticleData );
        fODESolver->SetFinalConditionArea( fFinalParticleData );
        fODESolver->SetErrorConditionArea( fErrorData );

        fInitialParticle->SetData( fInitialParticleData );
        fInitialParticle->SetMagneticFieldCalculator( KSRootMagneticField::GetInstance() );
        fInitialParticle->SetElectricFieldCalculator( KSRootElectricField::GetInstance() );

        fActiveParticle->SetMagneticFieldCalculator( KSRootMagneticField::GetInstance() );
        fActiveParticle->SetElectricFieldCalculator( KSRootElectricField::GetInstance() );

        fFinalParticle->SetData( fFinalParticleData );
        fFinalParticle->SetMagneticFieldCalculator( KSRootMagneticField::GetInstance() );
        fFinalParticle->SetElectricFieldCalculator( KSRootElectricField::GetInstance() );
    }

    KTrackStepComputer::~KTrackStepComputer()
    {
        delete fODE;
        delete fInitialParticle;
        delete[] fInitialParticleData;
        delete fActiveParticle;
        delete[] fActiveParticleData;
        delete fFinalParticle;
        delete[] fFinalParticleData;
        delete fError;
        delete[] fErrorData;
    }

    Bool_t KTrackStepComputer::EnableAction()
    {
        KTrackParticle::SetMass( fParent->GetStep()->GetInitialParticle()->GetMass() );
        KTrackParticle::SetCharge( fParent->GetStep()->GetInitialParticle()->GetCharge() );

        fInitialParticle->SetParticle( fParent->GetStep()->GetInitialParticle() );
        fActiveParticle->SetParticle( fParent->GetStep()->GetInitialParticle() );
        fFinalParticle->SetParticle( fParent->GetStep()->GetFinalParticle() );

        if( fSubProcesses.ForEachUntilFalse( &KSProcess::Enable ) == kFALSE )
        {
            return kFALSE;
        }

        if( fSubStepSizes.ForEachUntilFalse( &KSStepSize::Enable ) == kFALSE )
        {
            return kFALSE;
        }

        return kTRUE;
    }
    Bool_t KTrackStepComputer::DisableAction()
    {
        if( fSubProcesses.ForEachUntilFalse( &KSProcess::Disable ) == kFALSE )
        {
            return kFALSE;
        }

        if( fSubStepSizes.ForEachUntilFalse( &KSStepSize::Disable ) == kFALSE )
        {
            return kFALSE;
        }

        return kTRUE;
    }

    Bool_t KTrackStepComputer::ComputeStep()
    {
        fInitialParticle->PullUpdate();

        while( kTRUE )
        {
            fODESolver->SetTimeStep( fParent->GetTimeStep() );
            fODESolver->CalculateSolution();

            fFinalParticle->Reset();
            fError->Reset();

            if( fSubStepSizes.ForEachUntilFalse( &KSStepSize::ComputeCheck ) == kFALSE )
            {
                fParent->SetTimeStep( ComputeTimeStep() );
            }
            else
            {
                fParent->SetTimeStep( fFinalParticle->GetTime() - fInitialParticle->GetTime() );
                break;
            }
        }

        fFinalParticle->PushUpdate();

        return kTRUE;
    }
    Double_t KTrackStepComputer::ComputeTimeStep()
    {
        return fSubStepSizes.SmallestOfAll( &KSStepSize::ComputeTimeStep );
    }

    Bool_t KTrackStepComputer::AddParent( KSProcess* aParentProcess )
    {
        KSRootProcess* RootProcess = NULL;
        RootProcess = dynamic_cast< KSRootProcess* >( aParentProcess );
        if( RootProcess != NULL )
        {
            fParent = RootProcess;
            return kTRUE;
        }
        return kFALSE;
    }

    Bool_t KTrackStepComputer::AddProcess( KSProcess* aSubProcess )
    {
        if( (aSubProcess->AddParent( this ) == kTRUE) && (fSubProcesses.AddElement( aSubProcess ) != -1) )
        {
            if( IsEnabled() )
            {
                aSubProcess->Enable();
            }
            return kTRUE;
        }
        return kFALSE;
    }
    Bool_t KTrackStepComputer::RemoveProcess( KSProcess* aSubProcess )
    {
        if( fSubProcesses.RemoveElement( aSubProcess ) != -1 )
        {
            if( IsEnabled() )
            {
                aSubProcess->Disable();
            }
        }
        return kTRUE;
    }

    Bool_t KTrackStepComputer::AddStepSize( KSStepSize* aSubStepSize )
    {
        if( (aSubStepSize->AddParent( this ) == kTRUE) && (fSubStepSizes.AddElement( aSubStepSize ) != -1) )
        {
            if( IsEnabled() )
            {
                aSubStepSize->Enable();
            }
            return kTRUE;
        }
        return kFALSE;
    }
    Bool_t KTrackStepComputer::RemoveStepSize( KSStepSize* aSubStepSize )
    {
        if( fSubStepSizes.RemoveElement( aSubStepSize ) != -1 )
        {
            if( IsEnabled() )
            {
                aSubStepSize->Disable();
            }
        }
        return kTRUE;
    }

} /* namespace Kassiopeia */
