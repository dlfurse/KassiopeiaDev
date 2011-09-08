#ifndef KTRACKSTEPSIZE_H_
#define KTRACKSTEPSIZE_H_

#include "KSStepSize.h"

namespace Kassiopeia
{

    class KTrackStepComputer;
    class KTrackParticle;
    class KTrackError;

    class KTrackStepSize :
        public KSStepSize
    {
        public:
            KTrackStepSize();
            virtual ~KTrackStepSize();

            //*****
            //state
            //*****

        protected:
            virtual Bool_t EnableAction();
            virtual Bool_t DisableAction();

            //***********
            //composition
            //***********

        public:
            virtual Bool_t AddParent( KSProcess* aParentProcess );

        protected:
            KTrackStepComputer* fParent;
            KTrackParticle* fInitialParticle;
            KTrackParticle* fFinalParticle;
            KTrackError* fError;
    };

}

#endif
