#ifndef KSMESSAGE_H_
#define KSMESSAGE_H_

#include "Rtypes.h"

#include "KSMessageHandler.h"

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <sstream>
using std::stringstream;

#include <map>
using std::map;

namespace Kassiopeia
{

    typedef enum
    {
        eError = 0, eWarning = 1, eMessage = 2, eDebug = 3
    } KSMessageSeverity;
    class KSMessageNewline;
    class KSMessageEnd;

    class KSMessage
    {
        public:
            friend class KSMessageHandler;

        public:
            class NewLine;
            class End;

        public:
            KSMessage();
            virtual ~KSMessage();

            virtual const KSMessageSeverity& GetTerminalVerbosity() const = 0;
            virtual const KSMessageSeverity& GetLogVerbosity() const = 0;

            virtual const string& GetPrefix() const = 0;
            virtual const string& GetSuffix() const = 0;

            KSMessage& operator=( const KSMessageSeverity );

            template< class XPrintable >
            KSMessage& operator<( const XPrintable& aFragmant );

            template< class XPrintable >
            KSMessage& operator<<( const XPrintable& aFragment );

            KSMessage& operator<<( const KSMessageNewline& );
            KSMessage& operator<<( const KSMessageEnd& );

        private:
            KSMessageSeverity fSeverity;
            stringstream fOrigin;
            stringstream fLine;
            vector< string > fMessage;

            static const string fPrefix;
            static const string fSuffix;
    };

    inline KSMessage& KSMessage::operator =( const KSMessageSeverity aSeverity )
    {
        fSeverity = aSeverity;
        return *this;
    }

    template< class XPrintable >
    inline KSMessage& KSMessage::operator <( const XPrintable& aFragment )
    {
        fOrigin.clear();
        fOrigin.str( "" );
        fOrigin << aFragment;
        return *this;
    }

    template< class XPrintable >
    inline KSMessage& KSMessage::operator <<( const XPrintable& aFragment )
    {
        fLine << aFragment;
        return *this;
    }

    extern KSMessageNewline ret;

    inline KSMessage& KSMessage::operator <<( const KSMessageNewline& )
    {
        fMessage.push_back( fLine.str() );
        fLine.clear();
        fLine.str( "" );
        return *this;
    }

    extern KSMessageEnd end;

    inline KSMessage& KSMessage::operator <<( const KSMessageEnd& )
    {
        fMessage.push_back( fLine.str() );
        fLine.clear();
        fLine.str( "" );

        KSMessageHandler::GetInstance()->Record( this );

        while( !fMessage.empty() )
        {
            fMessage.pop_back();
        }
        return *this;
    }

    //

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

            using KSMessage::operator=;

            virtual const KSMessageSeverity& GetTerminalVerbosity() const
            {
                return fTerminalVerbosity;
            }
            virtual const KSMessageSeverity& GetLogVerbosity() const
            {
                return fLogVerbosity;
            }

            virtual const string& GetPrefix() const
            {
                return fPrefix;
            }
            virtual const string& GetSuffix() const
            {
                return fSuffix;
            }

        private:
            static KSMessageSeverity fTerminalVerbosity;
            static KSMessageSeverity fLogVerbosity;
            static string fPrefix;
            static string fSuffix;
    };

    template< class XSystem >
    KSMessageSeverity KSMessageSystem< XSystem >::fTerminalVerbosity = eWarning;
    template< class XSystem >
    KSMessageSeverity KSMessageSystem< XSystem >::fLogVerbosity = eWarning;
    template< class XSystem >
    string KSMessageSystem< XSystem >::fPrefix = string( "" );
    template< class XSystem >
    string KSMessageSystem< XSystem >::fSuffix = string( "" );

}

#endif /* KSMESSAGE_H_ */
