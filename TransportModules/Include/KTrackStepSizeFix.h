#ifndef KTRACKSTEPSIZEFIX_H_
#define KTRACKSTEPSIZEFIX_H_

#include "KTrackStepSize.h"

namespace Kassiopeia
{

    class KTrackStepSizeFix :
        public KTrackStepSize
    {
        public:
            KTrackStepSizeFix();
            virtual ~KTrackStepSizeFix();

            //******
            //action
            //******

        public:
            virtual Double_t ComputeTimeStep();
            virtual Bool_t ComputeCheck();

            //*************
            //configuration
            //*************

        public:
            void SetTimeStep( const Double_t& aTimeStep );

        private:
            Double_t fTimeStep;
    };

    inline void KTrackStepSizeFix::SetTimeStep( const Double_t& aTimeStep )
    {
        fTimeStep = aTimeStep;
        return;
    }

}

#endif /* KTRACKSTEPSIZEFIX_H_ */
