#ifndef KLMessageManager_h
#define KLMessageManager_h

/**
 @file
 @brief contains KLMessageManager
 @details
 <b>Revision History:</b>
 \verbatim
 Date         Name          Brief description
 -----------------------------------------------
 25/03/2010   N. Oblath     First version
 14/03/2011   N. Oblath     Converted KSExceptionManager to KLMessageManager
 \endverbatim

 */

/*!
 * @class Kassiopeia::KLMessageManager
 @author N. Oblath

 @brief Coordinates the printing of messages to the terminal and log file

 @details
 <b>Detailed Description:</b><br>
 The message manager is responsible for:
 - Holding a map of the instances of classes derived from KLMessageBase (each one defines a message system and is responsible for
 the actual printing and verbosity checking.
 - Holding a map of the string-keyed integer values of all severities from each message system.
 - Receiving setup information from the CoreManager.
 - Passing information to the KLManagerBase-derived objects.
 - Creating and deleting the instance of KSLog, and starting and stopping the log writing.

 Whether or not the log/error files are printed to is controled by the flag fWriteLogFlag.

 */

#include "KLMessageBase.h"

#include "Rtypes.h"

#include <string>
#include <map>

namespace Kassiopeia
{

    class KLMessageSeverity;
    //class KSCoreManager;
    class KSCommand;
    class KSLog;

    class KLMessageManager
    {

        public:
            typedef std::map< string, KLMessageBase* > MessageMap;
            typedef MessageMap::value_type MessageMapEntry;
            typedef MessageMap::iterator MessageMapIterator;

            typedef std::map< string, Int_t > SeverityMap;
            typedef SeverityMap::value_type SeverityMapEntry;
            typedef SeverityMap::iterator SeverityMapIterator;

        public:
            friend class KLMessage;

        public:
            virtual ~KLMessageManager();

            static KLMessageManager* GetInstance();

            void RegisterMessage( KLMessageBase* aMI );
            void RemoveMessage( const string& aType );

            void AddSeverityValue( const string& aSLabel, Int_t aSeverity );

            //void SetCoreManager(KSCoreManager* aCoreManager);
            void SetForceExitCommand( KSCommand* aCommand );
            void SetVerbosity( const string& v );
            void SetWriteLogFlag( Bool_t f );
            void SetDebugFlag( const string& d, Bool_t f );

            Int_t GetNMessagesRegistered() const;
            Int_t GetVerbosity() const;
            Bool_t GetWriteLogFlag() const;
            Bool_t GetKLMessageIsReady() const;
            KSLog* GetLog() const;
            //KSCoreManager* GetCoreManager() const;
            //Bool_t GetDebugFlag(const string& d);

            void ForceExit();

            void StartLog();
            void EndLog();

        private:
            void SetKLMessageIsReady( Bool_t aFlag );

        private:
            // Singleton class setup
            KLMessageManager();
            static KLMessageManager* fInstance;

            //KSCoreManager* fCoreManager;
            KSCommand* fForceExitCommand;

            Int_t fVerbosity;

            KSLog* fLog;
            Bool_t fWriteLogFlag;

            Bool_t fKLMessageIsReady;

            MessageMap fMessageMap;
            SeverityMap fSeverityMap;

    };

    inline Int_t KLMessageManager::GetNMessagesRegistered() const
    {
        return fMessageMap.size();
    }

    inline Int_t KLMessageManager::GetVerbosity() const
    {
        return fVerbosity;
    }

    inline Bool_t KLMessageManager::GetWriteLogFlag() const
    {
        return fWriteLogFlag;
    }

    inline KSLog* KLMessageManager::GetLog() const
    {
        return fLog;
    }
    /*
     inline KSCoreManager* KLMessageManager::GetCoreManager() const
     {
     return fCoreManager;
     }
     */
    inline Bool_t KLMessageManager::GetKLMessageIsReady() const
    {
        return fKLMessageIsReady;
    }

    inline void KLMessageManager::SetKLMessageIsReady( Bool_t aFlag )
    {
        fKLMessageIsReady = aFlag;
        return;
    }

} // end Kassiopeia namespace

#endif // KLMessageManager_h
