#include "KSIOToolbox.h"

#include "KSTextFile.h"
#include "KSRootFile.h"

#include "KSMessage.h"
#include "KSIOMessage.h"

#include "KSTokenizer.h"
#include "KSVariableProcessor.h"
#include "KSIncludeProcessor.h"
#include "KSLoopProcessor.h"
#include "KSBuilderProcessor.h"

#include "KSAssert.h"

#define STRING(anArgument) #anArgument
#define AS_STRING(anArgument) STRING(anArgument)

#ifndef KASSIOPEIA_CONFIG_DEFAULT_DIR
KSASSERT( false, KASSIOPEIA_CONFIG_DEFAULT_DIR_was_not_defined )
#define KASSIOPEIA_CONFIG_DEFAULT_DIR_STRING "."
#else
#define KASSIOPEIA_CONFIG_DEFAULT_DIR_STRING AS_STRING( KASSIOPEIA_CONFIG_DEFAULT_DIR )
#endif

#ifndef KASSIOPEIA_DATA_DEFAULT_DIR
KSASSERT( false, KASSIOPEIA_DATA_DEFAULT_DIR_was_not_defined )
#define KASSIOPEIA_DATA_DEFAULT_DIR_STRING "."
#else
#define KASSIOPEIA_DATA_DEFAULT_DIR_STRING AS_STRING( KASSIOPEIA_DATA_DEFAULT_DIR )
#endif

#ifndef KASSIOPEIA_SCRATCH_DEFAULT_DIR
KSASSERT( false, KASSIOPEIA_SCRATCH_DEFAULT_DIR_was_not_defined )
#define KASSIOPEIA_SCRATCH_DEFAULT_DIR_STRING "."
#else
#define KASSIOPEIA_SCRATCH_DEFAULT_DIR_STRING AS_STRING( KASSIOPEIA_SCRATCH_DEFAULT_DIR )
#endif

#ifndef KASSIOPEIA_OUTPUT_DEFAULT_DIR
KSASSERT( false, KASSIOPEIA_OUTPUT_DEFAULT_DIR_was_not_defined )
#define KASSIOPEIA_OUTPUT_DEFAULT_DIR_STRING "."
#else
#define KASSIOPEIA_OUTPUT_DEFAULT_DIR_STRING AS_STRING( KASSIOPEIA_OUTPUT_DEFAULT_DIR )
#endif

#ifndef KASSIOPEIA_LOG_DEFAULT_DIR
KSASSERT( false, KASSIOPEIA_LOG_DEFAULT_DIR_was_not_defined )
#define KASSIOPEIA_LOG_DEFAULT_DIR_STRING "."
#else
#define KASSIOPEIA_LOG_DEFAULT_DIR_STRING AS_STRING(KASSIOPEIA_LOG_DEFAULT_DIR)
#endif

#include <iostream>
using std::cout;
using std::endl;

namespace Kassiopeia
{

