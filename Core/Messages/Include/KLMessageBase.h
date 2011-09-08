#ifndef KLMessageBase_h
#define KLMessageBase_h

/**
 @file
 @brief contains KLMessageBase, KLMessageInterfaceBase, KLEndOfMessage, and KLEndOfLine

 @details
 This file contains the classes (or base classes) needed to make a message system.  The intent is to create message systems that
 function very much like the cout system in the iostream library.

 To make a message system one must make derived instances of KLMessageBase and KLMessageInterfaceBase.  The former is responsible
 for performing the actual printing to the terminal and the log file, and the latter is responsible for the interface used by
 the user (i.e. the code that wants to print messages).

 KLEndOfMessage and KLEndOfLine are modifier classes that are used to end messages and end lines, respectively, during the message printing.

 If you want to make a new message system, see KLMessage.h/cxx as an example.  KSMessage.h/cxx in Kassiopeia is another example of
 a slightly different message system.  The main difference between the two is that the names of the severities are different, and
 the format of the printing is slightly different.  The rest of the interface is equivalent between the two.

 Severity levels are defined with enums.  Other details that accompany the severity level (like the severity string) are
 defined in the constructor of the KLMessageBase-derived class.

 It is important that any new message system be compatible with KLMessage.  The severity levels should be essentially equivalent,
 even if they're renamed.  There is only one verbosity level, so it should be useable in KLMessage and any other message system
 simultaneously.

 Comparing KLMessage and KSMessage, though they are defined in independent enums, the integer equivalents compare as follows:
 KLMessage::eFatalError = KSMessage::eFatalError
 KLMessage::eError      = KSMessage::eError
 KLMessage::eWarning    = KSMessage::eWarning
 KLMessage::Message1    = KSMessage::eGlobalMessage
 KLMessage::Message2    = KSMessage::eRunMessage
 KLMessage::Message3    = KSMessage::eEventMessage
 KLMessage::Message4    = KSMessage::eTrackMessage

 It is ok to add more severities after the KLMessage4 level.  Any number of debug severities can be added.  They are given
 negative-integer equivalents in the enum definition.

 <b>Revision History:</b>
 \verbatim
 Date         Name          Brief description
 -----------------------------------------------
 16/03/2011   N. Oblath     First version
 \endverbatim

 */

#include "KSLog.h"

#include "Rtypes.h"

#include <map>
#include <string>
using std::string;
#include <sstream>
using std::stringstream;

namespace Kassiopeia
{

    /*!
     @class Kassiopeia::KLMessageBase
     @author N. Oblath

     @brief Base class for message systems

     @details
     <b>Detailed Description:</b><br>
     The KLMessageBase-derived objects are responsible for the actual printing of messages to the terminal and log.

     The elements that are common between all message systems (and are therefore in this class) are:
     - Debug scope map: string-keyed by the severity string, containing a Bool_t that determines whether or not debug messages for this debug type are printed.
     - A pointer to the KSLog instance, and a copy of the WriteLogFlag
     - A copy of the verbosity level

     */

    class KLMessageManager;

    class KLMessageBase
    {

        public:
            typedef std::map< string, Bool_t > DebugScopeFlagMap;
            typedef DebugScopeFlagMap::value_type DebugScopeFlagMapEntry;
            typedef DebugScopeFlagMap::iterator DebugScopeFlagMapIterator;

        public:
            friend class KLMessageManager;
            friend class KSException;

        public:
            KLMessageBase();
            KLMessageBase( const KLMessageBase& );
            virtual ~KLMessageBase();

            virtual const string& GetType() const = 0;

            // The return value of this Set function is dependent on whether or not d was found in this Message's map.
            Bool_t SetDebugFlag( const string& d, Bool_t f );
            Bool_t GetDebugFlag( const string& d ) const;

            virtual void TransferSeverityValues() const = 0;

            virtual KSLog* GetLog() const;
            virtual Int_t GetVerbosity() const;
            virtual Bool_t GetWriteLogFlag() const;

            virtual void SetLog( KSLog* aL );
            virtual void SetVerbosity( Int_t aV );
            virtual void SetWriteLogFlag( Bool_t aFlag );

