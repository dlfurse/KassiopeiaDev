#ifndef KSMESSAGESYSTEM_H_
#define KSMESSAGESYSTEM_H_

#include "KSMessage.h"

#include <iostream>
using std::cout;
using std::endl;

namespace Kassiopeia
{

    class KSMessageNewline;
    extern KSMessageNewline ret;

    class KSMessageEnd;
    extern KSMessageEnd end;

    template< class XSystem >
    class KSMessageSystem :
        public KSMessage
    {
        public:
            KSMessageSystem()
            {
            }
            virtual ~KSMessageSystem()
            {
            }

        public:
            virtual const string& GetKey()
            {
                return fKey;
            }
            virtual void SetTerminalVerbosity( const KSMessageSeverity aSeverity )
            {
                fTerminalVerbosity = aSeverity;
                return;
            }
            virtual void SetLogVerbosity( const KSMessageSeverity aSeverity )
            {
                fLogVerbosity = aSeverity;
                return;
            }

        private:
            static string fKey;
            static string fTerminalVerbosity;
            static string fLogVerbosity;

        public:
            KSMessageSystem& operator=( const KSMessageSeverity aSeverity )
            {
                fSeverity = aSeverity;
                return *this;
            }

            template< class XPrintable >
            KSMessageSystem& operator<( const XPrintable& aFragment )
            {
                fOrigin.clear();
                fOrigin.str( "" );
                fOrigin << aFragment;
                return *this;
            }

            template< class XPrintable >
            KSMessageSystem& operator<<( const XPrintable& aFragment )
            {
                fLine << aFragment;
                return *this;
            }

            KSMessageSystem& operator<<( const KSMessageNewline& )
            {
                fMessage.push_back( fLine.str() );
                fLine.clear();
                fLine.str( "" );
                return *this;
            }

            KSMessageSystem& operator<<( const KSMessageEnd& )
            {
                fMessage.push_back( fLine.str() );
                fLine.clear();
                fLine.str( "" );

                if( fSeverity <= fTerminalVerbosity )
                {
                    cout << fTopLine << '\n';
                    for( vector<string>::iterator It = fMessage.begin(); It != fMessage.end(); It++ )
                    {
                        cout << fPrefix << *It << fSuffix << '\n';
                    }
                    cout << fBottomLine << '\n';
                }

                if( fSeverity <= fLogVerbosity )
                {
                    cout << fTopLine << '\n';
                    for( vector<string>::iterator It = fMessage.begin(); It != fMessage.end(); It++ )
                    {
                        cout << fPrefix << *It << fSuffix << '\n';
                    }
                    cout << fBottomLine << '\n';
                }

                while( !fMessage.empty() )
                {
                    fMessage.pop_back();
                }
                return *this;
            }

        private:
            KSMessageSeverity fSeverity;
            stringstream fOrigin;
            stringstream fLine;
            vector< string > fMessage;

        private:
            static string fTopLine;
            static string fPrefix;
            static string fSuffix;
            static string fBottomLine;

            /*
             static string fErrorTerminalPrefix;
             static string fErrorTerminalSuffix;

             static string fWarningTerminalPrefix;
             static string fWarningTerminalSuffix;

             static string fMessageTerminalPrefix;
             static string fMessageTerminalSuffix;

             static string fDebugTerminalPrefix;
             static string fDebugTerminalSuffix;
             */
    };

    template< class XSystem >
    string KSMessageSystem< XSystem >::fTopLine = string( "**********" );
    template< class XSystem >
    string KSMessageSystem< XSystem >::fPrefix = string( "" );
    template< class XSystem >
    string KSMessageSystem< XSystem >::fSuffix = string( "" );
    template< class XSystem >
    string KSMessageSystem< XSystem >::fBottomLine = string( "**********" );

}

#endif