    KSIOToolbox* KSIOToolbox::fInstance = NULL;
    KSIOToolbox* KSIOToolbox::GetInstance()
    {
        if( fInstance == NULL )
        {
            fInstance = new KSIOToolbox();
        }
        return fInstance;
    }
    KSIOToolbox::KSIOToolbox() :
        KSManager( "IO" ),
        fConfigTextFileMap(),
        fConfigUserDirs(),
        fConfigDefaultDir( KASSIOPEIA_CONFIG_DEFAULT_DIR_STRING ),
        fDataTextFileMap(),
        fDataRootFileMap(),
        fDataUserDirs(),
        fDataDefaultDir( KASSIOPEIA_CONFIG_DEFAULT_DIR_STRING ),
        fScratchTextFileMap(),
        fScratchRootFileMap(),
        fScratchUserDirs(),
        fScratchDefaultDir( KASSIOPEIA_SCRATCH_DEFAULT_DIR_STRING ),
        fMessageMap(),
        fTerminalVerbosity( eNormal ),
        fLogVerbosity( eNormal ),
        fOutputRootFile( new KSRootFile() ),
        fOutputUserBase( "" ),
        fOutputDefaultBase( "KassiopeiaOutput.root" ),
        fOutputUserDir( "" ),
        fOutputDefaultDir( KASSIOPEIA_OUTPUT_DEFAULT_DIR_STRING ),
        fLogTextFile( new KSTextFile() ),
        fLogUserBase( "" ),
        fLogDefaultBase( "KassiopeiaLog.txt" ),
        fLogUserDir( "" ),
        fLogDefaultDir( KASSIOPEIA_LOG_DEFAULT_DIR_STRING ),
        fVariableMap(),
        fTokenizer( new KSTokenizer() ),
        fVariableProcessor( new KSVariableProcessor() ),
        fIncludeProcessor( new KSIncludeProcessor() ),
        fLoopProcessor( new KSLoopProcessor() ),
        fBuilderProcessor( new KSBuilderProcessor() )
    {
        fOutputRootFile->SetKey( "Output" );
        fOutputRootFile->AddToPaths( fOutputDefaultDir );
        fOutputRootFile->AddToBases( fOutputDefaultBase );

        fLogTextFile->SetKey( "Log" );
        fLogTextFile->AddToPaths( fLogDefaultDir );
        fLogTextFile->AddToBases( fLogDefaultBase );

        fTokenizer->DropProcessor( fVariableProcessor );
        fTokenizer->DropProcessor( fIncludeProcessor );
        fTokenizer->DropProcessor( fLoopProcessor );
        fTokenizer->DropProcessor( fBuilderProcessor );

        KSToolboxBuilder< KSIOToolbox >::SetToolbox( this );
    }
    KSIOToolbox::~KSIOToolbox()
    {
        delete fLoopProcessor;
        delete fIncludeProcessor;
        delete fVariableProcessor;
    }

    //****************
    //subclass control
    //****************

    void KSIOToolbox::SetupManagerSubclass()
    {
    }
    void KSIOToolbox::PrepareManagerSubclass()
    {
        this->ProcessConfigFile( "io" );
        return;
    }
    void KSIOToolbox::ShutdownManagerSubclass()
    {
    }
    void KSIOToolbox::AbortManagerSubclass()
    {
    }

    //*******************
    //configuration files
    //*******************

    void KSIOToolbox::AddConfigTextFile( KSTextFile* aConfigFile )
    {
        string aKey = aConfigFile->GetKey();
        TextFileIt TIt = fConfigTextFileMap.find( aKey );
        if( TIt == fConfigTextFileMap.end() )
        {
            aConfigFile->AddToBases( aKey + fConfigTextExtension );
            aConfigFile->AddToPaths( fConfigDefaultDir );
            DirListIt DIt;
            for( DIt = fConfigUserDirs.begin(); DIt != fConfigUserDirs.end(); DIt++ )
            {
                TIt->second->AddToPaths( *DIt );
            }

            fConfigTextFileMap.insert( TextFileEntry( aKey, aConfigFile ) );

#ifdef KASSIOPEIA_IO_DEBUG_VERBOSE
            iomsg < "KSIOToolbox::AddConfigTextFile";
            iomsg( eDebug ) << "added new config file with key <" << aKey << ">" << eom;
#endif

        }

        return;
    }
    KSTextFile* KSIOToolbox::GetConfigTextFile( const string& aKey )
    {
        TextFileIt TIt = fConfigTextFileMap.find( aKey );
        if( TIt != fConfigTextFileMap.end() )
        {
            return TIt->second;
        }
        return NULL;
    }
    KSTextFile* KSIOToolbox::DemandConfigTextFile( const string& aKey )
    {
        TextFileIt TIt = fConfigTextFileMap.find( aKey );
        if( TIt != fConfigTextFileMap.end() )
        {
            return TIt->second;
        }
        else
        {
            KSTextFile* aConfigFile = new KSTextFile();

            aConfigFile->SetKey( aKey );
            aConfigFile->AddToBases( aKey + fConfigTextExtension );
            aConfigFile->AddToPaths( fConfigDefaultDir );
            DirListIt DIt;
            for( DIt = fConfigUserDirs.begin(); DIt != fConfigUserDirs.end(); DIt++ )
            {
                aConfigFile->AddToPaths( *DIt );
            }

            fConfigTextFileMap.insert( TextFileEntry( aConfigFile->GetKey(), aConfigFile ) );

            return aConfigFile;
        }
    }
    void KSIOToolbox::RemoveConfigTextFile( KSTextFile* aConfigFile )
    {
        const string& aKey = aConfigFile->GetKey();
        TextFileIt TIt = fConfigTextFileMap.find( aKey );
        if( TIt != fConfigTextFileMap.end() )
        {
            fConfigTextFileMap.erase( TIt );
        }
        return;
    }
    const string KSIOToolbox::fConfigTextExtension = string( ".xml" );

