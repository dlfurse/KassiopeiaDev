/*
 Class: KLMessage
 Author: N. Oblath
 
 For full class documentation: KLMessage.h
 
 Revision History
 Date         Name          Brief description
 -----------------------------------------------
 15/03/2011   N. Oblath     First version
 
 */

#include "KLMessage.h"
#include "KLMessageManager.h"

#include <cstdio>
#include <cstdlib>
#include <execinfo.h>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::flush;

namespace Kassiopeia {
    
    static Int_t sKLMICounter = 0;
    
    string* KLMessage::fType = NULL;
    KLMessage* KLMessage::fInstance = NULL;

    KLMessageInterface klmsg;
    KLMessage* KLMessageInterface::fKLMessage = NULL;
    
    KLMessageInitializer::KLMessageInitializer()
    {
        //cout << "KLMessageInitializer constructor" << endl;
        if (0 == sKLMICounter++)
        {
            KLMessage::fType = new string("KLMessage");
            #ifndef SILENT_MODE
            #ifdef DEBUG_VERBOSE
            cout << "KLMessageInitializer (constructor): Setting up messaging system <" << *KLMessage::fType << ">" << endl;
            #endif
            #endif
            new (&klmsg) KLMessageInterface;
            KLMessageInterface::fKLMessage = KLMessage::GetInstance();
            new (&eom) KLEndOfMessage;
            new (&newline) KLEndOfLine;
        }
        //cout << "   sKLMICounter = " << sKLMICounter << endl;
    }
    
    KLMessageInitializer::~KLMessageInitializer()
    {
        //cout << "KLMessageInitializer destructor" << endl;
        if (0 == --sKLMICounter)
        {
            #ifndef SILENT_MODE
            #ifdef DEBUG_VERBOSE
            cout << "KLMessageInitializer (destructor): Shutting down messaging system <" << *KLMessage::fType << ">" << endl;
            #endif
            #endif
            delete KLMessageInterface::fKLMessage;
            KLMessageInterface::fKLMessage = NULL;
            
            KLMessageManager* tMM = KLMessageManager::GetInstance();
            if (tMM->GetNMessagesRegistered() == 0)
            {
                delete tMM;
            }
        }
        //cout << "   sKLMICounter = " << sKLMICounter << endl;
    }
    
    
    //*****************************************************************
    //*****************************************************************
    //*****************************************************************
    
    
    //string* KLMessage::fType = NULL;
    //KLMessage* KLMessage::fInstance = NULL;
    
