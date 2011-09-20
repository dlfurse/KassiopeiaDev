#ifndef KTRACKSCATTERINGELASTIC_H_
#define KTRACKSCATTERINGELASTIC_H_

#include "KTrackScattering.h"

namespace Kassiopeia
{
    class KScatterBasicElasticCalculatorFerenc;

    class KTrackScatteringElastic:
        public KTrackScattering
    {
        public:
            KTrackScatteringElastic();
            virtual ~KTrackScatteringElastic();

        private:
            KScatterBasicElasticCalculatorFerenc* fElasticCalculator;


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
#endif /* KTRACKSCATTERINGELASTIC_H_ */
