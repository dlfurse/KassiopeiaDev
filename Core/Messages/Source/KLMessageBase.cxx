/*
 Class: KLMessageBase
 Author: N. Oblath
 
 For full class documentation: KLMessageBase.h
 
 Revision History
 Date         Name          Brief description
 -----------------------------------------------
 16/03/2011   N. Oblath     First version
 
 */

#include "KLMessageBase.h"

#include "KLMessageManager.h"

#include <cstdlib>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

namespace Kassiopeia {
    
    KLEndOfMessage eom;
    KLEndOfLine newline;

    
    KLMessageBase::KLMessageBase() : 
    fDebugMap(),
    fMessageManager(KLMessageManager::GetInstance()),
    fLog(NULL),
    fVerbosity(0),
    fWriteLogFlag(kFALSE)
    {
        //cout << "KLMessageBase constructor" << endl;

        fLog = fMessageManager->GetLog();
        fVerbosity = fMessageManager->GetVerbosity();
        fWriteLogFlag = fMessageManager->GetWriteLogFlag();        
    }
    
    KLMessageBase::KLMessageBase(const KLMessageBase& copy) :
    fDebugMap(copy.fDebugMap),
    fMessageManager(copy.fMessageManager),
    fLog(copy.fLog),
    fVerbosity(copy.fVerbosity),
    fWriteLogFlag(copy.fWriteLogFlag)
    {
    }
        
    KLMessageBase::~KLMessageBase()
    {
    }
    
    //**********
	
    Bool_t KLMessageBase::SetDebugFlag(const string& d, Bool_t f)
    {
        DebugScopeFlagMapIterator tIter = fDebugMap.find(d);
        if (tIter == fDebugMap.end())
        {
            return kFALSE;
        }
        tIter->second = f;
        return kTRUE;
    }
    
    Bool_t KLMessageBase::GetDebugFlag(const string& d) const
    {
        DebugScopeFlagMap::const_iterator tIter = fDebugMap.find(d);
        if (tIter == fDebugMap.end())
        {
            // Do not switch this to using klmsg (even optionally). To do so risks an infinite loop if processing ends up
            // in this block when being called from KLMessageSeverity::PrintDebug.
            #ifndef SILENT_MODE
            cout << "Error (KLMessageManager::GetDebugFlag): Unknown debug type: " << d << endl;
            #endif
            return kFALSE;
        }
        return tIter->second;
        
    }
    
    //**********
	    
    void KLMessageBase::AddDebugScope(const string& aScope)
    {
        DebugScopeFlagMapIterator tDSFMIter = fDebugMap.find(aScope);
        if (tDSFMIter == fDebugMap.end())
        {
            fDebugMap.insert(DebugScopeFlagMapEntry(aScope, kFALSE));
        }
        return;
    }
    
    
    //*****************************************************************
    //*****************************************************************
    //*****************************************************************
    
    
    KLMessageInterfaceBase::KLMessageInterfaceBase() : 
    fOrigin(string("")),
    fMessage(string(""))
    {
        //cout << "KLMessageInterfaceBase constructor" << endl;
    }
    
    KLMessageInterfaceBase::~KLMessageInterfaceBase()
    {
    }
        
    
    //*****************************************************************
    //*****************************************************************
    //*****************************************************************
    
    
    KLEndOfMessage::KLEndOfMessage()
    {
        //cout << "KLEndOfMessage constructor" << endl;
    }
    
    KLEndOfMessage::~KLEndOfMessage()
    {
    }

    
    //*****************************************************************
    //*****************************************************************
    //*****************************************************************
    
    
    KLEndOfLine::KLEndOfLine()
    {
        //cout << "KLEndOfLine constructor" << endl;
    }
    
    KLEndOfLine::~KLEndOfLine()
    {
    }
    
    
} // end Kassiopeia namespace
