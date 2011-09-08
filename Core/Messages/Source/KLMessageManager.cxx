/*
 Class: KLMessageManager
 Author: N. Oblath

 For full class documentation: KLMessageManager.h

 Revision History
 Date         Name          Brief description
 -----------------------------------------------
 25/03/2010   N. Oblath     First version
 01/07/2010   N. Oblath     Added responsibility for the log file
 14/03/2011   N. Oblath     Converted KSExceptionManager to KLMessageManager

 */

#include "KLMessageManager.h"
#include "KLMessage.h"

//#include "KSCoreManager.h"
#include "KSCommand.h"
#include "KSLog.h"

#include <cstdlib>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

namespace Kassiopeia
{

    KLMessageManager* KLMessageManager::fInstance = NULL;

    // Private constructor
    KLMessageManager::KLMessageManager() :
        fForceExitCommand( NULL ), fVerbosity( 3 ), fLog( KSLog::GetInstance() ), fWriteLogFlag( kFALSE ), fKLMessageIsReady( kFALSE ), fMessageMap(), fSeverityMap()
    {
        //cout << "KLMessageManager constructor" << endl;
    }

    KLMessageManager::~KLMessageManager()
    {

        for( MessageMapIterator tIter = fMessageMap.begin(); tIter != fMessageMap.end(); tIter++ )
        {
            delete tIter->second;
            fMessageMap.erase( tIter );
        }

        fLog->DeleteInstance();

        fInstance = NULL;

    }

    KLMessageManager* KLMessageManager::GetInstance()
    {
        if( !fInstance ) fInstance = new KLMessageManager();
        return fInstance;
    }

    void KLMessageManager::RegisterMessage( KLMessageBase* aMI )
    {
#ifdef DEBUG_VERBOSE
        cout << "KLMessageManager::RegisterMessage: Registering a message with type <" << aMI->GetType() << ">" << endl;
#endif
        MessageMapIterator tIter = fMessageMap.find( aMI->GetType() );
        if( tIter != fMessageMap.end() )
        {
#ifndef SILENT_MODE
            cerr << "Fatal error from KLMessageManager::RegisterMessage: Already have a message with type <" << aMI->GetType() << "> !!!" << endl;
#endif
            exit( -1 );
        }
        fMessageMap.insert( MessageMapEntry( aMI->GetType(), aMI ) );

        // Request severities from the Message
        aMI->TransferSeverityValues();

        return;
    }

    void KLMessageManager::RemoveMessage( const string& aType )
    {
        MessageMapIterator tIter = fMessageMap.find( aType );
        if( tIter == fMessageMap.end() )
        {
            if( fKLMessageIsReady )
            {
                klmsg < "KLMessageManager::RemoveMessage";
                klmsg( KLMessage::eWarning ) << "Did not find message of type <" << aType << "> during removal attempt." << eom;
            }
            else
            {
#ifndef SILENT_MODE
                cout << "Warning (KLMessageManager::RemoveMessage): Did not find message of type <" << aType << "> during removal attempt." << endl;
#endif
            }

            return;
        }
        fMessageMap.erase( tIter );
        if( aType == string( "KLMessage" ) ) fKLMessageIsReady = kFALSE;
        return;
    }

    //**********

    void KLMessageManager::AddSeverityValue( const string& aSLabel, Int_t aSeverity )
    {
        SeverityMapIterator tSMIter = fSeverityMap.find( aSLabel );
        if( tSMIter != fSeverityMap.end() )
        {
            if( tSMIter->second != aSeverity && tSMIter->second >= 0 && aSeverity >= 0 )
            {
#ifndef SILENT_MODE
                cerr << "Fatal error in KLMessageManager::AddMessageSeverity: The same severity labels in different interfaces with different severities!" << '\n';
                cerr << "Previously registered in this manager: <" << tSMIter->first << "> = <" << tSMIter->second << ">" << '\n';
                cerr << "Trying to register: <" << aSLabel << "> = <" << aSeverity << ">" << endl;
#endif
                exit( -1 );
            }
            return;
        }
        fSeverityMap.insert( SeverityMapEntry( aSLabel, aSeverity ) );
        return;
    }

    //**********