    // Private constructor
    KLMessage::KLMessage() : 
    KLMessageBase()
    {
        //cout << "KLMessage constructor" << endl;
        
        // The order of these commands is important
        
        // First define fIndexOffset
        fIndexOffset = _start_of_list_ + 1;
        fNSeverities = _end_of_list_ - _start_of_list_ - 1;
        
        // Create the arrays
        fSeverityInfoArray = new KLSeverityInfo*[fNSeverities];
        fPrintFunctionArray = new PrintFunction[fNSeverities];
        for (Int_t i=0; i<fNSeverities; i++)
        {
            fSeverityInfoArray[i] = NULL;
            fPrintFunctionArray[i] = NULL;
        }
        
        // Next create the new KLMessageSeverities and Register them
        RegisterSeverity(KLMessage::eFatalError, string("FatalError"), string("FATAL ERROR"),       kFALSE, kTRUE,  string("Error"));
        RegisterSeverity(KLMessage::eError,      string("Error"),      string("ERROR"),             kFALSE, kFALSE, string("Error"));
        RegisterSeverity(KLMessage::eWarning,    string("Warning"),    string("WARNING"),           kTRUE,  kFALSE, string("Error"));
        RegisterSeverity(KLMessage::eMessage1,   string("Message1"),   string("MESSAGE (level 1)"), kTRUE,  kFALSE, string("Message"));
        RegisterSeverity(KLMessage::eMessage2,   string("Message2"),   string("MESSAGE (level 2)"), kTRUE,  kFALSE, string("Message"));
        RegisterSeverity(KLMessage::eMessage3,   string("Message3"),   string("MESSAGE (level 3)"), kTRUE,  kFALSE, string("Message"));
        RegisterSeverity(KLMessage::eMessage4,   string("Message4"),   string("MESSAGE (level 4)"), kTRUE,  kFALSE, string("Message"));
        RegisterSeverity(KLMessage::eDebug,      string("Debug"),      string("DEBUG MESSAGE"),     kFALSE, kFALSE, string("Debug"));
        RegisterSeverity(KLMessage::eCoreDebug,  string("CoreDebug"),  string("DEBUG MESSAGE"),     kFALSE, kFALSE, string("Debug"));
        RegisterSeverity(KLMessage::eInitDebug,  string("InitDebug"),  string("DEBUG MESSAGE"),     kFALSE, kFALSE, string("Debug"));        
        RegisterSeverity(KLMessage::eIODebug,    string("IODebug"),    string("DEBUG MESSAGE"),     kFALSE, kFALSE, string("Debug"));
        
        // Since this can't be set by config file before initialization, it is always set to kTRUE
        SetDebugFlag("InitDebug", kTRUE);
        
        // Finally, register this message with the MessageManager
        fMessageManager->RegisterMessage(this);
        fMessageManager->SetKLMessageIsReady(kTRUE);
    }	
    KLMessage::~KLMessage()
    {
        fMessageManager->RemoveMessage(*fType);
        fInstance = NULL;

        delete fType;
        fType = NULL;
        
        delete [] fPrintFunctionArray;
        for (Int_t i=0; i<fNSeverities; i++) delete fSeverityInfoArray[i];
        delete [] fSeverityInfoArray;
    }
    
    KLMessage* KLMessage::GetInstance()
    {
        if (! fInstance) fInstance = new KLMessage();
        return fInstance;
    }
    
    //*****************

    void KLMessage::TransferSeverityValues() const
    {
        for (Int_t i=0; i<fNSeverities; i++)
        {
            fMessageManager->AddSeverityValue(fSeverityInfoArray[i]->fSeverityLabel, fSeverityInfoArray[i]->fSeverity);
        }
        return;
    }
    
    //*****************
    
    void KLMessage::ProcessMessage(Severity aSeverity, const string& anOrigin, const string& aMessage)
    {
        (this->*fPrintFunctionArray[aSeverity-fIndexOffset])(anOrigin, aMessage, fSeverityInfoArray[aSeverity-fIndexOffset]);
        if (fSeverityInfoArray[aSeverity-fIndexOffset]->fIsFatal)
        {
            fMessageManager->ForceExit();
        }
        return;
    }

    void KLMessage::RegisterSeverity(Severity aSeverity, const string& aSeverityLabel, const string& aIntroText, Bool_t aCheckVerbosity, Bool_t aIsFatal, const string& aPrintFuncType)
    {
        if (fSeverityInfoArray[aSeverity-fIndexOffset] != NULL || fPrintFunctionArray[aSeverity-fIndexOffset] != NULL)
        {
            #ifndef SILENT_MODE
            cerr << "Fatal Error in KLMessage::RegisterSeverity:\n";
            cerr << "A severity of value <" << aSeverity << "> has already been registered!" << endl;
            #endif
            exit(-1);
        }
        
        // Add to fSeverityInfoArray
        KLSeverityInfo* tInfo = new KLSeverityInfo;
        tInfo->fSeverity = aSeverity;
        tInfo->fSeverityLabel = aSeverityLabel;
        tInfo->fIntroText = aIntroText;
        tInfo->fCheckVerbosity = aCheckVerbosity;
        tInfo->fIsFatal = aIsFatal;
        fSeverityInfoArray[aSeverity-fIndexOffset] = tInfo;
        
        // Add to fPrintFuncArray
        if (aPrintFuncType == string("Error"))
        {
            fPrintFunctionArray[aSeverity-fIndexOffset] = &KLMessage::PrintError;
        }
        else if (aPrintFuncType == string("Message"))
        {
            fPrintFunctionArray[aSeverity-fIndexOffset] = &KLMessage::PrintMessage;
        }
        else if (aPrintFuncType == string("Debug"))
        {
            fPrintFunctionArray[aSeverity-fIndexOffset] = &KLMessage::PrintDebug;
        }
        else
        {
            #ifndef SILENT_MODE
            cerr << "Fatal Error in KLMessage::RegisterSeverity:\n";
            cerr << "Unknown print function type <" << aPrintFuncType << ">" << endl;
            #endif
            if (fWriteLogFlag)
            {
                fLog->ErrorStream() << "Fatal Error in KLMessage::RegisterSeverity:\n";
                fLog->ErrorStream() << "Unknown print function type <" << aPrintFuncType << ">" << endl;
            }
            exit(-1);
        }
        
        // Fill in DebugScopeFlagMap
        if (aSeverity < 0) AddDebugScope(aSeverityLabel);
        
        return;
    }
    
