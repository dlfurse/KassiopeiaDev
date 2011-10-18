#ifndef KSBUILDERPROCESSOR_H_
#define KSBUILDERPROCESSOR_H_

#include "KSToolboxModuleBuilder.h"

namespace Kassiopeia
{

    class KSIOToolbox;

    class KSBuilderProcessor :
        public KSToolboxModuleBuilder< KSIOToolbox, KSBuilderProcessor >
    {
        public:
            KSBuilderProcessor();
            virtual ~KSBuilderProcessor();
    };

}

#endif
