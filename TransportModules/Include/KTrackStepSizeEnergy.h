#ifndef KTRACKSTEPSIZEENERGY_H_
#define KTRACKSTEPSIZEENERGY_H_

#include "KTrackStepSize.h"

namespace Kassiopeia
{

    class KTrackStepSizeEnergy :
        public KTrackStepSize
    {
        public:
            KTrackStepSizeEnergy();
            virtual ~KTrackStepSizeEnergy();

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
            void SetErrorMin( const Double_t& min );
            void SetErrorMax( const Double_t& max );

        private:
            Double_t fTimeStep;
            Double_t fErrorMin;
            Double_t fErrorMax;

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

    inline void KTrackStepSizeEnergy::SetErrorMin( const Double_t& min )
    {
        fErrorMin = min;
        return;
    }

    inline void KTrackStepSizeEnergy::SetErrorMax( const Double_t& max )
    {
        fErrorMin = max;
        return;
    }

}

#endif /* KTRACKSTEPSIZEENERGY_H_ */
