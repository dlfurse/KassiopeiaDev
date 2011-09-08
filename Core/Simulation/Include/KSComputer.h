#ifndef KSCOMPUTER_H_
#define KSCOMPUTER_H_

#include "KSProcess.h"

namespace Kassiopeia
{

    class KSComputer :
        public KSProcess
    {
        public:
            KSComputer();
            virtual ~KSComputer();

            void ExecuteTransport();
            void ExecuteDiscreteProcess();

        private:
            KSProcess* fTransportProcess;
            KSProcess* fDiscreteProcess;
    };

}

#endif