        protected:
            void AddDebugScope( const string& aScope );

            DebugScopeFlagMap fDebugMap;

            KLMessageManager* fMessageManager;
            KSLog* fLog;
            Int_t fVerbosity;
            Bool_t fWriteLogFlag;

    };

    inline KSLog* KLMessageBase::GetLog() const
    {
        return fLog;
    }

    inline Int_t KLMessageBase::GetVerbosity() const
    {
        return fVerbosity;
    }

    inline Bool_t KLMessageBase::GetWriteLogFlag() const
    {
        return fWriteLogFlag;
    }

    inline void KLMessageBase::SetLog( KSLog* aL )
    {
        fLog = aL;
        return;
    }

    inline void KLMessageBase::SetVerbosity( Int_t aV )
    {
        fVerbosity = aV;
        return;
    }

    inline void KLMessageBase::SetWriteLogFlag( Bool_t aFlag )
    {
        fWriteLogFlag = aFlag;
        return;
    }

    //*****************************************************************
    //*****************************************************************
    //*****************************************************************


    /*!
     @class Kassiopeia::KLMessageInterfaceBase
     @author N. Oblath

     @brief Base class for the interface to message systems

     @details
     <b>Detailed Description:</b><br>
     The KLMessageInterfaceBase-derived objects are used by other parts of the code for printing messages.
     The derived classes are intended to give the user a cout-like interface.

     The elements that are common between all message interfaces (and are therefore in this class) are:
     - The origin of the message
     - The message itself

     */

    class KLMessageInterfaceBase
    {
        public:
            KLMessageInterfaceBase();
            virtual ~KLMessageInterfaceBase();

            void ClearOrigin();
            void ClearMessage();

        protected:
            stringstream fOrigin;
            stringstream fMessage;
    };

    inline void KLMessageInterfaceBase::ClearOrigin()
    {
        fOrigin.str( "" );
        fOrigin.clear();
        return;
    }

    inline void KLMessageInterfaceBase::ClearMessage()
    {
        fMessage.str( "" );
        fOrigin.clear();
        return;
    }

    //*****************************************************************
    //*****************************************************************
    //*****************************************************************


    /*!
     @class Kassiopeia::KLEndOfMessage
     @author N. Oblath

     @brief Simple class acting as the end-of-message modifier

     @details
     <b>Detailed Description:</b><br>
     As the name suggests, this class is intended to act as the end of any message in a KLMessageBase-derived message system.

     The static instance eom is used just like endl in the iostream cout system.

     That usage needs to be implemented in each message system, but the implementation should be essentially the same each time.

     See KLMessageInterface in KLMessage.h for an example and documentation on usage.
     */

    class KLEndOfMessage
    {
        public:
            KLEndOfMessage();
            virtual ~KLEndOfMessage();

            void* operator new( size_t /*sz*/, KLEndOfMessage* place );
    };

    inline void* KLEndOfMessage::operator new( size_t /*sz*/, KLEndOfMessage* place )
    {
        return (void*) place;
    }

    extern KLEndOfMessage eom;

    //*****************************************************************
    //*****************************************************************
    //*****************************************************************


    /*!
     @class Kassiopeia::KLEndOfLine
     @author N. Oblath

     @brief Simple class acting as the end-of-line modifier

     @details
     <b>Detailed Description:</b><br>
     As the name suggests, this class is intended to act as the end of any line in a KLMessageBase-derived message system.

     The static instance newline is used just like endl in the iostream cout system, except that the message is not printed until KLEndOfMessage is used.

     That usage needs to be implemented in each message system, but the implementation should be essentially the same each time.

     See KLMessageInterface in KLMessage.h for an example and documentation on usage.
     */

    class KLEndOfLine
    {
        public:
            KLEndOfLine();
            virtual ~KLEndOfLine();

            void* operator new( size_t /*sz*/, KLEndOfLine* place );
    };

    inline void* KLEndOfLine::operator new( size_t /*sz*/, KLEndOfLine* place )
    {
        return (void*) place;
    }

    extern KLEndOfLine newline;

} // end Kassiopeia namespace

#endif // KLMessageBase_h
