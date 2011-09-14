#ifndef KSMESSAGE_H_
#define KSMESSAGE_H_

#include "Rtypes.h"

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <sstream>
using std::stringstream;

#include <iostream>
using std::cout;
using std::endl;

namespace Kassiopeia
{

    class KSTextFile;

    typedef UInt_t KSMessageSeverity;
    class KSMessageNewline
    {
    };
    class KSMessageEnd
    {
    };

    extern const KSMessageSeverity eError;
    extern const KSMessageSeverity eWarning;
    extern const KSMessageSeverity eNormal;
    extern const KSMessageSeverity eDebug;
    extern const KSMessageNewline ret;
    extern const KSMessageEnd end;

    class KSMessage
    {
        public:
            KSMessage( const string& aKey );
            virtual ~KSMessage();

        private:
            KSMessage();

            //**************
            //identification
            //**************

        public:
            const string& GetKey();

        protected:
            string fKey;

            //*********
            //interface
            //*********

        public:
            KSMessage& operator+( const KSMessageSeverity& aSeverity );

            KSMessage& operator<( const KSMessageEnd& );
            template< class XPrintable >
            KSMessage& operator<( const XPrintable& aFragment )
            {
                fOriginBuffer << aFragment;
                return *this;
            }

            KSMessage& operator<<( const KSMessageNewline& );
            KSMessage& operator<<( const KSMessageEnd& );
            template< class XPrintable >
            KSMessage& operator<<( const XPrintable& aFragment )
            {
                fLineBuffer << aFragment;
                return *this;
            }

        protected:
            string fSystemDescription;
            string fSystemPrefix;
            string fSystemSuffix;

            string fTopSeparator;
            string fBottomSeparator;

            string fErrorColorPrefix;
            string fErrorColorSuffix;
            string fErrorDescription;

            string fWarningColorPrefix;
            string fWarningColorSuffix;
            string fWarningDescription;

            string fNormalColorPrefix;
            string fNormalColorSuffix;
            string fNormalDescription;

            string fDebugColorPrefix;
            string fDebugColorSuffix;
            string fDebugDescription;

            string fDefaultColorPrefix;
            string fDefaultColorSuffix;
            string fDefaultDescription;

        private:
            KSMessageSeverity fSeverity;
            string fPrefix;
            string fSuffix;

            stringstream fDescriptionBuffer;
            string fDescription;

            stringstream fOriginBuffer;
            string fOrigin;

            stringstream fLineBuffer;
            vector< string > fLines;

            //********
            //settings
            //********

        public:
            void SetTerminalVerbosity( KSMessageSeverity aVerbosity );
            void SetLogVerbosity( KSMessageSeverity aVerbosity );
            void SetLogFile( KSTextFile* aLogFile );

        private:
            KSMessageSeverity fTerminalVerbosity;
            KSMessageSeverity fLogVerbosity;
            KSTextFile* fLogFile;
    };

}

#endif /* KSMESSAGE_H_ */
