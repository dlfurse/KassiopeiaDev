#include "KSIOToolbox.h"

#include "KSInstallDirectories.h"
#include "KSTextFile.h"
#include "KSRootFile.h"
#include "KSMessage.h"

#include "KSIOMessage.h"

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
        fConfigUserDir( "" ),
        fConfigDefaultDir( KASSIOPEIA_INSTALL_CONFIG_DIR ),
        fDataTextFileMap(),
        fDataRootFileMap(),
        fDataUserDir( "" ),
        fDataDefaultDir( KASSIOPEIA_INSTALL_DATA_DIR ),
        fScratchTextFileMap(),
        fScratchRootFileMap(),
        fScratchUserDir( "" ),
        fScratchDefaultDir( KASSIOPEIA_INSTALL_SCRATCH_DIR ),
        fOutputRootFile( new KSRootFile() ),
        fOutputUserBase( "" ),
        fOutputDefaultBase( "KassiopeiaOutput.root" ),
        fOutputUserDir( "" ),
        fOutputDefaultDir( KASSIOPEIA_INSTALL_OUTPUT_DIR ),
        fLogTextFile( new KSTextFile() ),
        fLogUserBase( "" ),
        fLogDefaultBase( "KassiopeiaLog.txt" ),
        fLogUserDir( "" ),
        fLogDefaultDir( KASSIOPEIA_INSTALL_LOG_DIR ),
        fMessageMap(),
        fTerminalVerbosity( eNormal ),
        fLogVerbosity( eNormal )

    {
        fOutputRootFile->SetKey("Output");
        fOutputRootFile->AddToPaths( fOutputDefaultDir );
        fOutputRootFile->AddToBases( fOutputDefaultBase );

        fLogTextFile->SetKey("Log");
        fLogTextFile->AddToPaths( fLogDefaultDir );
        fLogTextFile->AddToBases( fLogDefaultBase );
    }
    KSIOToolbox::~KSIOToolbox()
    {
    }

    //*******************
    //configuration files
    //*******************

    void KSIOToolbox::AddConfigTextFile( KSTextFile* aConfigFile )
    {
        TextFileIt TIt = fConfigTextFileMap.find( aConfigFile->GetKey() );
        if( TIt == fConfigTextFileMap.end() )
        {
            aConfigFile->AddToPaths( fConfigDefaultDir );
            if( fConfigUserDir.empty() == kFALSE )
            {
                aConfigFile->AddToPaths( fConfigUserDir );
            }

            fConfigTextFileMap.insert( TextFileEntry( aConfigFile->GetKey(), aConfigFile ) );
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
    KSTextFile* KSIOToolbox::DemandConfigFile( const string& aKey )
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

            aConfigFile->AddToPaths( fConfigDefaultDir );
            if( fConfigUserDir.empty() == kFALSE )
            {
                aConfigFile->AddToPaths( fConfigUserDir );
            }

            fConfigTextFileMap.insert( TextFileEntry( aConfigFile->GetKey(), aConfigFile ) );

            return aConfigFile;
        }
    }
    void KSIOToolbox::SetConfigUserDirectory( const string& aDirectory )
    {
        TextFileIt TIt;
        for( TIt = fConfigTextFileMap.begin(); TIt != fConfigTextFileMap.end(); TIt++ )
        {
            TIt->second->AddToPaths( aDirectory );
        }

        fConfigUserDir = aDirectory;

        return;
    }

    //**********
    //data files
    //**********

    void KSIOToolbox::AddDataTextFile( KSTextFile* aDataFile )
    {
        TextFileIt TIt = fDataTextFileMap.find( aDataFile->GetKey() );
        if( TIt == fDataTextFileMap.end() )
        {
            aDataFile->AddToPaths( fDataDefaultDir );
            if( fDataUserDir.empty() == kFALSE )
            {
                aDataFile->AddToPaths( fDataUserDir );
            }

            fDataTextFileMap.insert( TextFileEntry( aDataFile->GetKey(), aDataFile ) );
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

            aDataFile->AddToPaths( fDataDefaultDir );
            if( fDataUserDir.empty() == kFALSE )
            {
                aDataFile->AddToPaths( fDataUserDir );
            }

            fDataTextFileMap.insert( TextFileEntry( aDataFile->GetKey(), aDataFile ) );

            return aDataFile;
        }
    }
    void KSIOToolbox::AddDataRootFile( KSRootFile* aDataFile )
    {
        RootFileIt RIt = fDataRootFileMap.find( aDataFile->GetKey() );
        if( RIt == fDataRootFileMap.end() )
        {
            aDataFile->AddToPaths( fDataDefaultDir );
            if( fDataUserDir.empty() == kFALSE )
            {
                aDataFile->AddToPaths( fDataUserDir );
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
            aDataFile->SetKey( aKey );

            aDataFile->AddToPaths( fDataDefaultDir );
            if( fDataUserDir.empty() == kFALSE )
            {
                aDataFile->AddToPaths( fDataUserDir );
            }

            fDataRootFileMap.insert( RootFileEntry( aDataFile->GetKey(), aDataFile ) );

            return aDataFile;
        }
    }
    void KSIOToolbox::SetDataUserDirectory( const string& aDirectory )
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

        fDataUserDir = aDirectory;

        return;
    }

    //*************
    //scratch files
    //*************

    void KSIOToolbox::AddScratchTextFile( KSTextFile* aScratchFile )
    {
        TextFileIt TIt = fScratchTextFileMap.find( aScratchFile->GetKey() );
        if( TIt == fScratchTextFileMap.end() )
        {
            aScratchFile->AddToPaths( fScratchDefaultDir );
            if( fScratchUserDir.empty() == kFALSE )
            {
                aScratchFile->AddToPaths( fScratchUserDir );
            }

            fScratchTextFileMap.insert( TextFileEntry( aScratchFile->GetKey(), aScratchFile ) );
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

            aScratchFile->AddToPaths( fScratchDefaultDir );
            if( fScratchUserDir.empty() == kFALSE )
            {
                aScratchFile->AddToPaths( fScratchUserDir );
            }

            fScratchTextFileMap.insert( TextFileEntry( aScratchFile->GetKey(), aScratchFile ) );

            return aScratchFile;
        }
    }
    void KSIOToolbox::AddScratchRootFile( KSRootFile* aScratchFile )
    {
        RootFileIt RIt = fScratchRootFileMap.find( aScratchFile->GetKey() );
        if( RIt == fScratchRootFileMap.end() )
        {
            aScratchFile->AddToPaths( fScratchDefaultDir );
            if( fScratchUserDir.empty() == kFALSE )
            {
                aScratchFile->AddToPaths( fScratchUserDir );
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
            aScratchFile->SetKey( aKey );

            aScratchFile->AddToPaths( fScratchDefaultDir );
            if( fScratchUserDir.empty() == kFALSE )
            {
                aScratchFile->AddToPaths( fScratchUserDir );
            }

            fScratchRootFileMap.insert( RootFileEntry( aScratchFile->GetKey(), aScratchFile ) );

            return aScratchFile;
        }
    }
    void KSIOToolbox::SetScratchUserDirectory( const string& aDirectory )
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

        fScratchUserDir = aDirectory;

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

    //********
    //messages
    //********

    void KSIOToolbox::AddMessage( KSMessage* aMessage )
    {
        //iomsg + eWarning;
        //iomsg < "KSIOToolbox::AddMessage" < end;
        //iomsg << "message " << aMessage->GetKey() << " has been registered" << end;

        MessageIt MIt = fMessageMap.find( aMessage->GetKey() );
        if( MIt == fMessageMap.end() )
        {
            fMessageMap.insert( MessageEntry( aMessage->GetKey(), aMessage ) );
        }

        aMessage->SetTerminalVerbosity( fTerminalVerbosity );
        aMessage->SetLogVerbosity( fLogVerbosity );
        aMessage->SetLogFile( fLogTextFile );

        return;
    }
    void KSIOToolbox::RemoveMessage( KSMessage* aMessage )
    {
        MessageIt MIt = fMessageMap.find( aMessage->GetKey() );
        if( MIt != fMessageMap.end() )
        {
            fMessageMap.erase( MIt );
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

//static KSIOManagerFactory sKSIOManagerFactory;

}