    void KSIOToolbox::AddConfigUserDirectory( const string& aDirectory )
    {
        TextFileIt TIt;
        for( TIt = fConfigTextFileMap.begin(); TIt != fConfigTextFileMap.end(); TIt++ )
        {
            TIt->second->AddToPaths( aDirectory );
        }

        fConfigUserDirs.push_back( aDirectory );

#ifdef KASSIOPEIA_IO_DEBUG_VERBOSE
            iomsg < "KSIOToolbox::AddConfigUserDirectory";
            iomsg( eDebug ) << "added config directory <" << aDirectory << ">" << eom;
#endif

        return;
    }

    //**********
    //data files
    //**********

    void KSIOToolbox::AddDataTextFile( KSTextFile* aDataFile )
    {
        string aKey = aDataFile->GetKey();
        TextFileIt TIt = fDataTextFileMap.find( aKey );
        if( TIt == fDataTextFileMap.end() )
        {
            aDataFile->AddToBases( aKey + fDataTextExtension );
            aDataFile->AddToPaths( fDataDefaultDir );
            DirListIt DIt;
            for( DIt = fDataUserDirs.begin(); DIt != fDataUserDirs.end(); DIt++ )
            {
                TIt->second->AddToPaths( *DIt );
            }

            fDataTextFileMap.insert( TextFileEntry( aKey, aDataFile ) );
        }
        return;
    }
    KSTextFile* KSIOToolbox::GetDataTextFile( const string& aKey )
    {
        TextFileIt TIt = fDataTextFileMap.find( aKey );
        if( TIt != fDataTextFileMap.end() )
        {
            return TIt->second;
        }
        return NULL;
    }
    KSTextFile* KSIOToolbox::DemandDataTextFile( const string& aKey )
    {
        TextFileIt TIt = fDataTextFileMap.find( aKey );
        if( TIt != fDataTextFileMap.end() )
        {
            return TIt->second;
        }
        else
        {
            KSTextFile* aDataFile = new KSTextFile();

            aDataFile->SetKey( aKey );
            aDataFile->AddToBases( aKey + fDataTextExtension );
            aDataFile->AddToPaths( fDataDefaultDir );
            DirListIt DIt;
            for( DIt = fDataUserDirs.begin(); DIt != fDataUserDirs.end(); DIt++ )
            {
                aDataFile->AddToPaths( *DIt );
            }

            fDataTextFileMap.insert( TextFileEntry( aDataFile->GetKey(), aDataFile ) );

            return aDataFile;
        }
    }
    void KSIOToolbox::RemoveDataTextFile( KSTextFile* aDataFile )
    {
        const string& aKey = aDataFile->GetKey();
        TextFileIt TIt = fDataTextFileMap.find( aKey );
        if( TIt != fDataTextFileMap.end() )
        {
            fDataTextFileMap.erase( TIt );
        }
        return;
    }
    const string KSIOToolbox::fDataTextExtension = string( ".dat" );

