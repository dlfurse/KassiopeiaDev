#include "KSLoopProcessor.h"

#include "KSTokenizer.h"

#include "KSIOMessage.h"

namespace Kassiopeia
{

    KSLoopProcessor::KSLoopProcessor() :
        KSProcessor(),
        fLoopStack()
    {
        Reset();
    }

    KSLoopProcessor::~KSLoopProcessor()
    {
    }

    void KSLoopProcessor::ProcessToken( KSTokenBeginElement* aToken )
    {
        if( fState == eInactive )
        {
            if( aToken->GetElementName() == string( "loop" ) )
            {
                fCount++;

                if( fCount == 1 )
                {

                    fState = eActive;
                    return;
                }
            }

            KSProcessor::ProcessToken( aToken );
            return;
        }

        //trigger
        if( fState == eActive )
        {
            //hijack the tokenizer
            fTokenizer->PushContext( this );

            //collect trigger
            fState = eCollecting;
            ProcessToken( aToken );
            return;
        }

        //collect
        if( fState == eCollecting )
        {
            if( aToken->GetElementName() == string( "loop" ) )
            {
                fCount++;
            }
            fTokens.push_back( new KSTokenBeginElement( *aToken ) );
            return;
        }

        iomsg + eWarning;
        iomsg < "KSLoopProcessor::ProcessToken";
        iomsg << "got unknown element <" << aToken->GetElementName() << ">" << ret;
        iomsg << "in path <" << fTokenizer->GetFilePath() << "> in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;

        for( TokenIt It = fTokens.begin(); It != fTokens.end(); It++ )
        {
            delete *It;
        }
        Reset();

        return;
    }
    void KSLoopProcessor::ProcessToken( KSTokenEndElement* aToken )
    {
        if( fState == eInactive )
        {
            //just forward
            KSProcessor::ProcessToken( aToken );
            return;
        }

        if( fState == eActive )
        {
            //this means a loop was written with no contents
            Reset();
            return;
        }

        if( fState == eCollecting )
        {
            //see if the end element is a loop; if so, decrease the loop counter
            if( aToken->GetElementName() == string( "loop" ) )
            {
                fCount--;

                //if we're at the end of the loop counter
                if( fCount == 0 )
                {
                    //un-hijack the tokenizer
                    fTokenizer->PopContext();

                    //copy the state into stack variables and reset (otherwise nesting is not possible)
                    string Variable = fVariable;
                    Int_t Start = fStartValue;
                    Int_t End = fEndValue;
                    Int_t Step = fStepValue;
                    TokenVector Tokens = fTokens;
                    Reset();

                    //utilities
                    Int_t LoopIndex;
                    stringstream Converter;
                    KSTokenBeginElement BeginElement;
                    KSTokenAttribute Attribute;
                    KSTokenEndElement EndElement;

                    //run the loop
                    if( Step > 0 )
                    {
                        for( LoopIndex = Start; LoopIndex <= End; LoopIndex += Step )
                        {
                            BeginElement.SetElementName( "define" );
                            fTokenizer->ProcessToken( &BeginElement );

                            Attribute.SetAttributeName( "name" );
                            Attribute.SetAttributeValue( Variable );
                            fTokenizer->ProcessToken( &Attribute );

                            Converter.clear();
                            Converter.str( "" );
                            Converter << LoopIndex;
                            Attribute.SetAttributeName( "value" );
                            Attribute.SetAttributeValue( Converter.str() );
                            fTokenizer->ProcessToken( &Attribute );

                            EndElement.SetElementName( "define" );
                            fTokenizer->ProcessToken( &EndElement );

                            for( TokenIt It = Tokens.begin(); It != Tokens.end(); It++ )
                            {
                                Dispatch( *It );
                            }

                            BeginElement.SetElementName( "undefine" );
                            fTokenizer->ProcessToken( &BeginElement );

                            Attribute.SetAttributeName( "name" );
                            Attribute.SetAttributeValue( Variable );
                            fTokenizer->ProcessToken( &Attribute );

                            EndElement.SetElementName( "undefine" );
                            fTokenizer->ProcessToken( &EndElement );
                        }
                    }
                    else if( Step < 0 )
                    {
                        for( LoopIndex = Start; LoopIndex >= End; LoopIndex += Step )
                        {
                            BeginElement.SetElementName( "define" );
                            fTokenizer->ProcessToken( &BeginElement );

                            Attribute.SetAttributeName( "name" );
                            Attribute.SetAttributeValue( Variable );
                            fTokenizer->ProcessToken( &Attribute );

                            Converter.clear();
                            Converter.str( "" );
                            Converter << LoopIndex;
                            Attribute.SetAttributeName( "value" );
                            Attribute.SetAttributeValue( Converter.str() );
                            fTokenizer->ProcessToken( &Attribute );

                            EndElement.SetElementName( "define" );
                            fTokenizer->ProcessToken( &EndElement );

                            for( TokenIt It = Tokens.begin(); It != Tokens.end(); It++ )
                            {
                                Dispatch( *It );
                            }

                            BeginElement.SetElementName( "undefine" );
                            fTokenizer->ProcessToken( &BeginElement );

                            Attribute.SetAttributeName( "name" );
                            Attribute.SetAttributeValue( Variable );
                            fTokenizer->ProcessToken( &Attribute );

                            EndElement.SetElementName( "undefine" );
                            fTokenizer->ProcessToken( &EndElement );
                        }
                    }
                    else
                    {
                        iomsg + eWarning;
                        iomsg < "KSLoopProcessor::ProcessToken";
                        iomsg << "ignoring loop with zero step size" << ret;
                        iomsg << "in path <" << fTokenizer->GetFilePath() << "> in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;
                    }

                    //delete the old tokens (made with new during collection)
                    for( TokenIt It = Tokens.begin(); It != Tokens.end(); It++ )
                    {
                        delete *It;
                    }

                    return;
                }
            }

            fTokens.push_back( new KSTokenEndElement( *aToken ) );

            return;
        }

        iomsg + eWarning;
        iomsg < "KSLoopProcessor::ProcessToken";
        iomsg << "got unknown element <" << aToken->GetElementName() << ">" << ret;
        iomsg << "in path <" << fTokenizer->GetFilePath() << "> in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;

        for( TokenIt It = fTokens.begin(); It != fTokens.end(); It++ )
        {
            delete *It;
        }
        Reset();

        return;

        return;
    }
    void KSLoopProcessor::ProcessToken( KSTokenAttribute* aToken )
    {
        if( fState == eInactive )
        {
            KSProcessor::ProcessToken( aToken );
            return;
        }

        if( fState == eActive )
        {
            if( aToken->GetAttributeName() == string( "variable" ) )
            {
                fVariable = aToken->GetAttributeValue();

                return;
            }

            if( aToken->GetAttributeName() == string( "start" ) )
            {
                fStartValue = aToken->GetAttributeValue< Int_t >();

                return;
            }

            if( aToken->GetAttributeName() == string( "end" ) )
            {
                fEndValue = aToken->GetAttributeValue< Int_t >();

                return;
            }

            if( aToken->GetAttributeName() == string( "step" ) )
            {
                fStepValue = aToken->GetAttributeValue< Int_t >();

                return;
            }

            iomsg + eWarning;
            iomsg < "KSLoopProcessor::ProcessToken";
            iomsg << "ignoring unknown attribute" << ret;
            iomsg << "in path <" << fTokenizer->GetFilePath() << "in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;

            return;
        }

        if( fState == eCollecting )
        {

            fTokens.push_back( new KSTokenAttribute( *aToken ) );

            return;
        }

        return;
    }
    void KSLoopProcessor::ProcessToken( KSTokenData* aToken )
    {
        if( fState == eInactive )
        {
            KSProcessor::ProcessToken( aToken );
            return;
        }

        //trigger
        if( fState == eActive )
        {
            //hijack the tokenizer
            fTokenizer->PushContext( this );

            //collect trigger
            fState = eCollecting;
            ProcessToken( aToken );
            return;
        }

        if( fState == eCollecting )
        {
            fTokens.push_back( new KSTokenData( *aToken ) );
            return;
        }

    }

