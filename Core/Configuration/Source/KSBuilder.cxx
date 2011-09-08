#include "KSBuilder.h"

#include "KSIOMessage.h"

//#include <iostream>
//using std::cout;
//using std::endl;

namespace Kassiopeia
{

    KSBuilder::KSBuilder() :
        fTokenizer( NULL ),
        fParent( NULL ),
        fChild( NULL )
    {
    }
    KSBuilder::~KSBuilder()
    {
        //cout << "(" << this << ") i am like dying homes" << endl;
    }

    void KSBuilder::SetTokenizer( KSTokenizer* tokenizer )
    {
        fTokenizer = tokenizer;
        return;
    }
    void KSBuilder::DropBuilder( KSBuilder* const newbuild )
    {
        //cout << "(" << this << ") dropping a builder of type " << newbuild->GetTypeName() << endl;
        if( fChild == NULL )
        {
            fChild = newbuild;
            fChild->SetParent( this );
            return;
        }
        fChild->DropBuilder( newbuild );
        return;
    }
    void KSBuilder::LiftBuilder( KSBuilder* const oldbuild )
    {
        //cout << "(" << this << ") lifting a builder of type " << oldbuild->GetTypeName() << endl;
        if( fChild == NULL )
        {
            if( ProcessBuilder( oldbuild ) == kFALSE )
            {
                iomsg = eError;
                iomsg < this->GetTypeName() + "::LiftBuilder";
                iomsg << "got unknown nested builder: <" << oldbuild->GetTypeName() << ">" << ret;
                iomsg << "in file <" << fTokenizer->GetCurrentFileName() << "> at line <" << fTokenizer->GetCurrentLineNumber() << ">, column <" << fTokenizer->GetCurrentColumnNumber() << ">" << end;
            }
        }

        if( fParent == NULL )
        {
            delete oldbuild;
            return;
        }
        else
        {
            fParent->LiftBuilder( oldbuild );
            return;
        }
    }

    void KSBuilder::ReceiveToken( const KSErrorToken* token )
    {
        if( fChild == NULL )
        {
            if( ProcessToken( token ) == kFALSE )
            {
                iomsg = eError;
                iomsg < GetTypeName() + "::ReceiveToken";
                iomsg << "got unknown error: " << token->GetMessage() << ret;
                iomsg << "in file <" << fTokenizer->GetCurrentFileName() << "> at line <" << fTokenizer->GetCurrentLineNumber() << ">, column <" << fTokenizer->GetCurrentColumnNumber() << ">" << end;
            }
            return;
        }
        else
        {
            fChild->ReceiveToken( token );
            return;
        }
    }
    void KSBuilder::ReceiveToken( const KSTokenBeginParsing* token )
    {
        if( fChild == NULL )
        {
            if( ProcessToken( token ) == kFALSE )
            {
                iomsg = eError;
                iomsg < GetTypeName() + "::ReceiveToken";
                iomsg << "got unknown begin parsing mark" << ret;
                iomsg << "in file <" << fTokenizer->GetCurrentFileName() << "> at line <" << fTokenizer->GetCurrentLineNumber() << ">, column <" << fTokenizer->GetCurrentColumnNumber() << ">" << end;
            }
            return;
        }
        else
        {
            fChild->ReceiveToken( token );
            return;
        }
    }
    void KSBuilder::ReceiveToken( const KSTokenEndParsing* token )
    {
        if( fChild == NULL )
        {
            if( ProcessToken( token ) == kFALSE )
            {
                iomsg = eError;
                iomsg < GetTypeName() + "::ReceiveToken";
                iomsg << "got unknown end parsing mark" << ret;
                iomsg << "in file <" << fTokenizer->GetCurrentFileName() << "> at line <" << fTokenizer->GetCurrentLineNumber() << ">, column <" << fTokenizer->GetCurrentColumnNumber() << ">" << end;
            }
            return;
        }
        else
        {
            fChild->ReceiveToken( token );
            return;
        }
    }
    void KSBuilder::ReceiveToken( const KSTokenBeginFile* token )
    {
        if( fChild == NULL )
        {
            if( ProcessToken( token ) == kFALSE )
            {
                iomsg = eError;
                iomsg < GetTypeName() + "::ReceiveToken";
                iomsg << "got unknown begin file mark" << ret;
                iomsg << "in file <" << fTokenizer->GetCurrentFileName() << "> at line <" << fTokenizer->GetCurrentLineNumber() << ">, column <" << fTokenizer->GetCurrentColumnNumber() << ">" << end;
            }
            return;
        }
        else
        {
            fChild->ReceiveToken( token );
            return;
        }
    }
    void KSBuilder::ReceiveToken( const KSTokenEndFile* token )
    {
        if( fChild == NULL )
        {
            if( ProcessToken( token ) == kFALSE )
            {
                iomsg = eError;
                iomsg < GetTypeName() + "::ReceiveToken";
                iomsg << "got unknown end file mark" << ret;
                iomsg << "in file <" << fTokenizer->GetCurrentFileName() << "> at line <" << fTokenizer->GetCurrentLineNumber() << ">, column <" << fTokenizer->GetCurrentColumnNumber() << ">" << end;
            }
            return;
        }
        else
        {
            fChild->ReceiveToken( token );
            return;
        }
    }

