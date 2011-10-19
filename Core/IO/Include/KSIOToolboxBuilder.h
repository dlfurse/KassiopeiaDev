#ifndef KSIOTOOLBOXBUILDER_H_
#define KSIOTOOLBOXBUILDER_H_

#include "KSToolboxModuleBuilder.h"
#include "KSIOToolbox.h"

namespace Kassiopeia
{

    class KSIOToolboxBuilder :
        public KSToolboxModuleBuilder< KSIOToolbox, KSIOToolboxBuilder >
    {
        public:
            KSIOToolboxBuilder();
            virtual ~KSIOToolboxBuilder();
    };

}

#endif
