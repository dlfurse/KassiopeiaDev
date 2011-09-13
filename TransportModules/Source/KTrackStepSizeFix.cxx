#include "KTrackStepSizeFix.h"

namespace Kassiopeia
{

    KTrackStepSizeFix::KTrackStepSizeFix() :
        KTrackStepSize(),
        fTimeStep(0.0)
    {
    }

    KTrackStepSizeFix::~KTrackStepSizeFix()
    {
    }

    Double_t KTrackStepSizeFix::ComputeTimeStep()
    {
        return fTimeStep;
    }

    Bool_t KTrackStepSizeFix::ComputeCheck()
    {
        return kTRUE;
    }

}
