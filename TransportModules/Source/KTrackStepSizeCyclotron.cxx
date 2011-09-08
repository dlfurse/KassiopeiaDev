#include "KTrackStepSizeCyclotron.h"

#include "KTrackParticle.h"

namespace Kassiopeia
{

    KTrackStepSizeCyclotron::KTrackStepSizeCyclotron() :
        KTrackStepSize(),
        fFraction( 1. / 16. )
    {
    }

    KTrackStepSizeCyclotron::~KTrackStepSizeCyclotron()
    {
    }

    Double_t KTrackStepSizeCyclotron::ComputeTimeStep()
    {
        return fFraction / fInitialParticle->GetCyclotronFrequency();
    }

    Bool_t KTrackStepSizeCyclotron::ComputeCheck()
    {
        return kTRUE;
    }

}
