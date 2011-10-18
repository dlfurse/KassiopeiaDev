#ifndef KSTOOLBOX_H_
#define KSTOOLBOX_H_

#include "KSManager.h"
#include "KSProcessor.h"

namespace Kassiopeia
{

    class KSToolbox
    {
        public:
            KSToolbox();
            virtual ~KSToolbox();

            //*********
            //processor
            //*********

            virtual Bool_t ProcessEndToken( KSTokenBeginElement* aToken );
            virtual Bool_t ProcessEndToken( KSTokenEndElement* aToken );

    };

}

#endif