    void KSIOToolbox::AddDataRootFile( KSRootFile* aDataFile )
    {
        const string& aKey = aDataFile->GetKey();
        RootFileIt RIt = fDataRootFileMap.find( aDataFile->GetKey() );
        if( RIt == fDataRootFileMap.end() )
        {
            aDataFile->AddToBases( aKey + fDataRootExtension );
            aDataFile->AddToPaths( fDataDefaultDir );
            DirListIt DIt;
            for( DIt = fDataUserDirs.begin(); DIt != fDataUserDirs.end(); DIt++ )
            {
                aDataFile->AddToPaths( *DIt );
            }

            fDataRootFileMap.insert( RootFileEntry( aDataFile->GetKey(), aDataFile ) );
        }
        return;
    }
    KSRootFile* KSIOToolbox::GetDataRootFile( const string& aKey )
    {
        RootFileIt RIt = fDataRootFileMap.find( aKey );
        if( RIt != fDataRootFileMap.end() )
        {
            return RIt->second;
        }
        return NULL;
    }
    KSRootFile* KSIOToolbox::DemandDataRootFile( const string& aKey )
    {
        RootFileIt RIt = fDataRootFileMap.find( aKey );
        if( RIt != fDataRootFileMap.end() )
        {
            return RIt->second;
        }
        else
        {
            KSRootFile* aDataFile = new KSRootFile();

            aDataFile->AddToBases( aKey + fDataRootExtension );
            aDataFile->AddToPaths( fDataDefaultDir );
            DirListIt DIt;
            for( DIt = fDataUserDirs.begin(); DIt != fDataUserDirs.end(); DIt++ )
            {
                aDataFile->AddToPaths( *DIt );
            }

            fDataRootFileMap.insert( RootFileEntry( aDataFile->GetKey(), aDataFile ) );

            return aDataFile;
        }
    }
    void KSIOToolbox::RemoveDataRootFile( KSRootFile* aDataFile )
    {
        const string& aKey = aDataFile->GetKey();
        RootFileIt TIt = fDataRootFileMap.find( aKey );
        if( TIt != fDataRootFileMap.end() )
        {
            fDataRootFileMap.erase( TIt );
        }
        return;
    }
    const string KSIOToolbox::fDataRootExtension = string( ".root" );

    void KSIOToolbox::AddDataUserDirectory( const string& aDirectory )
    {
        TextFileIt TIt;
        for( TIt = fDataTextFileMap.begin(); TIt != fDataTextFileMap.end(); TIt++ )
        {
            TIt->second->AddToPaths( aDirectory );
        }

        RootFileIt RIt;
        for( RIt = fDataRootFileMap.begin(); RIt != fDataRootFileMap.end(); RIt++ )
        {
            RIt->second->AddToPaths( aDirectory );
        }

        fDataUserDirs.push_back( aDirectory );

        return;
    }

    //*************
    //scratch files
    //*************

    void KSIOToolbox::AddScratchTextFile( KSTextFile* aScratchFile )
    {
        string aKey = aScratchFile->GetKey();
        TextFileIt TIt = fScratchTextFileMap.find( aKey );
        if( TIt == fScratchTextFileMap.end() )
        {
            aScratchFile->AddToBases( aKey + fScratchTextExtension );
            aScratchFile->AddToPaths( fScratchDefaultDir );
            DirListIt DIt;
            for( DIt = fScratchUserDirs.begin(); DIt != fScratchUserDirs.end(); DIt++ )
            {
                TIt->second->AddToPaths( *DIt );
            }

            fScratchTextFileMap.insert( TextFileEntry( aKey, aScratchFile ) );
        }
        return;
    }
    KSTextFile* KSIOToolbox::GetScratchTextFile( const string& aKey )
    {
        TextFileIt TIt = fScratchTextFileMap.find( aKey );
        if( TIt != fScratchTextFileMap.end() )
        {
            return TIt->second;
        }
        return NULL;
    }
    KSTextFile* KSIOToolbox::DemandScratchTextFile( const string& aKey )
    {
        TextFileIt TIt = fScratchTextFileMap.find( aKey );
        if( TIt != fScratchTextFileMap.end() )
        {
            return TIt->second;
        }
        else
        {
            KSTextFile* aScratchFile = new KSTextFile();

            aScratchFile->SetKey( aKey );
            aScratchFile->AddToBases( aKey + fScratchTextExtension );
            aScratchFile->AddToPaths( fScratchDefaultDir );
            DirListIt DIt;
            for( DIt = fScratchUserDirs.begin(); DIt != fScratchUserDirs.end(); DIt++ )
            {
                aScratchFile->AddToPaths( *DIt );
            }

            fScratchTextFileMap.insert( TextFileEntry( aScratchFile->GetKey(), aScratchFile ) );

            return aScratchFile;
        }
    }
    void KSIOToolbox::RemoveScratchTextFile( KSTextFile* aScratchFile )
    {
        const string& aKey = aScratchFile->GetKey();
        TextFileIt TIt = fScratchTextFileMap.find( aKey );
        if( TIt != fScratchTextFileMap.end() )
        {
            fScratchTextFileMap.erase( TIt );
        }
        return;
    }
    const string KSIOToolbox::fScratchTextExtension = string( ".dat" );

