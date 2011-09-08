#ifndef KLMessage_h
#define KLMessage_h

/**
 @file
 @brief contains KLMessage and KLMessageInterface

 @details
 This file, and the accompanying .cxx file, comprise the implementation of the KLMessage system.

 KLMessage is responsible for the printing to the terminal and log file.

 KLMessageInterface defines the interface used by the user.

 See KLMessageInitializer.h for information about KLMessageInitializer.

 <b>Revision History:</b>
 \verbatim
 Date         Name          Brief description
 -----------------------------------------------
 15/03/2011   N. Oblath     First version
 29/04/2011   N. Oblath     KLMessageInitializer definition moved to a separate header file
 \endverbatim

 */

#include "KLMessageInitializer.h"

#include "KLMessageBase.h"

#include "Rtypes.h"

#include <string>
using std::string;

namespace Kassiopeia
{

    /*!
     @class Kassiopeia::KLMessage
     @author N. Oblath

     @brief Class for printing messages to the terminal and log

     @details
     Severities, integer equivalents, and string keys used in KLMessages:
     Severity     Int  String
     ------------------------------
     eFatalError  0    FatalError
     eError       1    Error
     eWarning     2    Warning
     eMessage1    3    Message1
     eMessage2    4    Message2
     eMessage3    5    Message3
     eMessage4    6    Message4

     Debug categories, integer equivalents, string keys, and usage notes
     Severity     Int  String      Usage
     ------------------------------------------------
     eDebug       -1   Debug       General use, anywhere there isn't another debug category defined
     eCoreDebug   -2   CoreDebug   For core parts of the code (management, builders, etc)
     eInitDebug   -3   InitDebug   For static initialization (e.g. factories, message systems, etc); The flag is set to kTRUE by default because static initialization happens before the flag could be set by a config file.
     eIODebug     -4   IODebug     For IO classes

     In the enum list, the integer equivalents must be sequential.  Message severities are positive, and debug categories are
     negative.  The integer equivalents of the debug categories must be explictely stated, as automatic counting of the
     negative integers is not automatic.  The list must start with _start_of_list_ (with its integer value defined explicitely)
     and end with _end_of_list_.  Neither is a valid message severity.

     The severities and associated information are stored in an array of KLSeverityInfo struct instances.  The positions in the array
     are determined by the severity, which allows for fast access to the appropriate information when a message is being printed.

     There are three printing templates: Error, Message, and Debug.  The information associated with each severity level is used
     by the appropriate template to customize the printed message (e.g. the string KLSeverityInfo::fIntroText tells PrintError() to
     say "FATAL ERROR" at the beginning of the fatal error message).
     */

    class KLMessage :
        public KLMessageBase
    {

        public:
            typedef enum
            {
                // The order of these is important!!!
                // They must be listed in order of severity, from greatest to least.
                // The first three must be eFatalError, eError, and eWarning, and there must be four types of messages after that.
                // Debug severities should come at the beginning (in any order).
                _start_of_list_ = -5, // This must be the first item defined
                eIODebug = -4,
                eInitDebug = -3,
                eCoreDebug = -2,
                eDebug = -1, // Debug categories are placed before the errors
                eFatalError = 0, // Do not use any other assignments
                eError,
                eWarning,
                eMessage1, // There must be exactly four message categories
                eMessage2,
                eMessage3,
                eMessage4,
                _end_of_list_
            // This must be the last item defined
            } Severity;

        private:
            struct KLSeverityInfo
            {
                    Severity fSeverity;
                    string fSeverityLabel;
                    string fIntroText;
                    Bool_t fCheckVerbosity;
                    Bool_t fIsFatal;
            };

        public:
            typedef void (KLMessage::*PrintFunction)( const string&, const string&, KLSeverityInfo* );

            friend class KLMessageInitializer;

        public:
            virtual ~KLMessage();

            static KLMessage* GetInstance();

            const string& GetType() const;

            void TransferSeverityValues() const;

            void ProcessMessage( Severity aSeverity, const string& anOrigin, const string& aMessage );

        private:
            // Singleton class setup
            KLMessage();
            static KLMessage* fInstance;

            static string* fType;

            Int_t fIndexOffset;
            Int_t fNSeverities;

            void RegisterSeverity( Severity aSeverity, const string& aSeverityLabel, const string& aIntroText, Bool_t aCheckVerbosity, Bool_t aIsFatal, const string& aPrintFuncType );

            void PrintError( const string& anOrigin, const string& aMessage, KLSeverityInfo* aSeverityInfo );
            void PrintMessage( const string& anOrigin, const string& aMessage, KLSeverityInfo* aSeverityInfo );
            void PrintDebug( const string& anOrigin, const string& aMessage, KLSeverityInfo* aSeverityInfo );

            KLSeverityInfo** fSeverityInfoArray;
            PrintFunction* fPrintFunctionArray;

    };

