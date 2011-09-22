#include "KScatteringStepSize.h"
#include "KScattering.h"

namespace Kassiopeia
{

    KScatteringStepSize::KScatteringStepSize() :
        KSStepSize(),
        fParent(NULL),
        fScatteringProbabilityMax(0.0)
    {
    }

    KScatteringStepSize::~KScatteringStepSize()
    {
    }

    Double_t KScatteringStepSize::ComputeTimeStep()
    {
        Double_t DiffScatteringProbability = fParent->GetDiffScatteringProbability();
//        #ifdef DEBUG_VERBOSE
//        //cout << "KTrackStepSizeScattering::ComputeTimeStep: differential scattering probability: " << DiffScatteringProbability << endl;
//        //cout << "KTrackStepSizeScattering::ComputeTimeStep: suggesting a timestep of: " << fScatteringProbabilityMax/DiffScatteringProbability << endl;
//        #endif
        return fScatteringProbabilityMax/DiffScatteringProbability;
    }

    Bool_t KScatteringStepSize::ComputeCheck()
    {
        Double_t ScatteringProbability = fParent->GetScatteringProbability();
        #ifdef DEBUG_VERBOSE
        //cout << "KTrackStepSizeScattering::Check: scattering probability: " << ScatteringProbability << endl;
        #endif
        if( ScatteringProbability > fScatteringProbabilityMax )
        {
            #ifdef DEBUG_VERBOSE
            //cout << "KTrackStepSizeScattering::Check: step rejected" << endl;
            #endif
            return kFALSE;
        }
        #ifdef DEBUG_VERBOSE
        //cout << "KTrackStepSizeScattering::Check: step accepted" << endl;
        #endif
        return kTRUE;
     }

    Bool_t KScatteringStepSize::AddParent( KSProcess* aParentProcess )
    {
        KScattering* ScatteringProcess = NULL;
        ScatteringProcess = dynamic_cast< KScattering* >( aParentProcess );
        if( ScatteringProcess != NULL )
        {
            fParent = ScatteringProcess;
            return kTRUE;
        }

        return kFALSE;
    }

    Bool_t KScatteringStepSize::EnableAction()
    {
        return kTRUE;
    }

}


