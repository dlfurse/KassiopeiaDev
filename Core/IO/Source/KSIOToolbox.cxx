#include "KSIOToolbox.h"

#include "KSInstallDirectories.h"
#include "KSTextFile.h"
#include "KSRootFile.h"

namespace Kassiopeia
{

    KSIOToolbox::KSIOToolbox() :
        fConfigTextFileMap(),
        fConfigDir( "" ),
        fInstallConfigDir( KASSIOPEIA_INSTALL_CONFIG_DIR ),
        fDataTextFileMap(),
        fDataRootFileMap(),
        fDataDir( "" ),
        fDataInstallDir( KASSIOPEIA_INSTALL_DATA_DIR ),
        fScratchTextFileMap(),
        fScratchRootFileMap(),
        fScratchDir( "" ),
        fScratchInstallDir( KASSIOPEIA_INSTALL_SCRATCH_DIR ),
        fOutputRootFile( new KSRootFile() ),
        fOutputDir( "" ),
        fOutputInstallDir( KASSIOPEIA_INSTALL_OUTPUT_DIR ),
        fLogTextFile( new KSTextFile() ),
        fLogDir( "" ),
        fLogInstallDir( KASSIOPEIA_INSTALL_LOG_DIR ),
        fMessageMap(),
        fTerminalVerbosity( eMessage ),
        fLogVerbosity( eMessage )

    {
        fOutputRootFile->AddToPaths( fOutputInstallDir );
        fOutputRootFile->AddToBases( "KassiopeiaOutput.root" );

        fLogTextFile->AddToPaths( fLogInstallDir );
        fLogTextFile->AddToBases( "KassiopeiaLog.txt" );
    }
    KSIOToolbox::~KSIOToolbox()
    {
    }

    const string& KSIOToolbox::GetTypeName() const
    {
        return fTypeName;
    }
    const string KSIOToolbox::fTypeName = string( "IO" );

    void KSIOToolbox::SetConfigDirectory( const string& aDirectory )
    {
        TextFileIt TIt;
        for( TIt = fConfigTextFileMap.begin(); TIt != fConfigTextFileMap.end(); TIt++ )
        {
            TIt->second->AddToPaths( aDirectory );
        }

        fConfigDir = aDirectory;

        return;
    }
    void KSIOToolbox::AddConfigTextFile( KSTextFile* aConfigFile )
    {
        TextFileIt TIt = fConfigTextFileMap.find( aConfigFile->GetKey() );
        if( TIt == fConfigTextFileMap.end() )
        {
            aConfigFile->AddToPaths( fInstallConfigDir );
            if( fConfigDir.empty() == kFALSE )
            {
                aConfigFile->AddToPaths( fConfigDir );
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

    void KSIOToolbox::SetDataDirectory( const string& aDirectory )
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

        fDataDir = aDirectory;

        return;
    }
    void KSIOToolbox::AddDataTextFile( KSTextFile* aDataFile )
    {
        TextFileIt TIt = fDataTextFileMap.find( aDataFile->GetKey() );
        if( TIt == fDataTextFileMap.end() )
        {
            aDataFile->AddToPaths( fDataInstallDir );
            if( fDataDir.empty() == kFALSE )
            {
                aDataFile->AddToPaths( fDataDir );
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
    void KSIOToolbox::AddDataRootFile( KSRootFile* aDataFile )
    {
        RootFileIt RIt = fDataRootFileMap.find( aDataFile->GetKey() );
        if( RIt == fDataRootFileMap.end() )
        {
            aDataFile->AddToPaths( fDataInstallDir );
            if( fDataDir.empty() == kFALSE )
            {
                aDataFile->AddToPaths( fDataDir );
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

    void KSIOToolbox::SetScratchDirectory( const string& aDirectory )
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

        fScratchDir = aDirectory;

        return;
    }
    void KSIOToolbox::AddScratchTextFile( KSTextFile* aScratchFile )
    {
        TextFileIt TIt = fScratchTextFileMap.find( aScratchFile->GetKey() );
        if( TIt == fScratchTextFileMap.end() )
        {
            aScratchFile->AddToPaths( fScratchInstallDir );
            if( fScratchDir.empty() == kFALSE )
            {
                aScratchFile->AddToPaths( fScratchDir );
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
    void KSIOToolbox::AddScratchRootFile( KSRootFile* aScratchFile )
    {
        RootFileIt RIt = fScratchRootFileMap.find( aScratchFile->GetKey() );
        if( RIt == fScratchRootFileMap.end() )
        {
            aScratchFile->AddToPaths( fScratchInstallDir );
            if( fScratchDir.empty() == kFALSE )
            {
                aScratchFile->AddToPaths( fScratchDir );
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

    void KSIOToolbox::SetOutputDirectory( const string& aDirectory )
    {
        fOutputRootFile->AddToPaths( aDirectory );
        fOutputDir = aDirectory;
        return;
    }
    KSRootFile* KSIOToolbox::GetOutputRootFile()
    {
        return fOutputRootFile;
    }


    void KSIOToolbox::SetLogDirectory( const string& aDirectory )
    {
        fLogTextFile->AddToPaths( aDirectory );
        fLogDir = aDirectory;
        return;
    }
    KSTextFile* KSIOToolbox::GetLogTextFile()
    {
        return fLogTextFile;
    }

    void KSIOToolbox::SetTerminalVerbosity( const KSMessageSeverity aVerbosity )
    {
        MessageIt MIt;
        for( MIt = fMessageMap.begin(); MIt != fMessageMap.end(); MIt++ )
        {
            MIt->second->SetTerminalVerbosity( aVerbosity );
        }

        fTerminalVerbosity = aVerbosity;

        return;
    }
    void KSIOToolbox::SetLogVerbosity( const KSMessageSeverity aVerbosity )
    {
        MessageIt MIt;
        for( MIt = fMessageMap.begin(); MIt != fMessageMap.end(); MIt++ )
        {
            MIt->second->SetLogVerbosity( aVerbosity );
        }

        fLogVerbosity = aVerbosity;
        return;
    }

    void KSIOToolbox::AddMessage( KSMessage* aMessage )
    {
        MessageIt MIt = fMessageMap.find( aMessage->GetKey() );
        if( MIt != fMessageMap.end() )
        {
            aMessage->SetTerminalVerbosity( fTerminalVerbosity );
            aMessage->SetLogVerbosity( fLogVerbosity );

            fMessageMap.insert( MessageEntry( aMessage->GetKey(), aMessage ));
        }
        return;
    }
    KSMessage* KSIOToolbox::GetMessage( const string& aKey )
    {
        MessageIt MIt = fMessageMap.find( aKey );
        if( MIt != fMessageMap.end() )
        {
            return MIt->second;
        }
        return NULL;
    }

}
