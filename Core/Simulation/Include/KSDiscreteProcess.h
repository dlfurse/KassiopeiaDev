#ifndef KSDISCRETEPROCESS_H_
#define KSDISCRETEPROCESS_H_

#include "KSProcess.h"

namespace Kassiopeia
{

    class KSDiscreteProcess :
        public KSProcess
    {
        public:
            KSDiscreteProcess();
            virtual ~KSDiscreteProcess();

            //******
            //action
            //******

        public:
            virtual Double_t& ComputeProbability() = 0;

    };

}

#endif

