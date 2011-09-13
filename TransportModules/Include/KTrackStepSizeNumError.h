#ifndef KTRACKSTEPSIZENUMERROR_H_
#define KTRACKSTEPSIZENUMERROR_H_

#include "KTrackStepSize.h"

namespace Kassiopeia
{

    class KTrackStepSizeNumError :
        public KTrackStepSize
    {
        public:
            KTrackStepSizeNumError();
            virtual ~KTrackStepSizeNumError();

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
            void SetPositionErrorMin( const Double_t& min );
            void SetPositionErrorMax( const Double_t& max );
            void SetMomentumErrorMin( const Double_t& min );
            void SetMomentumErrorMax( const Double_t& max );

        private:
            Double_t fTimeStep;
            Double_t fPositionErrorMin;
            Double_t fPositionErrorMax;
            Double_t fMomentumErrorMin;
            Double_t fMomentumErrorMax;

            //***********
            //composition
            //***********

        public:
            virtual Bool_t AddParent( KSProcess* aParentProcess );

            //*****
            //state
            //*****

        private:
            virtual Bool_t EnableAction();

            Double_t fFirstStepRatio;

    };

    inline void KTrackStepSizeNumError::SetPositionErrorMin( const Double_t& min )
    {
        fPositionErrorMin = min;
        return;
    }

    inline void KTrackStepSizeNumError::SetPositionErrorMax( const Double_t& max )
    {
        fPositionErrorMin = max;
        return;
    }

    inline void KTrackStepSizeNumError::SetMomentumErrorMin( const Double_t& min )
    {
        fMomentumErrorMin = min;
        return;
    }

    inline void KTrackStepSizeNumError::SetMomentumErrorMax( const Double_t& max )
    {
        fMomentumErrorMin = max;
        return;
    }

}


#endif /* KTRACKSTEPSIZENUMERROR_H_ */