    void KSBuilder::ReceiveToken( const KSPseudoBeginToken* token )
    {
        if( fChild == NULL )
        {
            if( ProcessToken( token ) == kFALSE )
            {
                iomsg = eError;
                iomsg < GetTypeName() + "::ReceiveToken";
                iomsg << "got unknown begin token: <" << token->GetValue() << ">" << ret;
                iomsg << "in file <" << fTokenizer->GetCurrentFileName() << "> at line <" << fTokenizer->GetCurrentLineNumber() << ">, column <" << fTokenizer->GetCurrentColumnNumber() << ">" << end;
            }
            return;
        }
        else
        {
            fChild->ReceiveToken( token );
            return;
        }
    }
    void KSBuilder::ReceiveToken( const KSPseudoParameterToken* token )
    {
        if( fChild == NULL )
        {
            if( ProcessSystemAttributes( token ) ) return;
            if( ProcessToken( token ) == kFALSE )
            {
                iomsg = eError;
                iomsg < GetTypeName() + "::ReceiveToken";
                iomsg << "got unknown parameter token: <<" << token->GetName() << "=" << token->GetValue() << ">>\n";
                iomsg << "in file <" << fTokenizer->GetCurrentFileName() << "> at line <" << fTokenizer->GetCurrentLineNumber() << ">, column <" << fTokenizer->GetCurrentColumnNumber() << ">" << end;
            }
            return;
        }
        else
        {
            fChild->ReceiveToken( token );
            return;
        }
    }
    void KSBuilder::ReceiveToken( const KSPseudoEndToken* token )
    {
        if( fChild == NULL )
        {
            if( ProcessToken( token ) == kFALSE )
            {
                iomsg = eError;
                iomsg < GetTypeName() + "::ReceiveToken";
                iomsg << "got unknown end token: <" << token->GetValue() << ">" << ret;
                iomsg << "in file <" << fTokenizer->GetCurrentFileName() << "> at line <" << fTokenizer->GetCurrentLineNumber() << ">, column <" << fTokenizer->GetCurrentColumnNumber() << ">" << end;
            }
            fParent->SetChild( NULL );
            fParent->LiftBuilder( this );
            return;

        }
        else
        {
            fChild->ReceiveToken( token );
            return;
        }
    }
    void KSBuilder::ReceiveToken( const KSPseudoKeywordToken* token )
    {
        if( fChild == NULL )
        {
            if( ProcessToken( token ) == kFALSE )
            {
                iomsg = eError;
                iomsg < GetTypeName() + "::ReceiveToken";
                iomsg << "got unknown keyword token: @" << token->GetKeyword() << "(";
                for( vector< string >::const_iterator It = token->GetParameters().begin(); It != (token->GetParameters().end() - 1); It++ )
                {
                    iomsg << *It << ",";
                }
                iomsg << *(token->GetParameters().end() - 1) << ")\n";
                iomsg << "in file <" << fTokenizer->GetCurrentFileName() << "> at line <" << fTokenizer->GetCurrentLineNumber() << ">, column <" << fTokenizer->GetCurrentColumnNumber() << ">" << end;
            }
            return;
        }
        else
        {
            fChild->ReceiveToken( token );
            return;
        }
    }
    void KSBuilder::ReceiveToken( const KSPseudoErrorToken* token )
    {
        if( fChild == NULL )
        {
            if( ProcessToken( token ) == kFALSE )
            {
                iomsg = eError;
                iomsg < GetTypeName() + "::ReceiveToken";
                iomsg << "A parsing or file error occurred: <" << token->GetMessage() << ">" << ret;
                iomsg << "in file <" << fTokenizer->GetCurrentFileName() << "> at line <" << fTokenizer->GetCurrentLineNumber() << ">, column <" << fTokenizer->GetCurrentColumnNumber() << ">" << end;
            }
            return;

        }
        else
        {
            fChild->ReceiveToken( token );
            return;
        }
    }

