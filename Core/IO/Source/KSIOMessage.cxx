#include "KSIOMessage.h"

namespace Kassiopeia
{

    KSIOMessage::KSIOMessage() :
        KSMessage("IO")
    {
        fSystemDescription = string( "INPUT/OUTPUT" );
    }
    KSIOMessage::~KSIOMessage()
    {
    }

    KSIOMessage& iomsg = *(siomsg.fAddress);
}
