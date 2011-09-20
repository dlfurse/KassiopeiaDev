#include "KSProcessor.h"

#include "KSIOMessage.h"
#include "KSTokenizer.h"

//#include <iostream>
//using std::cout;
//using std::endl;

namespace Kassiopeia
{

    KSTokenizer* KSProcessor::fTokenizer = NULL;

    KSProcessor::KSProcessor() :
        fParent( NULL ),
        fChild( NULL )
    {
    }
    KSProcessor::~KSProcessor()
    {
        //cout << "(" << this << ") i am like dying homes" << endl;
    }

    void KSProcessor::DropProcessor( KSProcessor* aNewProcessor )
    {
        //cout << "(" << this << ") dropping a processor of type " << aNewProcessor->GetTypeName() << endl;
        if( fChild == NULL )
        {
            fChild = aNewProcessor;
            fChild->fParent = this;
            return;
        }
        fChild->DropProcessor( aNewProcessor );
        return;
    }
    void KSProcessor::LiftProcessor( KSProcessor* const anOldProcessor )
    {
        //cout << "(" << this << ") lifting a builder of type " << anOldProcessor->GetTypeName() << endl;

        if( fParent == NULL )
        {
            delete anOldProcessor;
            return;
        }
        fParent->LiftProcessor( anOldProcessor );
        return;
    }

    void KSProcessor::ProcessToken( KSTokenBeginParsing* aToken )
    {
        if( fChild == NULL )
        {
            if( ProcessEndToken( aToken ) == kFALSE )
            {
                iomsg + eError;
                iomsg < "KSProcessor::ReceiveToken";
                iomsg << "got unknown token: " << ret;
                iomsg << "in path <" << fTokenizer->GetFilePath() << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;
            }
            return;
        }
        else
        {
            if( ProcessStreamToken( aToken ) == kFALSE )
            {
                iomsg + eError;
                iomsg < "KSProcessor::ReceiveToken";
                iomsg << "got unknown token: " << ret;
                iomsg << "in path <" << fTokenizer->GetFilePath() << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;
            }
            fChild->ProcessToken( aToken );
            return;
        }
    }
    void KSProcessor::ProcessToken( KSTokenEndParsing* aToken )
    {
        if( fChild == NULL )
        {
            if( ProcessEndToken( aToken ) == kFALSE )
            {
                iomsg + eError;
                iomsg < "KSProcessor::ReceiveToken";
                iomsg << "got unknown token: " << ret;
                iomsg << "in path <" << fTokenizer->GetFilePath() << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;
            }
            return;
        }
        else
        {
            if( ProcessStreamToken( aToken ) == kFALSE )
            {
                iomsg + eError;
                iomsg < "KSProcessor::ReceiveToken";
                iomsg << "got unknown token: " << ret;
                iomsg << "in path <" << fTokenizer->GetFilePath() << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;
            }
            fChild->ProcessToken( aToken );
            return;
        }
    }
    void KSProcessor::ProcessToken( KSTokenBeginFile* aToken )
    {
        if( fChild == NULL )
        {
            if( ProcessEndToken( aToken ) == kFALSE )
            {
                iomsg + eError;
                iomsg < "KSProcessor::ReceiveToken";
                iomsg << "got unknown token: " << ret;
                iomsg << "in path <" << fTokenizer->GetFilePath() << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;
            }
            return;
        }
        else
        {
            if( ProcessStreamToken( aToken ) == kFALSE )
            {
                iomsg + eError;
                iomsg < "KSProcessor::ReceiveToken";
                iomsg << "got unknown token: " << ret;
                iomsg << "in path <" << fTokenizer->GetFilePath() << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;
            }
            fChild->ProcessToken( aToken );
            return;
        }
    }
    void KSProcessor::ProcessToken( KSTokenEndFile* aToken )
    {
        if( fChild == NULL )
        {
            if( ProcessEndToken( aToken ) == kFALSE )
            {
                iomsg + eError;
                iomsg < "KSProcessor::ReceiveToken";
                iomsg << "got unknown token: " << ret;
                iomsg << "in path <" << fTokenizer->GetFilePath() << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;
            }
            return;
        }
        else
        {
            if( ProcessStreamToken( aToken ) == kFALSE )
            {
                iomsg + eError;
                iomsg < "KSProcessor::ReceiveToken";
                iomsg << "got unknown token: " << ret;
                iomsg << "in path <" << fTokenizer->GetFilePath() << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;
            }
            fChild->ProcessToken( aToken );
            return;
        }
    }
    void KSProcessor::ProcessToken( KSTokenBeginElement* aToken )
    {
        if( fChild == NULL )
        {
            if( ProcessEndToken( aToken ) == kFALSE )
            {
                iomsg + eError;
                iomsg < "KSProcessor::ReceiveToken";
                iomsg << "got unknown token: " << ret;
                iomsg << "in path <" << fTokenizer->GetFilePath() << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;
            }
            return;
        }
        else
        {
            if( ProcessStreamToken( aToken ) == kFALSE )
            {
                iomsg + eError;
                iomsg < "KSProcessor::ReceiveToken";
                iomsg << "got unknown token: " << ret;
                iomsg << "in path <" << fTokenizer->GetFilePath() << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;
            }
            fChild->ProcessToken( aToken );
            return;
        }
    }
    void KSProcessor::ProcessToken( KSTokenEndElement* aToken )
    {
        if( fChild == NULL )
        {
            if( ProcessEndToken( aToken ) == kFALSE )
            {
                iomsg + eError;
                iomsg < "KSProcessor::ReceiveToken";
                iomsg << "got unknown token: " << ret;
                iomsg << "in path <" << fTokenizer->GetFilePath() << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;
            }
            return;
        }
        else
        {
            if( ProcessStreamToken( aToken ) == kFALSE )
            {
                iomsg + eError;
                iomsg < "KSProcessor::ReceiveToken";
                iomsg << "got unknown token: " << ret;
                iomsg << "in path <" << fTokenizer->GetFilePath() << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;
            }
            fChild->ProcessToken( aToken );
            return;
        }
    }
    void KSProcessor::ProcessToken( KSTokenAttribute* aToken )
    {
        if( fChild == NULL )
        {
            if( ProcessEndToken( aToken ) == kFALSE )
            {
                iomsg + eError;
                iomsg < "KSProcessor::ReceiveToken";
                iomsg << "got unknown token: " << ret;
                iomsg << "in path <" << fTokenizer->GetFilePath() << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;
            }
            return;
        }
        else
        {
            if( ProcessStreamToken( aToken ) == kFALSE )
            {
                iomsg + eError;
                iomsg < "KSProcessor::ReceiveToken";
                iomsg << "got unknown token: " << ret;
                iomsg << "in path <" << fTokenizer->GetFilePath() << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;
            }
            fChild->ProcessToken( aToken );
            return;
        }
    }
    void KSProcessor::ProcessToken( KSTokenData* aToken )
    {
        if( fChild == NULL )
        {
            if( ProcessEndToken( aToken ) == kFALSE )
            {
                iomsg + eError;
                iomsg < "KSProcessor::ReceiveToken";
                iomsg << "got unknown token: " << ret;
                iomsg << "in path <" << fTokenizer->GetFilePath() << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;
            }
            return;
        }
        else
        {
            if( ProcessStreamToken( aToken ) == kFALSE )
            {
                iomsg + eError;
                iomsg < "KSProcessor::ReceiveToken";
                iomsg << "got unknown token: " << ret;
                iomsg << "in path <" << fTokenizer->GetFilePath() << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;
            }
            fChild->ProcessToken( aToken );
            return;
        }
    }
    void KSProcessor::ProcessToken( KSTokenError* aToken )
    {
        if( fChild == NULL )
        {
            if( ProcessEndToken( aToken ) == kFALSE )
            {
                iomsg + eError;
                iomsg < "KSProcessor::ReceiveToken";
                iomsg << "got unknown token: " << ret;
                iomsg << "in path <" << fTokenizer->GetFilePath() << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;
            }
            return;
        }
        else
        {
            if( ProcessStreamToken( aToken ) == kFALSE )
            {
                iomsg + eError;
                iomsg < "KSProcessor::ReceiveToken";
                iomsg << "got unknown token: " << ret;
                iomsg << "in path <" << fTokenizer->GetFilePath() << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;
            }
            fChild->ProcessToken( aToken );
            return;
        }
    }

