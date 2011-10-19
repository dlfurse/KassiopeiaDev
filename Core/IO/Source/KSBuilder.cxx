#include "KSBuilder.h"

#include "KSTokenizer.h"
#include "KSIOMessage.h"

namespace Kassiopeia
{

    KSBuilder::KSBuilder() :
        KSProcessor()
    {
    }
    KSBuilder::~KSBuilder()
    {
    }

    void KSBuilder::ProcessToken( KSTokenBeginElement* aToken )
    {
        if( fChild == NULL )
        {
            FactoryIt It = fMap->find( aToken->GetElementName() );
            if( It == fMap->end() )
            {
                iomsg < "KSBuilder::ReceiveToken" < ret;
                iomsg << "no builder registered for begin element token: " << aToken->GetElementName() << ret;
                iomsg( eWarning ) << "in path <" << fTokenizer->GetFilePath() << "> in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << "> at column <" << fTokenizer->GetFileColumn() << ">" << eom;
                return;
            }

            KSBuilder* Builder = (It->second)();
            if( Builder->Start() == kFALSE )
            {
                iomsg < "KSBuilder::ReceiveToken" < ret;
                iomsg << "could not start builder for element token: " << aToken->GetElementName() << ret;
                iomsg( eWarning ) << "in path <" << fTokenizer->GetFilePath() << "> in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << "> at column <" << fTokenizer->GetFileColumn() << ">" << eom;
                return;
            }

            this->DropProcessor( Builder );
            return;
        }
        else
        {
            KSProcessor::ProcessToken( aToken );
            return;
        }
    }
    void KSBuilder::ProcessToken( KSTokenEndElement* aToken )
    {
        if( fChild == NULL )
        {
            if( End() == kFALSE )
            {
                iomsg < "KSBuilder::ReceiveToken" < ret;
                iomsg << "could not end builder for element token: " << aToken->GetElementName() << ret;
                iomsg( eWarning ) << "in path <" << fTokenizer->GetFilePath() << "> in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << "> at column <" << fTokenizer->GetFileColumn() << ">" << eom;
                return;
            }

            LiftProcessor( this );
            return;
        }
        else
        {
            KSProcessor::ProcessToken( aToken );
            return;
        }
    }
    void KSBuilder::ProcessToken( KSTokenAttribute* aToken )
    {
        if( fChild == NULL )
        {
            if( AddAttribute( aToken ) == kFALSE )
            {
                iomsg < "KSBuilder::ReceiveToken" < ret;
                iomsg << "got unknown attribute token: " << ret;
                iomsg( eWarning ) << "in path <" << fTokenizer->GetFilePath() << "> in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << "> at column <" << fTokenizer->GetFileColumn() << ">" << eom;
            }
            return;
        }
        else
        {
            KSProcessor::ProcessToken( aToken );
            return;
        }
    }
    void KSBuilder::ProcessToken( KSTokenData* aToken )
    {
        if( fChild == NULL )
        {
            if( AddData( aToken ) == kFALSE )
            {
                iomsg < "KSBuilder::ReceiveToken" < ret;
                iomsg << "got unknown data token: " << ret;
                iomsg( eWarning ) << "in path <" << fTokenizer->GetFilePath() << "> in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << "> at column <" << fTokenizer->GetFileColumn() << ">" << eom;
            }
            return;
        }
        else
        {
            KSProcessor::ProcessToken( aToken );
            return;
        }
    }

    Bool_t KSBuilder::Start()
    {
        return kTRUE;
    }
    Bool_t KSBuilder::AddAttribute( KSTokenAttribute* /*aToken*/)
    {
        return kFALSE;
    }
    Bool_t KSBuilder::AddData( KSTokenData* /*aToken*/)
    {
        return kFALSE;
    }
    Bool_t KSBuilder::End()
    {
        return kTRUE;
    }

}
