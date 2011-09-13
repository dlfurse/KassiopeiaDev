#include "KTrackStepSizeEnergy.h"

#include "KSRootProcess.h"
#include "KTrackParticle.h"
#include "KSConst.h"
#include "KTrackExactStepComputer.h"
//#include "KTrackAdiabaticStepComputer.h"

namespace Kassiopeia
{

    KTrackStepSizeEnergy::KTrackStepSizeEnergy() :
        KTrackStepSize(),
        fTimeStep(0.0),
        fErrorMin(0.0),
        fErrorMax(0.0),
        fFirstStepRatio(0.0)
    {
    }

    KTrackStepSizeEnergy::~KTrackStepSizeEnergy()
    {
    }

    Double_t KTrackStepSizeEnergy::ComputeTimeStep()
    {
        return fTimeStep;
    }

    Bool_t KTrackStepSizeEnergy::ComputeCheck()
    {
        Double_t InitialETotal = fInitialParticle->GetKineticEnergy() + fInitialParticle->GetCharge()*fInitialParticle->GetElectricPotential()*1. / KSConst::Q();
        Double_t FinalETotal = fFinalParticle->GetKineticEnergy() + fFinalParticle->GetCharge()*fFinalParticle->GetElectricPotential()*1. / KSConst::Q();
        Double_t Error = TMath::Abs((FinalETotal-InitialETotal)/InitialETotal);
        Double_t TimeStep = KSRootProcess::GetInstance()->GetTimeStep();

        #ifdef DEBUG_VERBOSE
        //cout.precision(20);
        //cout << "KTrackStepSizeEnergy::Check: initial total energy: " << InitialETotal << endl;
        //cout << "KTrackStepSizeEnergy::Check: final total energy: " << FinalETotal << endl;
        //cout << "KTrackStepSizeEnergy::Check: error: " << Error << endl;
        #endif

        if( Error < fErrorMin )
        {
            #ifdef DEBUG_VERBOSE
            //cout << "KTrackStepSizeEnergy::Check: error too small: " << Error << endl;
            #endif

            fTimeStep = TimeStep * 1.5;
            return kTRUE;
        }

        if( Error > fErrorMax )
        {
            #ifdef DEBUG_VERBOSE
            //cout << "KTrackStepSizeEnergy::Check: error too large: " << Error << endl;
            #endif

            fTimeStep = TimeStep * (2.0/5.0);
            return kFALSE;
        }

        return kTRUE;
    }

    Bool_t KTrackStepSizeEnergy::AddParent( KSProcess* aParentProcess )
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

    Bool_t KTrackStepSizeEnergy::EnableAction()
    {
        KTrackStepSize::EnableAction();
        fTimeStep = fFirstStepRatio / fInitialParticle->GetCyclotronFrequency();
        return kTRUE;
    }

}