    Bool_t KSProcessor::ProcessStreamToken( KSTokenBeginParsing* /*aToken*/)
    {
        return kTRUE;
    }
    Bool_t KSProcessor::ProcessStreamToken( KSTokenEndParsing* /*aToken*/)
    {
        return kTRUE;
    }
    Bool_t KSProcessor::ProcessStreamToken( KSTokenBeginFile* /*aToken*/)
    {
        return kTRUE;
    }
    Bool_t KSProcessor::ProcessStreamToken( KSTokenEndFile* /*aToken*/)
    {
        return kTRUE;
    }
    Bool_t KSProcessor::ProcessStreamToken( KSTokenBeginElement* /*aToken*/)
    {
        return kTRUE;
    }
    Bool_t KSProcessor::ProcessStreamToken( KSTokenEndElement* /*aToken*/)
    {
        return kTRUE;
    }
    Bool_t KSProcessor::ProcessStreamToken( KSTokenAttribute* /*aToken*/)
    {
        return kTRUE;
    }
    Bool_t KSProcessor::ProcessStreamToken( KSTokenData* /*aToken*/)
    {
        return kTRUE;
    }
    Bool_t KSProcessor::ProcessStreamToken( KSTokenError* /*aToken*/)
    {
        return kTRUE;
    }

    Bool_t KSProcessor::ProcessEndToken( KSTokenBeginParsing* /*aToken*/)
    {
        return kTRUE;
    }
    Bool_t KSProcessor::ProcessEndToken( KSTokenEndParsing* /*aToken*/)
    {
        return kTRUE;
    }
    Bool_t KSProcessor::ProcessEndToken( KSTokenBeginFile* /*aToken*/)
    {
        return kTRUE;
    }
    Bool_t KSProcessor::ProcessEndToken( KSTokenEndFile* /*aToken*/)
    {
        return kTRUE;
    }
    Bool_t KSProcessor::ProcessEndToken( KSTokenBeginElement* /*aToken*/)
    {
        return kTRUE;
    }
    Bool_t KSProcessor::ProcessEndToken( KSTokenEndElement* /*aToken*/)
    {
        return kTRUE;
    }
    Bool_t KSProcessor::ProcessEndToken( KSTokenAttribute* /*aToken*/)
    {
        return kTRUE;
    }
    Bool_t KSProcessor::ProcessEndToken( KSTokenData* /*aToken*/)
    {
        return kTRUE;
    }
    Bool_t KSProcessor::ProcessEndToken( KSTokenError* /*aToken*/)
    {
        return kTRUE;
    }

} /* namespace Kassiopeia */
