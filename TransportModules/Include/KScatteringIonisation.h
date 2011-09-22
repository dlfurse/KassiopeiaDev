#ifndef KSCATTERINGIONISATION_H_
#define KSCATTERINGIONISATION_H_

#include "KScattering.h"

namespace Kassiopeia
{
    class KScatteringCalculatorInelastic;

    class KScatteringIonisation:
        public KScattering
    {
        public:
            KScatteringIonisation();
            virtual ~KScatteringIonisation();

        private:
            KScatteringCalculatorInelastic* fInelasticCalculator;


            //******
            //action
            //******

        public:
            Bool_t Execute();

        private:
            void CreateSecondaryParticle(Double_t ELoss) const;
            Double_t GetInitialCrossSection_Recalculate() const;
            Double_t GetFinalCrossSection_Recalculate() const;

    };

} /* namespace Kassiopeia */
#endif /* KSCATTERINGIONISATION_H_ */