    inline const string& KLMessage::GetType() const
    {
        return *fType;
    }

    //*****************************************************************
    //*****************************************************************
    //*****************************************************************


    /*!
     @class Kassiopeia::KLMessageInterface
     @author N. Oblath

     @brief Class for the user interface to the KLMessage system.

     @details
     The KLMessage interface system is intended to give a cout-like interface for the printing of messages to the terminal and log.

     In lieu of a lengthy explanation, here are some examples:

     Code:
     \code
     klmsg < "KLMessage Demonstration";
     klmsg(KLMessage::eCoreDebug) << "This is a CoreDebug message.  This is printed with klmsg." << eom;

     klmsg < "KLMessage Demonstration";
     klmsg(KLMessage::eWarning) << "First warning!" << eom;

     klmsg < "KLMessage Demonstration";
     klmsg << "Second warning! (don't make me tell you a third time! :-)" << newline;
     klmsg << "This one has a second line." << eom;

     klmsg < "KLMessage Demonstration";
     klmsg(KLMessage::eMessage1) << "Here is a level-1 message." << eom;

     klmsg < "KLMessage Demonstration";
     klmsg(KLMessage::eMessage2) << "Here is a level-2 message." << eom;
     \endcode

     Screen output:
     \code
     DEBUG MESSAGE (KLMessage Demonstration): This is a CoreDebug message.  This is printed with klmsg.

     WARNING: First warning!
     ORIGIN: KLMessage Demonstration

     WARNING: Second warning! (don't make me tell you a third time! :-)
     This one has a second line.
     ORIGIN: KLMessage Demonstration

     MESSAGE (level 1) (KLMessage Demonstration):
     Here is a level-1 message.

     MESSAGE (level 2) (KLMessage Demonstration):
     Here is a level-2 message.
     \endcode

     Notes:
     - klmsg can be used anywhere KLMessage.h is included.
     - The < operator sets the origin of the message.  It erases the previous origin and replaces it with the one provided.  This should be done almost every time a message is printed, in case another function was called that changed the origin in the global klmsg instance.
     - The () operator is used to give the severity using the KLMessage::Severity enum.  It only needs to be done once per message.
     - The << operator adds to the message.  The message is only erased when the message is printed.
     - Using "<< newline" goes to the next line without printing the message.
     - Using "<< eom" prints the message.  It also erases the message text to prepare it for the next message.
     */

    class KLMessageInterface :
        public KLMessageInterfaceBase
    {
        public:
            friend class KLMessageInitializer;

        public:
            KLMessageInterface();
            virtual ~KLMessageInterface();

            void* operator new( size_t /*sz*/, KLMessageInterface* place );

            KLMessageInterface& operator=( KLMessage::Severity severity );
            KLMessageInterface& operator()( KLMessage::Severity severity );

            KLMessageInterface& operator<( const string& origin );

            template< class XPrintable >
            KLMessageInterface& operator<<( const XPrintable& message );

            KLMessageInterface& operator<<( const KLEndOfLine );

            KLMessageInterface& operator<<( const KLEndOfMessage );

        private:
            static KLMessage* fKLMessage;

            KLMessage::Severity fSeverity;
    };

    inline void* KLMessageInterface::operator new( size_t /*sz*/, KLMessageInterface* place )
    {
        return (void*) place;
    }

    inline KLMessageInterface& KLMessageInterface::operator=( KLMessage::Severity severity )
    {
        fSeverity = severity;
        return *this;
    }

    inline KLMessageInterface& KLMessageInterface::operator()( KLMessage::Severity severity )
    {
        fSeverity = severity;
        return *this;
    }

    inline KLMessageInterface& KLMessageInterface::operator<( const string& origin )
    {
        ClearOrigin();
        fOrigin << origin;
        return *this;
    }

    template< class XPrintable >
    inline KLMessageInterface& KLMessageInterface::operator<<( const XPrintable& message )
    {
        fMessage << message;
        return *this;
    }

    inline KLMessageInterface& KLMessageInterface::operator<<( const KLEndOfLine )
    {
        fMessage << '\n';
        return *this;
    }

    inline KLMessageInterface& KLMessageInterface::operator<<( const KLEndOfMessage )
    {
        fMessage << '\n';
        string tMessage( fMessage.str() );
        ClearMessage();
        fKLMessage->ProcessMessage( fSeverity, fOrigin.str(), tMessage );
        return *this;
    }

    extern KLMessageInterface klmsg;

} // end Kassiopeia namespace

#endif // KLMessage_h