    //*****************
    
    void KLMessage::PrintError(const string& anOrigin, const string& aMessage, KLSeverityInfo* aSeverityInfo)
    {
        if (! aSeverityInfo->fCheckVerbosity || fVerbosity >= aSeverityInfo->fSeverity)
        {
            #ifndef SILENT_MODE
            cerr << '\n';
            cerr << aSeverityInfo->fIntroText << ": " << aMessage;
            cerr << "ORIGIN: " << anOrigin << endl;
            
            #ifdef DEBUG_VERBOSE
            if (aSeverityInfo->fSeverity == eFatalError)
            {
                cerr << '\n';
                // print the backtrace
                void *array[10];
                size_t size;
                Char_t **strings;
                size_t i;
                size = backtrace(array, 10);
                strings = backtrace_symbols(array, size);
                fprintf(stderr, "Backtrace: obtained %zd stack frames.\n", size);
                for (i=0; i<size; i++)
                    fprintf(stderr, "%s\n", strings[i]);
                free(strings);
            }
            cerr << endl;
            #endif
            
            #endif
                
            if (fWriteLogFlag)
            {
                fLog->ErrorStream() << aSeverityInfo->fIntroText << ": " << aMessage << '\n';
                fLog->ErrorStream() << "ORIGIN: " << anOrigin << '\n';
                fLog->ErrorStream() << endl;
            }
        }
        return;
    }
        
    void KLMessage::PrintMessage(const string& anOrigin, const string& aMessage, KLSeverityInfo* aSeverityInfo)
    {
        if (! aSeverityInfo->fCheckVerbosity || fVerbosity >= aSeverityInfo->fSeverity)
        {
            #ifndef SILENT_MODE
            cout << '\n';
            cout << aSeverityInfo->fIntroText << " (" << anOrigin << "):\n";
            cout << aMessage << flush;
            #endif
            
            if (fWriteLogFlag)
            {
                fLog->LogStream() << aSeverityInfo->fIntroText << " (" << anOrigin << "):\n";
                fLog->LogStream() << aMessage << endl;
            }
        }
        return;
    }
        
    void KLMessage::PrintDebug(const string& anOrigin, const string& aMessage, KLSeverityInfo* aSeverityInfo)
    {
        if (GetDebugFlag(aSeverityInfo->fSeverityLabel))
        {
            #ifndef SILENT_MODE
            cout << '\n';
            cout << aSeverityInfo->fIntroText << " (" << anOrigin << "): " << aMessage << flush;
            #endif
            
            if (fWriteLogFlag)
            {
                fLog->LogStream() << aSeverityInfo->fIntroText << " (" << anOrigin << "): " << aMessage << endl;
            }
        }
        return;
    }

    
    //*****************************************************************
    //*****************************************************************
    //*****************************************************************
    
    
    //KLMessageInterface klmsg;
    
    //KLMessage* KLMessageInterface::fKLMessage = NULL;
    
    KLMessageInterface::KLMessageInterface() :
    KLMessageInterfaceBase()
    {
        //cout << "KLMessageInterface constructor" << endl;
    }
    
    KLMessageInterface::~KLMessageInterface()
    {
    }


} // end Kassiopeia namespace
