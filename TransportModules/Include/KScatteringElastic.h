#ifndef KSCATTERINGELASTIC_H_
#define KSCATTERINGELASTIC_H_

#include "KScattering.h"

namespace Kassiopeia
{
    class KScatteringCalculatorElastic;

    class KScatteringElastic:
        public KScattering
    {
        public:
            KScatteringElastic();
            virtual ~KScatteringElastic();

        private:
            KScatteringCalculatorElastic* fElasticCalculator;


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
#endif /* KSCATTERINGELASTIC_H_ */