    void KSBuilder::ReceiveToken( const KSTokenBeginElement* token )
    {
        if( fChild == NULL )
        {
            if( ProcessToken( token ) == kFALSE )
            {
                iomsg = eError;
                iomsg < GetTypeName() + "::ReceiveToken";
                iomsg << "got unknown start element token: <" << token->GetElementName() << " ...\n";
                iomsg << "in file <" << fTokenizer->GetCurrentFileName() << "> at line <" << fTokenizer->GetCurrentLineNumber() << ">, column <" << fTokenizer->GetCurrentColumnNumber() << ">" << end;
            }
            return;
        }
        else
        {
            fChild->ReceiveToken( token );
            return;
        }
    }
    void KSBuilder::ReceiveToken( const KSTokenAttribute* token )
    {
        if( fChild == NULL )
        {
            if( ProcessSystemAttributes( token ) ) return;
            if( ProcessToken( token ) == kFALSE )
            {
                iomsg = eError;
                iomsg < GetTypeName() + "::ReceiveToken";
                iomsg << "got unknown attribute token: " << token->GetAttributeName() << "=\"" << token->GetAttributeValue() << "\"\n";
                iomsg << "in file <" << fTokenizer->GetCurrentFileName() << "> at line <" << fTokenizer->GetCurrentLineNumber() << ">, column <" << fTokenizer->GetCurrentColumnNumber() << ">" << end;
            }
            return;
        }
        else
        {
            fChild->ReceiveToken( token );
            return;
        }
    }
    void KSBuilder::ReceiveToken( const KSTokenEndElement* token )
    {
        if( fChild == NULL )
        {
            if( ProcessToken( token ) == kFALSE )
            {
                iomsg = eError;
                iomsg < GetTypeName() + "::ReceiveToken";
                iomsg << "got unknown end element token: </" << token->GetElementName() << ">" << ret;
                iomsg << "in file <" << fTokenizer->GetCurrentFileName() << "> at line <" << fTokenizer->GetCurrentLineNumber() << ">, column <" << fTokenizer->GetCurrentColumnNumber() << ">" << end;
            }
            fParent->SetChild( NULL );
            fParent->LiftBuilder( this );
            return;
        }
        else
        {
            fChild->ReceiveToken( token );
            return;
        }
    }
    void KSBuilder::ReceiveToken( const KSTokenData* token )
    {
        if( fChild == NULL )
        {
            if( ProcessToken( token ) == kFALSE )
            {
                iomsg = eError;
                iomsg < GetTypeName() + "::ReceiveToken";
                iomsg << "got unknown data token: " << token->GetDataValue() << ret;
                iomsg << "in file <" << fTokenizer->GetCurrentFileName() << "> at line <" << fTokenizer->GetCurrentLineNumber() << ">, column <" << fTokenizer->GetCurrentColumnNumber() << ">" << end;
            }
            return;
        }
        else
        {
            fChild->ReceiveToken( token );
            return;
        }
    }
    void KSBuilder::ReceiveToken( const KSTokenError* token )
    {
        if( fChild == NULL )
        {
            if( ProcessToken( token ) == kFALSE )
            {
                iomsg = eError;
                iomsg < GetTypeName() + "::ReceiveToken";
                iomsg << "A parsing or file error occurred: " << token->GetMessage() << ret;
                iomsg << "in file <" << fTokenizer->GetCurrentFileName() << "> at line <" << fTokenizer->GetCurrentLineNumber() << ">, column <" << fTokenizer->GetCurrentColumnNumber() << ">" << end;
            }
            return;
        }
        else
        {
            fChild->ReceiveToken( token );
            return;
        }
    }

