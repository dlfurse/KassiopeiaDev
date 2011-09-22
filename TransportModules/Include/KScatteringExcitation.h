#ifndef KSCATTERINGEXCITATION_H_
#define KSCATTERINGEXCITATION_H_

#include "KScattering.h"

namespace Kassiopeia
{
    class KScatteringCalculatorInelastic;

    class KScatteringExcitation:
        public KScattering
    {
        public:
            KScatteringExcitation();
            virtual ~KScatteringExcitation();

        private:
            KScatteringCalculatorInelastic* fInelasticCalculator;


            //******
            //action
            //******

        public:
            Bool_t Execute();

        private:
            Double_t GetInitialCrossSection_Recalculate() const;
            Double_t GetFinalCrossSection_Recalculate() const;

    };

} /* namespace Kassiopeia */
#endif /* KSCATTERINGEXCITATION_H_ */
