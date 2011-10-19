#include "KSIOMessage.h"
#include "KSIOToolbox.h"

namespace Kassiopeia
{

    KSIOMessage::KSIOMessage() :
        KSMessage()
    {
        fKey = string( "IO" );
        fSystemDescription = string( "INPUT/OUTPUT" );
        KSIOToolbox::GetInstance()->AddMessage( this );
    }
    KSIOMessage::~KSIOMessage()
    {
        KSIOToolbox::GetInstance()->RemoveMessage( this );
    }

    KSIOMessage& iomsg = *(siomsg.fAddress);
}
