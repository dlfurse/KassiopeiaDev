#include "KTrackStepSize.h"

#include "KTrackStepComputer.h"

namespace Kassiopeia
{

    KTrackStepSize::KTrackStepSize() :
        KSStepSize(),
        fParent( NULL ),
        fInitialParticle( NULL ),
        fFinalParticle( NULL ),
        fError( NULL)
    {
    }

    KTrackStepSize::~KTrackStepSize()
    {
    }

    Bool_t KTrackStepSize::AddParent( KSProcess* aParentProcess )
    {
        KTrackStepComputer* StepComputer = NULL;
        StepComputer = dynamic_cast< KTrackStepComputer* >( aParentProcess );
        if( StepComputer != NULL )
        {
            fParent = StepComputer;
            return kTRUE;
        }

        return kFALSE;
    }

    Bool_t KTrackStepSize::EnableAction()
    {
        fInitialParticle = fParent->GetInitialParticle();
        fFinalParticle = fParent->GetFinalParticle();
        fError = fParent->GetError();
        return kTRUE;
    }
    Bool_t KTrackStepSize::DisableAction()
    {
        fInitialParticle = NULL;
        fFinalParticle = NULL;
        fError = NULL;
        return kTRUE;
    }

} /* namespace Kassiopeia */
