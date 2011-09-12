#ifndef KSMESSAGE_H_
#define KSMESSAGE_H_

#include "Rtypes.h"

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

    class KSMessage
    {
        public:
            class NewLine;
            class End;

        public:
            KSMessage();
            virtual ~KSMessage();

        public:
            virtual const string& GetKey() = 0;
            virtual void SetTerminalVerbosity( const KSMessageSeverity aSeverity ) = 0;
            virtual void SetLogVerbosity( const KSMessageSeverity aSeverity ) = 0;
    };

}

#endif /* KSMESSAGE_H_ */
