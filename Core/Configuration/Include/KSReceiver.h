#ifndef KSRECEIVER_H_
#define KSRECEIVER_H_
/*!
 * @file KSReceiver.h
 */

#include "KSTokenEndParsing.h"
#include "KSTokenBeginFile.h"
#include "KSTokenEndFile.h"
#include "KSTokenBeginElement.h"
#include "KSTokenEndElement.h"
#include "KSTokenAttribute.h"
#include "KSTokenData.h"
#include "KSTokenError.h"

/*!
 * @class Kassiopeia::KSReceiver
 * @author Dan Furse
 *
 * @brief this class provides an interface for receiving XML tokens.
 *
 */
namespace Kassiopeia
{

    class KSReceiver
    {
        public:
            KSReceiver();
            virtual ~KSReceiver();

            virtual void ReceiveToken( const KSTokenBeginParsing* token ) = 0;
            virtual void ReceiveToken( const KSTokenEndParsing* token ) = 0;

            virtual void ReceiveToken( const KSTokenBeginFile* token ) = 0;
            virtual void ReceiveToken( const KSTokenEndFile* token ) = 0;

            virtual void ReceiveToken( const KSTokenBeginElement* token ) = 0;
            virtual void ReceiveToken( const KSTokenEndElement* token ) = 0;

            virtual void ReceiveToken( const KSTokenAttribute* token ) = 0;
            virtual void ReceiveToken( const KSTokenData* token ) = 0;

            virtual void ReceiveToken( const KSTokenError* token ) = 0;
    };

}

#endif /* KSRECEIVER_H_ */