    void KSIOToolbox::AddScratchRootFile( KSRootFile* aScratchFile )
    {
        const string& aKey = aScratchFile->GetKey();
        RootFileIt RIt = fScratchRootFileMap.find( aScratchFile->GetKey() );
        if( RIt == fScratchRootFileMap.end() )
        {
            aScratchFile->AddToBases( aKey + fScratchRootExtension );
            aScratchFile->AddToPaths( fScratchDefaultDir );
            DirListIt DIt;
            for( DIt = fScratchUserDirs.begin(); DIt != fScratchUserDirs.end(); DIt++ )
            {
                aScratchFile->AddToPaths( *DIt );
            }

            fScratchRootFileMap.insert( RootFileEntry( aScratchFile->GetKey(), aScratchFile ) );
        }
        return;
    }
    KSRootFile* KSIOToolbox::GetScratchRootFile( const string& aKey )
    {
        RootFileIt RIt = fScratchRootFileMap.find( aKey );
        if( RIt != fScratchRootFileMap.end() )
        {
            return RIt->second;
        }
        return NULL;
    }
    KSRootFile* KSIOToolbox::DemandScratchRootFile( const string& aKey )
    {
        RootFileIt RIt = fScratchRootFileMap.find( aKey );
        if( RIt != fScratchRootFileMap.end() )
        {
            return RIt->second;
        }
        else
        {
            KSRootFile* aScratchFile = new KSRootFile();

            aScratchFile->AddToBases( aKey + fScratchRootExtension );
            aScratchFile->AddToPaths( fScratchDefaultDir );
            DirListIt DIt;
            for( DIt = fScratchUserDirs.begin(); DIt != fScratchUserDirs.end(); DIt++ )
            {
                aScratchFile->AddToPaths( *DIt );
            }

            fScratchRootFileMap.insert( RootFileEntry( aScratchFile->GetKey(), aScratchFile ) );

            return aScratchFile;
        }
    }
    void KSIOToolbox::RemoveScratchRootFile( KSRootFile* aScratchFile )
    {
        const string& aKey = aScratchFile->GetKey();
        RootFileIt TIt = fScratchRootFileMap.find( aKey );
        if( TIt != fScratchRootFileMap.end() )
        {
            fScratchRootFileMap.erase( TIt );
        }
        return;
    }
    const string KSIOToolbox::fScratchRootExtension = string( ".root" );

    void KSIOToolbox::AddScratchUserDirectory( const string& aDirectory )
    {
        TextFileIt TIt;
        for( TIt = fScratchTextFileMap.begin(); TIt != fScratchTextFileMap.end(); TIt++ )
        {
            TIt->second->AddToPaths( aDirectory );
        }

        RootFileIt RIt;
        for( RIt = fScratchRootFileMap.begin(); RIt != fScratchRootFileMap.end(); RIt++ )
        {
            RIt->second->AddToPaths( aDirectory );
        }

        fScratchUserDirs.push_back( aDirectory );

        return;
    }

    //********
    //messages
    //********

