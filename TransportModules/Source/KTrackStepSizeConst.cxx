#include "KTrackStepSizeConst.h"

#include "KSRootProcess.h"
#include "KTrackParticle.h"

namespace Kassiopeia
{

    KTrackStepSizeConst::KTrackStepSizeConst() :
        KTrackStepSize(),
        fTimeStep(0.0),
        fLengthMax(0.0),
        fFirstTry(kTRUE)
    {
    }

    KTrackStepSizeConst::~KTrackStepSizeConst()
    {
    }

    Double_t KTrackStepSizeConst::ComputeTimeStep()
    {
        if(fFirstTry)
        {
            Double_t AverageSpeed = (fInitialParticle->GetVelocity().Mag() + fFinalParticle->GetVelocity().Mag() )/2.0;

            fTimeStep = fLengthMax/AverageSpeed;
            #ifdef DEBUG_VERBOSE
            //cout << "StepSizeConst::ComputeTimeStep: initial particle speed: " << fInitialParticle->GetSpeed() << endl;
            //cout << "StepSizeConst::ComputeTimeStep: final particle speed: " << fFinalParticle->GetSpeed() << endl;
            //cout << "StepSizeConst::ComputeTimeStep: average particle speed: " << AverageSpeed << endl;
            //cout << "StepSizeConst::ComputeTimeStep: suggesting a timestep of " << fLengthMax/AverageSpeed << endl;
            //cout << "StepSizeConst::ComputeTimeStep: current failure count: " << fFailureCount << endl;
            #endif
        }

        return fTimeStep;
    }

    Bool_t KTrackStepSizeConst::ComputeCheck()
    {
        Double_t AverageSpeed = (fInitialParticle->GetVelocity().Mag() + fFinalParticle->GetVelocity().Mag() )/2.0;
        Double_t TimeStep = KSRootProcess::GetInstance()->GetTimeStep();
        Double_t StepLength = AverageSpeed * TimeStep;

        #ifdef DEBUG_VERBOSE
        //cout << "StepSizeConst::Check: initial particle speed: " << fInitialParticle->GetSpeed() << endl;
        //cout << "StepSizeConst::Check: final particle speed: " << fFinalParticle->GetSpeed() << endl;
        //cout << "StepSizeConst::Check: average particle speed: " << AverageSpeed << endl;
        //cout << "StepSizeConst::Check: step length: " << StepLength << endl;
        //cout << "StepSizeConst::Check: max length: " << fLengthMax << endl;
        //cout << "StepSizeConst::Check: current failure count: " << fFailureCount << endl;
        #endif


        if( StepLength > (fLengthMax + 1e-9) )
        {

            #ifdef DEBUG_VERBOSE
            //cout << "StepSizeConst::Check: step rejected, halving timestep" << endl;
            #endif
            fTimeStep = (1.0/2.0) * TimeStep;

            fFirstTry=kFALSE;
            return kFALSE;
        }

        #ifdef DEBUG_VERBOSE
        //cout << "StepSizeConst::Check: step accepted" << endl;
        #endif

        fFirstTry=kTRUE;
        return kTRUE;
    }

    Bool_t KTrackStepSizeConst::EnableAction()
    {
        KTrackStepSize::EnableAction();
        fFirstTry = kTRUE;
        return kTRUE;
    }

}
