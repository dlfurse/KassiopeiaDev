#include "KTrackStepSizeNumError.h"

#include "KSRootProcess.h"
#include "KTrackParticle.h"
#include "KTrackError.h"
#include "KTrackExactStepComputer.h"
//#include "KTrackAdiabaticStepComputer.h"

namespace Kassiopeia
{

    KTrackStepSizeNumError::KTrackStepSizeNumError() :
        KTrackStepSize(),
        fTimeStep(0.0),
        fPositionErrorMin(0.0),
        fPositionErrorMax(1e10),
        fMomentumErrorMin(0.0),
        fMomentumErrorMax(1e10),
        fFirstStepRatio(0.0)
    {
    }

    KTrackStepSizeNumError::~KTrackStepSizeNumError()
    {
    }

    Double_t KTrackStepSizeNumError::ComputeTimeStep()
    {
        return fTimeStep;
    }

    Bool_t KTrackStepSizeNumError::ComputeCheck()
    {
        Double_t PositionError = TMath::Abs(fError->GetPositionError().Mag());
        Double_t MomentumError = TMath::Abs(fError->GetMomentumError().Mag());
        Double_t TimeStep = KSRootProcess::GetInstance()->GetTimeStep();

        #ifdef DEBUG_VERBOSE
        //cout.precision(20);
        //cout << "KTrackStepSizeNumError::Check: initial total energy: " << InitialETotal << endl;
        //cout << "KTrackStepSizeNumError::Check: final total energy: " << FinalETotal << endl;
        //cout << "KTrackStepSizeNumError::Check: error: " << Error << endl;
        #endif

        if( PositionError < fPositionErrorMin && MomentumError < fMomentumErrorMin)
        {
            #ifdef DEBUG_VERBOSE
            //cout << "KTrackStepSizeNumError::Check: error too small: " << Error << endl;
            #endif

            fTimeStep = TimeStep * 1.5;
            return kTRUE;
        }

        if( PositionError > fPositionErrorMax || MomentumError > fMomentumErrorMax)
        {
            #ifdef DEBUG_VERBOSE
            //cout << "KTrackStepSizeNumError::Check: error too large: " << Error << endl;
            #endif

            fTimeStep = TimeStep * (2.0/5.0);
            return kFALSE;
        }

        return kTRUE;
    }

    Bool_t KTrackStepSizeNumError::AddParent( KSProcess* aParentProcess )
    {


        KTrackExactStepComputer* ExactStepComputer = NULL;
        ExactStepComputer = dynamic_cast< KTrackExactStepComputer* >( aParentProcess );
        if( ExactStepComputer != NULL )
        {
            fParent = ExactStepComputer;
            fFirstStepRatio = 1./16.;
            return kTRUE;
        }

//        KTrackAdiabaticStepComputer* AdiabaticStepComputer = NULL;
//        AdiabaticStepComputer = dynamic_cast< KTrackAdiabaticStepComputer* >( aParentProcess );
//        if( AdiabaticStepComputer != NULL )
//        {
//            fParent = AdiabaticStepComputer;
//            fFirstStepRatio = 1.0;
//            return kTRUE;
//        }


        return kFALSE;
    }

    Bool_t KTrackStepSizeNumError::EnableAction()
    {
        KTrackStepSize::EnableAction();
        fTimeStep = fFirstStepRatio / fInitialParticle->GetCyclotronFrequency();
        return kTRUE;
    }

}


