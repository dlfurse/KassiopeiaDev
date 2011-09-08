/*
 * KSIOMessage.h
 *
 * created on: Sep 6, 2011
 * author: dlfurse
 */

#ifndef KSIOMESSAGE_H_
#define KSIOMESSAGE_H_

#include "KSMessage.h"

namespace Kassiopeia
{

    typedef KSMessageSystem< class KSIOSystem > KSIOMessage;

    extern KSIOMessage iomsg;

}

#endif /* KSIOMESSAGE_H_ */