    void KSLoopProcessor::Dispatch( KSToken* aToken )
    {
        KSTokenBeginElement* BeginElementToken = NULL;
        BeginElementToken = dynamic_cast< KSTokenBeginElement* >( aToken );
        {
            if( BeginElementToken != NULL )
            {
                KSTokenBeginElement CopyBeginElementToken( *BeginElementToken );
                fTokenizer->ProcessToken( &CopyBeginElementToken );
                return;
            }
        }

        KSTokenEndElement* EndElementToken = NULL;
        EndElementToken = dynamic_cast< KSTokenEndElement* >( aToken );
        {
            if( EndElementToken != NULL )
            {
                KSTokenEndElement CopyEndElementToken( *EndElementToken );
                fTokenizer->ProcessToken( &CopyEndElementToken );
                return;
            }
        }

        KSTokenAttribute* AttributeToken = NULL;
        AttributeToken = dynamic_cast< KSTokenAttribute* >( aToken );
        {
            if( AttributeToken != NULL )
            {
                KSTokenAttribute CopyAttributeToken( *AttributeToken );
                fTokenizer->ProcessToken( &CopyAttributeToken );
                return;
            }
        }

        KSTokenData* DataToken = NULL;
        DataToken = dynamic_cast< KSTokenData* >( aToken );
        {
            if( DataToken != NULL )
            {
                KSTokenData CopyDataToken( *DataToken );
                fTokenizer->ProcessToken( &CopyDataToken );
                return;
            }
        }

        iomsg + eWarning;
        iomsg < "KSLoopProcessor::Dispatch";
        iomsg << "failed to dispatch token of type <" << aToken->GetTypeName() << ">" << eom;

        return;
    }

    void KSLoopProcessor::Reset()
    {
        fState = eInactive;
        fCount = 0;
        fVariable.clear();
        fStartValue = 0;
        fEndValue = 0;
        fStepValue = 0;
        fTokens.clear();
        return;
    }

}