    Bool_t KSBuilder::ProcessToken( const KSErrorToken* /*token*/)
    {
        return kFALSE;
    }
    Bool_t KSBuilder::ProcessToken( const KSTokenBeginParsing* /*token*/)
    {
        return kFALSE;
    }
    Bool_t KSBuilder::ProcessToken( const KSTokenEndParsing* /*token*/)
    {
        return kFALSE;
    }
    Bool_t KSBuilder::ProcessToken( const KSTokenBeginFile* /*token*/)
    {
        return kFALSE;
    }
    Bool_t KSBuilder::ProcessToken( const KSTokenEndFile* /*token*/)
    {
        return kFALSE;
    }

    Bool_t KSBuilder::ProcessToken( const KSPseudoBeginToken* /*token*/)
    {
        return kFALSE;
    }
    Bool_t KSBuilder::ProcessToken( const KSPseudoParameterToken* /*token*/)
    {
        return kFALSE;
    }
    Bool_t KSBuilder::ProcessToken( const KSPseudoEndToken* /*token*/)
    {
        return kFALSE;
    }
    Bool_t KSBuilder::ProcessToken( const KSPseudoKeywordToken* /*token*/)
    {
        return kFALSE;
    }
    Bool_t KSBuilder::ProcessToken( const KSPseudoErrorToken* /*token*/)
    {
        return kFALSE;
    }

    Bool_t KSBuilder::ProcessToken( const KSTokenBeginElement* /*token*/)
    {
        return kFALSE;
    }
    Bool_t KSBuilder::ProcessToken( const KSTokenAttribute* /*token*/)
    {
        return kFALSE;
    }
    Bool_t KSBuilder::ProcessToken( const KSTokenEndElement* /*token*/)
    {
        return kFALSE;
    }
    Bool_t KSBuilder::ProcessToken( const KSTokenData* /*token*/)
    {
        return kFALSE;
    }
    Bool_t KSBuilder::ProcessToken( const KSTokenError* /*token*/)
    {
        return kFALSE;
    }

    Bool_t KSBuilder::ProcessBuilder( const KSBuilder* /*builder*/)
    {
        return kFALSE;
    }

    Bool_t KSBuilder::ProcessSystemAttributes( const KSPseudoParameterToken* /*token*/)
    {
        return kFALSE;
    }

    Bool_t KSBuilder::ProcessSystemAttributes( const KSTokenAttribute* /*token*/)
    {
        return kFALSE;
    }

    const KSBuilder* KSBuilder::GetParent() const
    {
        return fParent;
    }

    const KSBuilder* KSBuilder::GetChild() const
    {
        return fChild;
    }

    void KSBuilder::SetParent( KSBuilder* const parent )
    {
        //cout << "(" << this << ") parent set to " << parent << endl;
        fParent = parent;
        return;
    }
    void KSBuilder::SetChild( KSBuilder* const child )
    {
        //cout << "(" << this << ") child set to " << child << endl;
        fChild = child;
        return;
    }

}
