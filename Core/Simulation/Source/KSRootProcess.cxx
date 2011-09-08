#include "KSRootProcess.h"

#include "KSTransportProcess.h"
#include "KSDiscreteProcess.h"

namespace Kassiopeia
{

    KSRootProcess* KSRootProcess::fInstance = NULL;
    KSRootProcess* KSRootProcess::GetInstance()
    {
        if( fInstance == NULL )
        {
            fInstance = new KSRootProcess();
            fInstance->SetName( "RootProcess" );
        }
        return fInstance;
    }

    KSRootProcess::KSRootProcess() :
        fTransportProcess( NULL ),
        fEndDiscreteProcess( 0 ),
        fCurrentDiscreteProcess( 0 ),
        fCurrentStep( NULL ),
        fCurrentTimeStep( 0. ),
        fCurrentTimeCompression( 0. )
    {

    }
    KSRootProcess::~KSRootProcess()
    {
    }

    Bool_t KSRootProcess::EnableAction()
    {
        if( fTransportProcess != NULL )
        {
            if( fTransportProcess->Enable() == kFALSE )
            {
                return kFALSE;
            }
        }

        for( fCurrentDiscreteProcess = 0; fCurrentDiscreteProcess < fEndDiscreteProcess; fCurrentDiscreteProcess++ )
        {
            if( fDiscreteProcesses[fCurrentDiscreteProcess]->Enable() == kFALSE )
            {
                return kFALSE;
            }
        }

        return kTRUE;
    }
    Bool_t KSRootProcess::DisableAction()
    {
        if( fTransportProcess != NULL )
        {
            if( fTransportProcess->Disable() == kFALSE )
            {
                return kFALSE;
            }
        }

        for( fCurrentDiscreteProcess = 0; fCurrentDiscreteProcess < fEndDiscreteProcess; fCurrentDiscreteProcess++ )
        {
            if( fDiscreteProcesses[fCurrentDiscreteProcess]->Disable() == kFALSE )
            {
                return kFALSE;
            }
        }

        return kTRUE;
    }

    Bool_t KSRootProcess::ComputeStep()
    {
        fCurrentTimeStep = ComputeTimeStep();

        if( fTransportProcess->ComputeStep() == kFALSE )
        {
            return kFALSE;
        }

        //TODO: navigation algorithm goes here

        for( fCurrentDiscreteProcess = 0; fCurrentDiscreteProcess < fEndDiscreteProcess; fCurrentDiscreteProcess++ )
        {
            if( fDiscreteProcesses[fCurrentDiscreteProcess]->ComputeStep() == kFALSE )
            {
                return kFALSE;
            }
        }

        return kTRUE;
    }
    Double_t KSRootProcess::ComputeTimeStep()
    {
        Double_t TimeStep = 1.e30;
        Double_t CurrentTimeStep = fTransportProcess->ComputeTimeStep();
        if( CurrentTimeStep < TimeStep )
        {
            TimeStep = CurrentTimeStep;
        }
        for( fCurrentDiscreteProcess = 0; fCurrentDiscreteProcess < fEndDiscreteProcess; fCurrentDiscreteProcess++ )
        {
            CurrentTimeStep = fDiscreteProcesses[fCurrentDiscreteProcess]->ComputeTimeStep();
            if( CurrentTimeStep < TimeStep )
            {
                TimeStep = CurrentTimeStep;
            }
        }
        return TimeStep;
    }

    //***********
    //composition
    //***********

