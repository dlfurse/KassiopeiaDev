#include "KSProcessor.h"

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

    void KSProcessor::ProcessToken( const KSTokenBeginParsing* aToken )
    {
        if( fChild == NULL )
        {
            if( ProcessEndToken( aToken ) == kFALSE )
            {
                //iomsg = eError;
                //iomsg < GetTypeName() + "::ReceiveToken";
                //iomsg << "got unknown token: " << ret;
                //iomsg << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << end;
            }
            return;
        }
        else
        {
            if( ProcessStreamToken( aToken ) == kFALSE )
            {
                //iomsg = eError;
                //iomsg < GetTypeName() + "::ReceiveToken";
                //iomsg << "got unknown token: " << ret;
                //iomsg << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << end;
            }
            fChild->ProcessToken( aToken );
            return;
        }
    }
    void KSProcessor::ProcessToken( const KSTokenEndParsing* aToken )
    {
        if( fChild == NULL )
        {
            if( ProcessEndToken( aToken ) == kFALSE )
            {
                //iomsg = eError;
                //iomsg < GetTypeName() + "::ReceiveToken";
                //iomsg << "got unknown token: " << ret;
                //iomsg << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << end;
            }
            return;
        }
        else
        {
            if( ProcessStreamToken( aToken ) == kFALSE )
            {
                //iomsg = eError;
                //iomsg < GetTypeName() + "::ReceiveToken";
                //iomsg << "got unknown token: " << ret;
                //iomsg << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << end;
            }
            fChild->ProcessToken( aToken );
            return;
        }
    }
    void KSProcessor::ProcessToken( const KSTokenBeginFile* aToken )
    {
        if( fChild == NULL )
        {
            if( ProcessEndToken( aToken ) == kFALSE )
            {
                //iomsg = eError;
                //iomsg < GetTypeName() + "::ReceiveToken";
                //iomsg << "got unknown token: " << ret;
                //iomsg << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << end;
            }
            return;
        }
        else
        {
            if( ProcessStreamToken( aToken ) == kFALSE )
            {
                //iomsg = eError;
                //iomsg < GetTypeName() + "::ReceiveToken";
                //iomsg << "got unknown token: " << ret;
                //iomsg << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << end;
            }
            fChild->ProcessToken( aToken );
            return;
        }
    }
    void KSProcessor::ProcessToken( const KSTokenEndFile* aToken )
    {
        if( fChild == NULL )
        {
            if( ProcessEndToken( aToken ) == kFALSE )
            {
                //iomsg = eError;
                //iomsg < GetTypeName() + "::ReceiveToken";
                //iomsg << "got unknown token: " << ret;
                //iomsg << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << end;
            }
            return;
        }
        else
        {
            if( ProcessStreamToken( aToken ) == kFALSE )
            {
                //iomsg = eError;
                //iomsg < GetTypeName() + "::ReceiveToken";
                //iomsg << "got unknown token: " << ret;
                //iomsg << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << end;
            }
            fChild->ProcessToken( aToken );
            return;
        }
    }
    void KSProcessor::ProcessToken( const KSTokenBeginElement* aToken )
    {
        if( fChild == NULL )
        {
            if( ProcessEndToken( aToken ) == kFALSE )
            {
                //iomsg = eError;
                //iomsg < GetTypeName() + "::ReceiveToken";
                //iomsg << "got unknown token: " << ret;
                //iomsg << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << end;
            }
            return;
        }
        else
        {
            if( ProcessStreamToken( aToken ) == kFALSE )
            {
                //iomsg = eError;
                //iomsg < GetTypeName() + "::ReceiveToken";
                //iomsg << "got unknown token: " << ret;
                //iomsg << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << end;
            }
            fChild->ProcessToken( aToken );
            return;
        }
    }
    void KSProcessor::ProcessToken( const KSTokenEndElement* aToken )
    {
        if( fChild == NULL )
        {
            if( ProcessEndToken( aToken ) == kFALSE )
            {
                //iomsg = eError;
                //iomsg < GetTypeName() + "::ReceiveToken";
                //iomsg << "got unknown token: " << ret;
                //iomsg << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << end;
            }
            return;
        }
        else
        {
            if( ProcessStreamToken( aToken ) == kFALSE )
            {
                //iomsg = eError;
                //iomsg < GetTypeName() + "::ReceiveToken";
                //iomsg << "got unknown token: " << ret;
                //iomsg << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << end;
            }
            fChild->ProcessToken( aToken );
            return;
        }
    }
    void KSProcessor::ProcessToken( const KSTokenAttribute* aToken )
    {
        if( fChild == NULL )
        {
            if( ProcessEndToken( aToken ) == kFALSE )
            {
                //iomsg = eError;
                //iomsg < GetTypeName() + "::ReceiveToken";
                //iomsg << "got unknown token: " << ret;
                //iomsg << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << end;
            }
            return;
        }
        else
        {
            if( ProcessStreamToken( aToken ) == kFALSE )
            {
                //iomsg = eError;
                //iomsg < GetTypeName() + "::ReceiveToken";
                //iomsg << "got unknown token: " << ret;
                //iomsg << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << end;
            }
            fChild->ProcessToken( aToken );
            return;
        }
    }
    void KSProcessor::ProcessToken( const KSTokenData* aToken )
    {
        if( fChild == NULL )
        {
            if( ProcessEndToken( aToken ) == kFALSE )
            {
                //iomsg = eError;
                //iomsg < GetTypeName() + "::ReceiveToken";
                //iomsg << "got unknown token: " << ret;
                //iomsg << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << end;
            }
            return;
        }
        else
        {
            if( ProcessStreamToken( aToken ) == kFALSE )
            {
                //iomsg = eError;
                //iomsg < GetTypeName() + "::ReceiveToken";
                //iomsg << "got unknown token: " << ret;
                //iomsg << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << end;
            }
            fChild->ProcessToken( aToken );
            return;
        }
    }
    void KSProcessor::ProcessToken( const KSTokenError* aToken )
    {
        if( fChild == NULL )
        {
            if( ProcessEndToken( aToken ) == kFALSE )
            {
                //iomsg = eError;
                //iomsg < GetTypeName() + "::ReceiveToken";
                //iomsg << "got unknown token: " << ret;
                //iomsg << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << end;
            }
            return;
        }
        else
        {
            if( ProcessStreamToken( aToken ) == kFALSE )
            {
                //iomsg = eError;
                //iomsg < GetTypeName() + "::ReceiveToken";
                //iomsg << "got unknown token: " << ret;
                //iomsg << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << end;
            }
            fChild->ProcessToken( aToken );
            return;
        }
    }

    Bool_t KSProcessor::ProcessStreamToken( const KSTokenBeginParsing* /*aToken*/)
    {
        return kTRUE;
    }
    Bool_t KSProcessor::ProcessStreamToken( const KSTokenEndParsing* /*aToken*/)
    {
        return kTRUE;
    }
    Bool_t KSProcessor::ProcessStreamToken( const KSTokenBeginFile* /*aToken*/)
    {
        return kTRUE;
    }
    Bool_t KSProcessor::ProcessStreamToken( const KSTokenEndFile* /*aToken*/)
    {
        return kTRUE;
    }
    Bool_t KSProcessor::ProcessStreamToken( const KSTokenBeginElement* /*aToken*/)
    {
        return kTRUE;
    }
    Bool_t KSProcessor::ProcessStreamToken( const KSTokenEndElement* /*aToken*/)
    {
        return kTRUE;
    }
    Bool_t KSProcessor::ProcessStreamToken( const KSTokenAttribute* /*aToken*/)
    {
        return kTRUE;
    }
    Bool_t KSProcessor::ProcessStreamToken( const KSTokenData* /*aToken*/)
    {
        return kTRUE;
    }
    Bool_t KSProcessor::ProcessStreamToken( const KSTokenError* /*aToken*/)
    {
        return kTRUE;
    }

    Bool_t KSProcessor::ProcessEndToken( const KSTokenBeginParsing* /*aToken*/)
    {
        return kFALSE;
    }
    Bool_t KSProcessor::ProcessEndToken( const KSTokenEndParsing* /*aToken*/)
    {
        return kFALSE;
    }
    Bool_t KSProcessor::ProcessEndToken( const KSTokenBeginFile* /*aToken*/)
    {
        return kFALSE;
    }
    Bool_t KSProcessor::ProcessEndToken( const KSTokenEndFile* /*aToken*/)
    {
        return kFALSE;
    }
    Bool_t KSProcessor::ProcessEndToken( const KSTokenBeginElement* /*aToken*/)
    {
        return kFALSE;
    }
    Bool_t KSProcessor::ProcessEndToken( const KSTokenEndElement* /*aToken*/)
    {
        return kFALSE;
    }
    Bool_t KSProcessor::ProcessEndToken( const KSTokenAttribute* /*aToken*/)
    {
        return kFALSE;
    }
    Bool_t KSProcessor::ProcessEndToken( const KSTokenData* /*aToken*/)
    {
        return kFALSE;
    }
    Bool_t KSProcessor::ProcessEndToken( const KSTokenError* /*aToken*/)
    {
        return kFALSE;
    }

} /* namespace Kassiopeia */
