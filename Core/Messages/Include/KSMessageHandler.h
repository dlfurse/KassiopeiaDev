#ifndef KSMESSAGEHANDLER_H_
#define KSMESSAGEHANDLER_H_

#include "Rtypes.h"

#include <iostream>
using std::ostream;

namespace Kassiopeia
{

    class KSLog;
    class KSCommand;
    class KSMessage;

    class KSMessageHandler
    {
            //****************
            //singleton system
            //****************

        public:
            static KSMessageHandler* GetInstance();

        private:
            KSMessageHandler();
            ~KSMessageHandler();
            static KSMessageHandler* fInstance;

            //*******************
            //behavioral settings
            //*******************

        public:
            void Record( const KSMessage* aMessage );

            void SetTerminalVerbosity( const UInt_t aSeverity );
            void SetLogVerbosity( const UInt_t aSeverity );
            void SetLog( KSLog* aLog );
            void SetError( KSCommand* anError );

        private:
            UInt_t fTerminalVerbosity;
            UInt_t fLogVerbosity;

            KSLog* fLog;

            KSCommand* fError;
    };

    inline void KSMessageHandler::SetTerminalVerbosity( const UInt_t aSeverity )
    {
        fTerminalVerbosity = aSeverity;
        return;
    }
    inline void KSMessageHandler::SetLogVerbosity( const UInt_t aSeverity )
    {
        fLogVerbosity = aSeverity;
        return;
    }

    inline void KSMessageHandler::SetLog( KSLog* aLog )
    {
        fLog = aLog;
        return;
    }

    inline void KSMessageHandler::SetError( KSCommand* anError )
    {
        fError = anError;
        return;
    }

}
#endif
