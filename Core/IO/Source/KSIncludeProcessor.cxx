#include "KSIncludeProcessor.h"

#include "KSTextFile.h"
#include "KSTokenizer.h"

#include "KSIOToolbox.h"
#include "KSIOMessage.h"

namespace Kassiopeia
{

    KSIncludeProcessor::KSIncludeProcessor()
    {
        Reset();
    }
    KSIncludeProcessor::~KSIncludeProcessor()
    {
    }

    void KSIncludeProcessor::ProcessToken( KSTokenBeginElement* aToken )
    {
        if( fState == eInactive )
        {

            if( aToken->GetElementName() == string( "include" ) )
            {
                fState = eActive;
                return;
            }
            KSProcessor::ProcessToken( aToken );
            return;

        }

        iomsg + eWarning;
        iomsg < "KSIncludeProcessor::ProcessToken";
        iomsg << "got unknown element <" << aToken->GetElementName() << ">" << ret;
        iomsg << "in path <" << fTokenizer->GetFilePath() << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;

        Reset();

        return;
    }

    void KSIncludeProcessor::ProcessToken( KSTokenAttribute* aToken )
    {

        if( fState == eInactive )
        {
            KSProcessor::ProcessToken( aToken );
            return;
        }
        if( fState == eActive )
        {
            if( (aToken->GetAttributeName() == string( "name" )) || (aToken->GetAttributeName() == string( "path" )) || (aToken->GetAttributeName() == string( "base" )) )
            {
                fState = eUseNames;
                ProcessToken( aToken );
            }
            if( aToken->GetAttributeName() == string( "key" ) )
            {
                fState = eUseKeys;
                ProcessToken( aToken );
            }
            return;
        }

        if( fState == eUseNames )
        {
            if( aToken->GetAttributeName() == string( "name" ) )
            {
                fNames.push_back( aToken->GetAttributeValue() );
                return;
            }
            if( aToken->GetAttributeName() == string( "path" ) )
            {
                fPaths.push_back( aToken->GetAttributeValue() );
                return;
            }
            if( aToken->GetAttributeName() == string( "base" ) )
            {
                fBases.push_back( aToken->GetAttributeValue() );
                return;
            }
        }

        if( fState == eUseKeys )
        {
            if( aToken->GetAttributeName() == string( "key" ) )
            {
                fKey = aToken->GetAttributeValue();
                return;
            }
        }

        iomsg + eWarning;
        iomsg < "KSIncludeProcessor::ProcessToken";
        iomsg << "got unknown attribute <" << aToken->GetAttributeName() << ">" << ret;
        iomsg << "in path <" << fTokenizer->GetFilePath() << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;

        Reset();

        return;

    }

    void KSIncludeProcessor::ProcessToken( KSTokenEndElement* aToken )
    {
        if( fState == eInactive )
        {
            KSProcessor::ProcessToken( aToken );
            return;
        }
        if( fState == eUseNames )
        {
            KSTextFile* aFile = new KSTextFile();
            aFile->SetKey( "(temporary included file)" );
            vector< string >::iterator It;
            for( It = fNames.begin(); It != fNames.end(); It++ )
            {
                aFile->AddToNames( *It );
            }
            for( It = fPaths.begin(); It != fPaths.end(); It++ )
            {
                aFile->AddToPaths( *It );
            }
            for( It = fBases.begin(); It != fBases.end(); It++ )
            {
                aFile->AddToBases( *It );
            }

            Reset();

            fTokenizer->IncludeFile( aFile );

            delete aFile;

            return;
        }
        if( fState == eUseKeys )
        {
            KSTextFile* aFile = KSIOToolbox::GetInstance()->GetConfigTextFile( fKey );
            if( aFile == NULL )
            {
                iomsg + eWarning;
                iomsg < "KSIncludeProcessor::ProcessToken";
                iomsg << "could not find file with key <" << fKey << "> without" << ret;
                iomsg << "in path <" << fTokenizer->GetFilePath() << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;

                Reset();

                return;
            }

            Reset();

            fTokenizer->IncludeFile( aFile );

            return;
        }
        if( fState == eActive )
        {
            iomsg + eWarning;
            iomsg < "KSIncludeProcessor::ProcessToken";
            iomsg << "got end element <" << aToken->GetElementName() << "> without attributes" << ret;
            iomsg << "in path <" << fTokenizer->GetFilePath() << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;

            Reset();

            return;
        }

        return;
    }

    void KSIncludeProcessor::Reset()
    {
        fNames.clear();
        fPaths.clear();
        fBases.clear();
        fKey.clear();

        fState = eInactive;

        return;
    }

}
