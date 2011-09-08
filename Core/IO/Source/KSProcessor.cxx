#include "KSProcessor.h"

#include "KSTokenizer.h"

//#include <iostream>
//using std::cout;
//using std::endl;

namespace Kassiopeia
{

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
            if( EndProcessToken( aToken ) == kFALSE )
            {
                //iomsg = eError;
                //iomsg < GetTypeName() + "::ReceiveToken";
                // << "got unknown token: " << ret;
                //iomsg << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << end;
            }
            return;
        }
        else
        {
            if( MidProcessToken( aToken ) == kFALSE )
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
            if( EndProcessToken( aToken ) == kFALSE )
            {
                //iomsg = eError;
                //iomsg < GetTypeName() + "::ReceiveToken";
                // << "got unknown token: " << ret;
                //iomsg << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << end;
            }
            return;
        }
        else
        {
            if( MidProcessToken( aToken ) == kFALSE )
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
            if( EndProcessToken( aToken ) == kFALSE )
            {
                //iomsg = eError;
                //iomsg < GetTypeName() + "::ReceiveToken";
                // << "got unknown token: " << ret;
                //iomsg << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << end;
            }
            return;
        }
        else
        {
            if( MidProcessToken( aToken ) == kFALSE )
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
            if( EndProcessToken( aToken ) == kFALSE )
            {
                //iomsg = eError;
                //iomsg < GetTypeName() + "::ReceiveToken";
                // << "got unknown token: " << ret;
                //iomsg << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << end;
            }
            return;
        }
        else
        {
            if( MidProcessToken( aToken ) == kFALSE )
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
            if( EndProcessToken( aToken ) == kFALSE )
            {
                //iomsg = eError;
                //iomsg < GetTypeName() + "::ReceiveToken";
                // << "got unknown token: " << ret;
                //iomsg << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << end;
            }
            return;
        }
        else
        {
            if( MidProcessToken( aToken ) == kFALSE )
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
            if( EndProcessToken( aToken ) == kFALSE )
            {
                //iomsg = eError;
                //iomsg < GetTypeName() + "::ReceiveToken";
                // << "got unknown token: " << ret;
                //iomsg << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << end;
            }
            return;
        }
        else
        {
            if( MidProcessToken( aToken ) == kFALSE )
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
            if( EndProcessToken( aToken ) == kFALSE )
            {
                //iomsg = eError;
                //iomsg < GetTypeName() + "::ReceiveToken";
                // << "got unknown token: " << ret;
                //iomsg << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << end;
            }
            return;
        }
        else
        {
            if( MidProcessToken( aToken ) == kFALSE )
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
            if( EndProcessToken( aToken ) == kFALSE )
            {
                //iomsg = eError;
                //iomsg < GetTypeName() + "::ReceiveToken";
                // << "got unknown token: " << ret;
                //iomsg << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << end;
            }
            return;
        }
        else
        {
            if( MidProcessToken( aToken ) == kFALSE )
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
            if( EndProcessToken( aToken ) == kFALSE )
            {
                //iomsg = eError;
                //iomsg < GetTypeName() + "::ReceiveToken";
                // << "got unknown token: " << ret;
                //iomsg << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << end;
            }
            return;
        }
        else
        {
            if( MidProcessToken( aToken ) == kFALSE )
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

    Bool_t KSProcessor::MidProcessToken( const KSTokenBeginParsing* /*aToken*/)
    {
        return kFALSE;
    }
    Bool_t KSProcessor::MidProcessToken( const KSTokenEndParsing* /*aToken*/)
    {
        return kFALSE;
    }
    Bool_t KSProcessor::MidProcessToken( const KSTokenBeginFile* /*aToken*/)
    {
        return kFALSE;
    }
    Bool_t KSProcessor::MidProcessToken( const KSTokenEndFile* /*aToken*/)
    {
        return kFALSE;
    }
    Bool_t KSProcessor::MidProcessToken( const KSTokenBeginElement* /*aToken*/)
    {
        return kFALSE;
    }
    Bool_t KSProcessor::MidProcessToken( const KSTokenEndElement* /*aToken*/)
    {
        return kFALSE;
    }
    Bool_t KSProcessor::MidProcessToken( const KSTokenAttribute* /*aToken*/)
    {
        return kFALSE;
    }
    Bool_t KSProcessor::MidProcessToken( const KSTokenData* /*aToken*/)
    {
        return kFALSE;
    }
    Bool_t KSProcessor::MidProcessToken( const KSTokenError* /*aToken*/)
    {
        return kFALSE;
    }

    Bool_t KSProcessor::EndProcessToken( const KSTokenBeginParsing* /*aToken*/)
    {
        return kFALSE;
    }
    Bool_t KSProcessor::EndProcessToken( const KSTokenEndParsing* /*aToken*/)
    {
        return kFALSE;
    }
    Bool_t KSProcessor::EndProcessToken( const KSTokenBeginFile* /*aToken*/)
    {
        return kFALSE;
    }
    Bool_t KSProcessor::EndProcessToken( const KSTokenEndFile* /*aToken*/)
    {
        return kFALSE;
    }
    Bool_t KSProcessor::EndProcessToken( const KSTokenBeginElement* /*aToken*/)
    {
        return kFALSE;
    }
    Bool_t KSProcessor::EndProcessToken( const KSTokenEndElement* /*aToken*/)
    {
        return kFALSE;
    }
    Bool_t KSProcessor::EndProcessToken( const KSTokenAttribute* /*aToken*/)
    {
        return kFALSE;
    }
    Bool_t KSProcessor::EndProcessToken( const KSTokenData* /*aToken*/)
    {
        return kFALSE;
    }
    Bool_t KSProcessor::EndProcessToken( const KSTokenError* /*aToken*/)
    {
        return kFALSE;
    }

} /* namespace Kassiopeia */
