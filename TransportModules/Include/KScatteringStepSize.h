#ifndef KSCATTERINGSTEPSIZE_H_
#define KSCATTERINGSTEPSIZE_H_

#include "KSStepSize.h"

namespace Kassiopeia
{
    class KScattering;

    class KScatteringStepSize :
        public KSStepSize
    {
        public:
            KScatteringStepSize();
            virtual ~KScatteringStepSize();

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
            void SetScatteringProbabilityMax( const Double_t& lossMax );

        private:
            KScattering* fParent;
            Double_t fScatteringProbabilityMax;

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

    };

    inline void KScatteringStepSize::SetScatteringProbabilityMax( const Double_t& lossMax )
    {
        fScatteringProbabilityMax = lossMax;
        return;
    }

} /* namespace Kassiopeia */
#endif /* KSCATTERINGSTEPSIZE_H_ */
