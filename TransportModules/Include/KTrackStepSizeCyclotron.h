#ifndef KTRACKSTEPSIZECYCLOTRON_H_
#define KTRACKSTEPSIZECYCLOTRON_H_

#include "KTrackStepSize.h"

namespace Kassiopeia
{

    class KTrackStepSizeCyclotron :
        public KTrackStepSize
    {
        public:
            KTrackStepSizeCyclotron();
            virtual ~KTrackStepSizeCyclotron();

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
            void SetFraction( const Double_t& aFraction );

        private:
            Double_t fFraction;
    };

    inline void KTrackStepSizeCyclotron::SetFraction( const Double_t& aFraction )
    {
        fFraction = aFraction;
        return;
    }

}

#endif