    //! Finds the string-keyed severity in one of the message systems, and uses the integer-equivalant of the severity
    //! to set the severity in each message system.s
    void KLMessageManager::SetVerbosity( const string& v )
    {
        SeverityMapIterator tSMIter = fSeverityMap.find( v );
        if( tSMIter != fSeverityMap.end() )
        {
            fVerbosity = tSMIter->second;
            for( MessageMapIterator tMMIter = fMessageMap.begin(); tMMIter != fMessageMap.end(); tMMIter++ )
            {
                tMMIter->second->SetVerbosity( tSMIter->second );
            }
            return;
        }
        klmsg < "KLMessageManager::SetVerbosity";
        klmsg( KLMessage::eError ) << "Unknown verbosity: " << v << eom;
        return;
    }

    void KLMessageManager::SetWriteLogFlag( Bool_t aFlag )
    {
        Bool_t tFormerFlag = fWriteLogFlag;

        if( !tFormerFlag && aFlag )
        {
            if( fKLMessageIsReady )
            {
                klmsg < "KLMessageManager::SetWriteLogFlag";
                klmsg( KLMessage::eMessage1 ) << "Log-writing flag set to TRUE;\n";
                klmsg << "Actual log writing will begin when KLMessageManager::StartLog() is called" << eom;
            }
            else
            {
#ifndef SILENT_MODE
                cout << "KLMessageManager::SetWriteLogFlag: Log-writing flag set to TRUE;\n";
                cout << "Actual log writing will begin when KLMessageManager::StartLog() is called" << endl;
#endif
            }
        }
        if( tFormerFlag && !aFlag ) EndLog();

        // Do the actual assigning of the flag after the message above, to avoid log warnings when turning it on.
        fWriteLogFlag = aFlag;
        for( MessageMapIterator tMMIter = fMessageMap.begin(); tMMIter != fMessageMap.end(); tMMIter++ )
        {
            tMMIter->second->SetWriteLogFlag( aFlag );
        }

        return;
    }

    //**********

    void KLMessageManager::SetDebugFlag( const string& d, Bool_t f )
    {
        Bool_t tCheck = kFALSE;
        for( MessageMapIterator tIter = fMessageMap.begin(); tIter != fMessageMap.end(); tIter++ )
        {
            Bool_t tSetResult = tIter->second->SetDebugFlag( d, f );
            tCheck = tCheck || tSetResult;
        }
        if( !tCheck )
        {
            if( fKLMessageIsReady )
            {
                klmsg < "KLMessageManager::SetDebugFlag";
                klmsg( KLMessage::eError ) << "Unknown debug type: " << d << eom;
            }
            else
            {
#ifndef SILENT_MODE
                cout << "Error (KLMessageManager::SetDebugFlag): Unknown debug type: " << d << endl;
#endif
            }

            return;
        }
        return;
    }
    /*
     Bool_t KLMessageManager::GetDebugFlag(const string& d)
     {
     DebugScopeFlagMapIterator tIter = fDebugScopeFlagMap.find(d);
     if (tIter == fDebugScopeFlagMap.end())
     {
     // Do not switch this to using klmsg (even optionally). To do so risks an infinite loop if processing ends up
     // in this block when being called from KLMessageSeverity::PrintDebug.
     cout << "Error (KLMessageManager::GetDebugFlag): Unknown debug type: " << d << endl;
     return kFALSE;
     }
     return tIter->second;
     }
     */

    //*************
    /*
     void KLMessageManager::SetCoreManager(KSCoreManager* aCoreManager)
     {
     fCoreManager = aCoreManager;
     return;
     }
     */
    void KLMessageManager::SetForceExitCommand( KSCommand* aCommand )
    {
        fForceExitCommand = aCommand;
        return;
    }

    //*************

    void KLMessageManager::ForceExit()
    {
        //if (fCoreManager) fCoreManager->ShutdownApplication();
        if( fForceExitCommand ) fForceExitCommand->Execute();
        exit( -1 );
    }

    void KLMessageManager::StartLog()
    {
        if( fWriteLogFlag )
        {
            fLog->StartLog();
            fLog->StartError();
        }
        return;
    }

    void KLMessageManager::EndLog()
    {
        fLog->EndError();
        fLog->EndLog();
        return;
    }

} // end Kassiopeia namespace
