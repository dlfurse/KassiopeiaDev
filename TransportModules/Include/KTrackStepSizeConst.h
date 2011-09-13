#ifndef KTRACKSTEPSIZECONST_H_
#define KTRACKSTEPSIZECONST_H_

#include "KTrackStepSize.h"

namespace Kassiopeia
{

    class KTrackStepSizeConst :
        public KTrackStepSize
    {
        public:
            KTrackStepSizeConst();
            virtual ~KTrackStepSizeConst();

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
            void SetLengthMax( const Double_t& length );

        private:
            Double_t fTimeStep;
            Double_t fLengthMax;
            Bool_t fFirstTry;

            //*****
            //state
            //*****

        private:
            virtual Bool_t EnableAction();

    };

    inline void KTrackStepSizeConst::SetTimeStep( const Double_t& aTimeStep )
    {
        fTimeStep = aTimeStep;
        return;
    }

    inline void KTrackStepSizeConst::SetLengthMax( const Double_t& length )
    {
        fLengthMax = length;
        return;
    }

}

#endif /* KTRACKSTEPSIZECONST_H_ */
