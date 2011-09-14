#ifndef KSIOMESSAGE_H_
#define KSIOMESSAGE_H_

#include "KSMessage.h"
#include "KSSingle.h"

namespace Kassiopeia
{

    class KSIOMessage :
        public KSMessage
    {
        public:
            KSIOMessage();
            virtual ~KSIOMessage();
    };

    extern KSIOMessage& iomsg;
    static KSSingle< KSIOMessage > siomsg;

}

#endif
