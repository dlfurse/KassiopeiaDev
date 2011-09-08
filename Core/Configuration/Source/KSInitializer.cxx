/*
 * KSInitializer.cxx
 *
 * created on: Apr 11, 2011
 * author: dlfurse
 */

#include "KSInitializer.h"

#include "KLMessage.h"

namespace Kassiopeia
{

    KSInitializer::KSInitializer() :
        fMap( NULL ), fMapIt()
    {
    }

    KSInitializer::~KSInitializer()
    {
        //if( fTokenizer != NULL )
        //{
        //    delete fTokenizer;
        //    fTokenizer = NULL;
        //}

        if( fMap != NULL )
        {
            delete fMap;
            fMap = NULL;
        }
    }

    void KSInitializer::Read( const string& filename )
    {
        fMap = KSBuilderFactoryTable::GetInstance()->GetMap( GetSystemName() );

        if( fMap == NULL )
        {
            klmsg < "KSInitializer::Read";
            klmsg( KLMessage::eFatalError ) << "Could not find any builders listed under system name <" << GetSystemName() << ">!" << eom;
            return;
        }

        if( fTokenizer == NULL )
        {
            klmsg < "KSInitializer::Read";
            klmsg( KLMessage::eFatalError ) << "Cannot read file without a tokenizer installed!" << eom;
            return;
        }

        fTokenizer->SetReceiver( this );
        fTokenizer->Read( filename );

        return;
    }

    void KSInitializer::ReceiveToken( const KSPseudoBeginToken* token )
    {
        fMapIt = fMap->find( token->GetValue() );

        if( fMapIt == fMap->end() )
        {
            klmsg < "KSInitializer::ReceiveToken";
            klmsg( KLMessage::eFatalError ) << "Could not find a builder factory called <" << token->GetValue() << "> registered for system <" << GetSystemName() << "> !" << eom;
            return;
        }

        KSBuilder* NewBuilder = fMapIt->second->Build();

        if( NewBuilder == 0 )
        {
            klmsg < "KSInitializer::ReceiveToken";
            klmsg( KLMessage::eFatalError ) << "Builder factory called <" << token->GetValue() << "> registered for system <" << token->GetSystemName() << "> built nothing!" << eom;
            return;
        }

        NewBuilder->SetTokenizer( fTokenizer );
        DropBuilder( NewBuilder );
        delete token;
        return;
    }

    void KSInitializer::ReceiveToken( const KSTokenBeginElement* token )
    {
        fMapIt = fMap->find( token->GetElementName() );

        if( fMapIt == fMap->end() )
        {
            klmsg < "KSInitializer::ReceiveToken";
            klmsg( KLMessage::eFatalError ) << "Could not find a builder factory called <" << token->GetElementName() << "> registered for system <" << GetSystemName() << "> !" << eom;
            return;
        }

        KSBuilder* NewBuilder = fMapIt->second->Build();

        if( NewBuilder == 0 )
        {
            klmsg < "KSInitializer::ReceiveToken";
            klmsg( KLMessage::eFatalError ) << "Builder factory called <" << token->GetElementName() << "> registered for system <" << token->GetSystemName() << "> built nothing!" << eom;
            return;
        }

        NewBuilder->SetTokenizer( fTokenizer );
        DropBuilder( NewBuilder );
        delete token;
        return;
    }

    Bool_t KSInitializer::ProcessBuilder( const KSBuilder* /*builder*/)
    {
        return kTRUE;
    }

}
