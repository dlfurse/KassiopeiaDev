#include "KSMessageHandler.h"

#include "KSMessage.h"
#include "KSLog.h"
#include "KSCommand.h"

#include <iostream>
using std::cout;
using std::endl;

#include <cstdlib>

namespace Kassiopeia
{

    KSMessageHandler* KSMessageHandler::fInstance = NULL;
    KSMessageHandler* KSMessageHandler::GetInstance()
    {
        if( fInstance == NULL )
        {
            fInstance = new KSMessageHandler();
        }
        return fInstance;
    }

    KSMessageHandler::KSMessageHandler() :
        fTerminalVerbosity( 1 ),
        fLogVerbosity( 1 ),
        fLog( NULL ),
        fError( NULL )
    {
    }

    KSMessageHandler::~KSMessageHandler()
    {
    }

    void KSMessageHandler::Record( const KSMessage* aMessage )
    {
        if( (aMessage->fSeverity <= fTerminalVerbosity) && (aMessage->fSeverity <= aMessage->GetTerminalVerbosity()) )
        {
            cout.precision( 20 );

            cout << aMessage->GetPrefix();
            cout << "***************";
            cout << aMessage->GetSuffix();
            cout << "\n";

            cout << aMessage->GetPrefix();
            cout << "MESSAGE LEVEL " << aMessage->fSeverity;
            cout << aMessage->GetSuffix();
            cout << "\n";

            cout << aMessage->GetPrefix();
            cout << "ORIGIN: " << aMessage->fOrigin.str();
            cout << aMessage->GetSuffix();
            cout << "\n";

            for( UInt_t Line = 0; Line < aMessage->fMessage.size(); Line++ )
            {
                cout << aMessage->GetPrefix();
                cout << aMessage->fMessage.at( Line );
                cout << aMessage->GetSuffix();
                cout << "\n";
            }

            cout << aMessage->GetPrefix();
            cout << "***************";
            cout << aMessage->GetSuffix();
            cout << "\n";
        }

        if( fLog != NULL )
        {

            if( (aMessage->fSeverity <= fLogVerbosity) && (aMessage->fSeverity <= aMessage->GetLogVerbosity()) )
            {
                ostream& LogStream = fLog->LogStream();

                LogStream << aMessage->GetPrefix();
                LogStream << "***************";
                LogStream << aMessage->GetSuffix();
                LogStream << "\n";

                LogStream << aMessage->GetPrefix();
                LogStream << "MESSAGE LEVEL " << aMessage->fSeverity;
                LogStream << aMessage->GetSuffix();
                LogStream << "\n";

                LogStream << aMessage->GetPrefix();
                LogStream << "ORIGIN: " << aMessage->fOrigin;
                LogStream << aMessage->GetSuffix();
                LogStream << "\n";

                for( UInt_t Line = 0; Line < aMessage->fMessage.size(); Line++ )
                {
                    cout << aMessage->GetPrefix();
                    cout << aMessage->fMessage.at( Line );
                    cout << aMessage->GetSuffix();
                    cout << "\n";
                }

                LogStream << aMessage->GetPrefix();
                LogStream << "***************";
                LogStream << aMessage->GetSuffix();
                LogStream << "\n";
            }

            if( aMessage->fSeverity == 0 )
            {
                ostream& ErrorStream = fLog->ErrorStream();

                ErrorStream << aMessage->GetPrefix();
                ErrorStream << "***************";
                ErrorStream << aMessage->GetSuffix();
                ErrorStream << "\n";

                ErrorStream << aMessage->GetPrefix();
                ErrorStream << "MESSAGE LEVEL " << aMessage->fSeverity;
                ErrorStream << aMessage->GetSuffix();
                ErrorStream << "\n";

                ErrorStream << aMessage->GetPrefix();
                ErrorStream << "ORIGIN: " << aMessage->fOrigin;
                ErrorStream << aMessage->GetSuffix();
                ErrorStream << "\n";

                for( UInt_t Line = 0; Line < aMessage->fMessage.size(); Line++ )
                {
                    cout << aMessage->GetPrefix();
                    cout << aMessage->fMessage.at( Line );
                    cout << aMessage->GetSuffix();
                    cout << "\n";
                };

                ErrorStream << aMessage->GetPrefix();
                ErrorStream << "***************";
                ErrorStream << aMessage->GetSuffix();
                ErrorStream << "\n";
            }
        }

        if( aMessage->fSeverity == 0 )
        {
            if( fError != NULL )
            {
                fError->Execute();
            }
            exit( -1 );
        }

        return;
    }

} /* namespace Kassiopeia */