    Bool_t KSRootProcess::AddParent( KSProcess* /*aParentProcess*/)
    {
        return kFALSE;
    }
    Bool_t KSRootProcess::AddProcess( KSProcess* aSubProcess )
    {
        KSTransportProcess* Transport = NULL;
        Transport = dynamic_cast< KSTransportProcess* >( aSubProcess );
        if( Transport != NULL )
        {
            fTransportProcess = Transport;
            Transport->AddParent( this );
            if( IsEnabled() )
            {
                Transport->Enable();
            }
            return kTRUE;
        }
        KSDiscreteProcess* Discrete = NULL;
        Discrete = dynamic_cast< KSDiscreteProcess* >( aSubProcess );
        if( Discrete != NULL )
        {
            fDiscreteProcesses[fEndDiscreteProcess] = Discrete;
            fDiscreteProcesses[fEndDiscreteProcess]->AddParent( this );
            if( IsEnabled() )
            {
                fDiscreteProcesses[fEndDiscreteProcess]->Enable();
            }
            fEndDiscreteProcess++;
            return kTRUE;
        }

        if( (fTransportProcess != NULL) && (fTransportProcess->AddProcess( aSubProcess ) == kTRUE) )
        {
            return kTRUE;
        }
        for( fCurrentDiscreteProcess = 0; fCurrentDiscreteProcess < fEndDiscreteProcess; fCurrentDiscreteProcess++ )
        {
            if( fDiscreteProcesses[fCurrentDiscreteProcess]->AddProcess( aSubProcess ) == kTRUE )
            {
                return kTRUE;
            }
        }

        return kFALSE;
    }
    Bool_t KSRootProcess::RemoveProcess( KSProcess* aSubProcess )
    {
        if( fTransportProcess == aSubProcess )
        {
            if( IsEnabled() )
            {
                fTransportProcess->Disable();
            }
            fTransportProcess = NULL;
            return kTRUE;
        }

        Bool_t ProcessFound = kFALSE;
        for( fCurrentDiscreteProcess = 0; fCurrentDiscreteProcess < fEndDiscreteProcess; fCurrentDiscreteProcess++ )
        {
            if( ProcessFound == kTRUE )
            {
                fDiscreteProcesses[fCurrentDiscreteProcess - 1] = fDiscreteProcesses[fCurrentDiscreteProcess];
                continue;
            }
            if( fDiscreteProcesses[fCurrentDiscreteProcess] == aSubProcess )
            {
                if( IsEnabled() )
                {
                    fDiscreteProcesses[fCurrentDiscreteProcess]->Disable();
                }
                fDiscreteProcesses[fCurrentDiscreteProcess] = NULL;
                ProcessFound = kTRUE;
            }
        }
        if( ProcessFound == kTRUE )
        {
            fEndDiscreteProcess--;
            return kTRUE;
        }


        if( (fTransportProcess != NULL) && (fTransportProcess->RemoveProcess( aSubProcess ) == kTRUE) )
        {
            return kTRUE;
        }

        for( fCurrentDiscreteProcess = 0; fCurrentDiscreteProcess < fEndDiscreteProcess; fCurrentDiscreteProcess++ )
        {
            if( fDiscreteProcesses[fCurrentDiscreteProcess]->RemoveProcess( aSubProcess ) == kTRUE )
            {
                return kTRUE;
            }
        }

        return kFALSE;
    }
    Bool_t KSRootProcess::AddStepSize( KSStepSize* aSubStepSize )
    {
        if( (fTransportProcess != NULL) && (fTransportProcess->AddStepSize( aSubStepSize ) == kTRUE) )
        {
            return kTRUE;
        }
        for( fCurrentDiscreteProcess = 0; fCurrentDiscreteProcess < fEndDiscreteProcess; fCurrentDiscreteProcess++ )
        {
            if( fDiscreteProcesses[fCurrentDiscreteProcess]->AddStepSize( aSubStepSize ) == kTRUE )
            {
                return kTRUE;
            }
        }

        return kFALSE;
    }
    Bool_t KSRootProcess::RemoveStepSize( KSStepSize* aSubStepSize )
    {
        if( (fTransportProcess != NULL) && (fTransportProcess->RemoveStepSize( aSubStepSize ) == kTRUE) )
        {
            return kTRUE;
        }
        for( fCurrentDiscreteProcess = 0; fCurrentDiscreteProcess < fEndDiscreteProcess; fCurrentDiscreteProcess++ )
        {
            if( fDiscreteProcesses[fCurrentDiscreteProcess]->RemoveStepSize( aSubStepSize ) == kTRUE )
            {
                return kTRUE;
            }
        }

        return kFALSE;
    }

}
