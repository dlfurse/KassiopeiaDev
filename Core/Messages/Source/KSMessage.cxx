/*
 * KSMessage.cxx
 *
 * created on: Jul 20, 2011
 * author: dlfurse
 */

#include "KSMessage.h"

#include "KSMessageHandler.h"

namespace Kassiopeia
{

    KSMessage::KSMessage() :
        fSeverity(eWarning),
        fOrigin(),
        fLine(),
        fMessage()
    {
        fLine.precision(20);
    }
    KSMessage::~KSMessage()
    {
    }

}