    void KSIOToolbox::AddMessage( KSMessage* aMessage )
    {
        string aKey = aMessage->GetKey();
        MessageIt TIt = fMessageMap.find( aKey );
        if( TIt == fMessageMap.end() )
        {
            aMessage->SetTerminalVerbosity( fTerminalVerbosity );
            aMessage->SetLogVerbosity( fLogVerbosity );
            aMessage->SetLogFile( fLogTextFile );

            fMessageMap.insert( MessageEntry( aMessage->GetKey(), aMessage ) );
        }
        return;
    }
    KSMessage* KSIOToolbox::GetMessage( const string& aKey )
    {
        MessageIt TIt = fMessageMap.find( aKey );
        if( TIt != fMessageMap.end() )
        {
            return TIt->second;
        }
        return NULL;
    }
    KSMessage* KSIOToolbox::DemandMessage( const string& aKey )
    {
        MessageIt TIt = fMessageMap.find( aKey );
        if( TIt != fMessageMap.end() )
        {
            return TIt->second;
        }
        else
        {
            KSMessage* aMessage = new KSMessage();

            aMessage->SetKey( aKey );
            aMessage->SetTerminalVerbosity( fTerminalVerbosity );
            aMessage->SetLogVerbosity( fLogVerbosity );
            aMessage->SetLogFile( fLogTextFile );

            fMessageMap.insert( MessageEntry( aMessage->GetKey(), aMessage ) );

            return aMessage;
        }
    }
    void KSIOToolbox::RemoveMessage( KSMessage* aFile )
    {
        const string& aKey = aFile->GetKey();
        MessageIt TIt = fMessageMap.find( aKey );
        if( TIt != fMessageMap.end() )
        {
            fMessageMap.erase( TIt );
        }
        return;
    }

    void KSIOToolbox::SetTerminalVerbosity( const UInt_t& aVerbosity )
    {
        MessageIt MIt;
        for( MIt = fMessageMap.begin(); MIt != fMessageMap.end(); MIt++ )
        {
            MIt->second->SetTerminalVerbosity( aVerbosity );
        }

        fTerminalVerbosity = aVerbosity;

        return;
    }
    void KSIOToolbox::SetLogVerbosity( const UInt_t& aVerbosity )
    {
        MessageIt MIt;
        for( MIt = fMessageMap.begin(); MIt != fMessageMap.end(); MIt++ )
        {
            MIt->second->SetLogVerbosity( aVerbosity );
        }

        fLogVerbosity = aVerbosity;
        return;
    }

    //***********
    //output file
    //***********

    KSRootFile* KSIOToolbox::GetOutputRootFile()
    {
        return fOutputRootFile;
    }
    void KSIOToolbox::SetOutputUserBase( const string& aBase )
    {
        fOutputUserBase = aBase;
        fOutputRootFile->AddToBases( fOutputUserBase );
        return;
    }
    void KSIOToolbox::SetOutputUserDirectory( const string& aDirectory )
    {
        fOutputUserDir = aDirectory;
        fOutputRootFile->AddToPaths( fOutputUserDir );
        return;
    }

    //********
    //log file
    //********

    KSTextFile* KSIOToolbox::GetLogTextFile()
    {
        return fLogTextFile;
    }
    void KSIOToolbox::SetLogUserBase( const string& aBase )
    {
        fLogUserBase = aBase;
        fLogTextFile->AddToBases( fLogUserBase );
    }
    void KSIOToolbox::SetLogUserDirectory( const string& aDirectory )
    {
        fLogUserDir = aDirectory;
        fLogTextFile->AddToPaths( fLogUserDir );
        return;
    }

    //*********
    //variables
    //*********

    void KSIOToolbox::AddVariable( const string& aName, const string& aValue )
    {
        VariableIt It = fVariableMap.find( aName );
        if( It == fVariableMap.end() )
        {
            fVariableMap.insert( VariableEntry( aName, aValue ) );
            return;
        }
        It->second = aValue;
        return;
    }
    KSIOToolbox::VariableMap* KSIOToolbox::GetVariables()
    {
        return &fVariableMap;
    }

    //*******************
    //config file reading
    //*******************

    void KSIOToolbox::ProcessConfigFile( const string& aKey )
    {
        fTokenizer->ProcessFile( DemandConfigTextFile( aKey ) );
        return;
    }

}
