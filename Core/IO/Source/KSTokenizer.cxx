#include "KSTokenizer.h"

#include "KSTextFile.h"

//#include <iostream>
//using std::endl;
//using std::cout;

namespace Kassiopeia
{

    KSTokenizer::KSTokenizer( void(KSTokenizer::*anInitialState)(), void(KSTokenizer::*aFinalState)() ) :
        KSProcessor(),

        fFile( NULL ),
        fPath( "" ),
        fName( "" ),
        fLine( 0 ),
        fColumn( 0 ),
        fChar( '\0' ),

        fState( anInitialState ),
        fInitialState( anInitialState ),
        fFinalState( aFinalState ),
        fElementNames(),

        fNameBuffer( "" ),
        fValueBuffer( "" ),
        fErrorBuffer( "" ),
        fBeginParsing( new KSTokenBeginParsing() ),
        fEndParsing( new KSTokenEndParsing() ),
        fBeginFile( new KSTokenBeginFile() ),
        fEndFile( new KSTokenEndFile() ),
        fBeginElement( new KSTokenBeginElement() ),
        fEndElement( new KSTokenEndElement() ),
        fAttribute( new KSTokenAttribute() ),
        fData( new KSTokenData() ),
        fError( new KSTokenError() )
    {
        fTokenizer = this;
    }

    KSTokenizer::~KSTokenizer()
    {
        delete fBeginParsing;
        delete fEndParsing;
        delete fBeginFile;
        delete fEndFile;
        delete fBeginElement;
        delete fEndElement;
        delete fAttribute;
        delete fData;
        delete fError;
    }

    const string& KSTokenizer::GetTypeName() const
    {
        return fTypeName;
    }
    const string KSTokenizer::fTypeName = string( "Tokenizer" );

    void KSTokenizer::ProcessFile( KSTextFile* aFile )
    {
        if( fState == fInitialState )
        {
            fFile = aFile;
            while( kTRUE )
            {
                if( fState == fFinalState )
                {
                    ((this)->*(fState))();
                    break;
                }
                ((this)->*(fState))();
            }
            return;
        }
        else
        {
            KSTokenizer* aNewTokenizer = new KSTokenizer( &KSTokenizer::ParseBeginFile, &KSTokenizer::ParseCompleteFile );
            fTokenizer = aNewTokenizer;

            aNewTokenizer->ProcessFile( aFile );

            delete aNewTokenizer;
            fTokenizer = this;

            return;
        }
    }

    void KSTokenizer::ParseBegin()
    {
        //cout << "in begin";
        //cout << ", current file key is <" << fFile->GetKey() << ">" << endl;
        //if at whitespace, then append char to value, then recurse
        ProcessToken( fBeginParsing );
        fState = &KSTokenizer::ParseBeginFile;
        return;
    }
    void KSTokenizer::ParseBeginFile()
    {
        //cout << "in begin file";
        //cout << ", current file key is <" << fFile->GetKey() << ">" << endl;
        //if at whitespace, then append char to value, then recurse
        if( fFile->Open( KSFile::eRead ) == kFALSE )
        {
            fErrorBuffer.clear();
            fErrorBuffer = string( "unable to open file with key <" ) + fFile->GetKey() + string( ">" );

            fState = &KSTokenizer::ParseError;
            return;
        }

        fPath = fFile->GetPath();
        fName = fFile->GetName();
        fLine = 1;
        fColumn = 1;
        fChar = fFile->File()->get();

        fBeginFile->SetFilename( fName );
        ProcessToken( fBeginFile );

        fState = &KSTokenizer::ParseBody;
        return;
    }
    void KSTokenizer::ParseBody()
    {
        //cout << "in body";
        //cout << ", current character is <" << fChar << ">" << endl;
        //if at whitespace, then append char to value, then recurse
        if( AtOneOf( fWhiteSpaceChars ) )
        {
            fValueBuffer.append( 1, fChar );

            ToNext();
            fState = &KSTokenizer::ParseBody;
            return;
        }

        //if at "</", then ParseEndElementPre
        //if at "<" followed by anything else, then ParseStartElementPre
        if( AtOneOf( fLeftAngle ) )
        {
            ToNext();

            if( AtOneOf( fSlash ) )
            {
                ToNext();
                fState = &KSTokenizer::ParseEndElementPre;
                return;
            }

            fState = &KSTokenizer::ParseStartElementPre;
            return;
        }

        //if at value, then append char to value, then ParseDataValue
        if( AtOneOf( fValueChars ) )
        {
            fValueBuffer.append( 1, fChar );

            ToNext();
            fState = &KSTokenizer::ParseDataValue;
            return;
        }

        //if at end of file, then ParseComplete
        if( AtEnd() )
        {
            fState = &KSTokenizer::ParseComplete;
            return;
        }

        fState = &KSTokenizer::ParseError;
        return;
    }
    void KSTokenizer::ParseStartElementPre()
    {
        //cout << "in startelementpre";
        //cout << ", current character is <" << fChar << ">" << endl;
        //if at whitespace, then recurse
        if( AtOneOf( fWhiteSpaceChars ) )
        {
            ToNext();
            fState = &KSTokenizer::ParseStartElementPre;
            return;
        }

        //if at name start, then assign initial char to name, then ParseElementName
        if( AtOneOf( fNameStartChars ) )
        {
            fNameBuffer.assign( 1, fChar );

            ToNext();
            fState = &KSTokenizer::ParseStartElementName;
            return;
        }

        fState = &KSTokenizer::ParseError;
        return;
    }
    void KSTokenizer::ParseStartElementName()
    {
        //cout << "in startelementname";
        //cout << ", current character is <" << fChar << ">" << endl;
        //if at name, append char to name, then recurse
        if( AtOneOf( fNameChars ) )
        {
            fNameBuffer.append( 1, fChar );

            ToNext();
            fState = &KSTokenizer::ParseStartElementName;
            return;
        }

        //if at "/>", then send start element, then send end element, then prepare value, then ParseBody
        //if at "/" followed by something else, then ParseError
        if( AtOneOf( fSlash ) )
        {
            ToNext();

            if( AtOneOf( fRightAngle ) )
            {
                //std::cout << "end element (3): " << fNameBuffer << std::endl;
                fBeginElement->SetElementName( fNameBuffer );
                ProcessToken( fBeginElement );

                fEndElement->SetElementName( fNameBuffer );
                ProcessToken( fEndElement );

                fValueBuffer.clear();

                ToNext();
                fState = &KSTokenizer::ParseBody;
                return;
            }

            fState = &KSTokenizer::ParseError;
            return;
        }

        //if at ">", the put name on stack, then send start element, then ParseBody
        if( AtOneOf( fRightAngle ) )
        {
            //std::cout << "start element (1): " << fNameBuffer << std::endl;
            fElementNames.push( fNameBuffer );

            fBeginElement->SetElementName( fNameBuffer );
            ProcessToken( fBeginElement );

            fValueBuffer.clear();

            ToNext();
            fState = &KSTokenizer::ParseBody;
            return;
        }

        //if at whitespace, then put name on stack, then send start element, then ParseStartElementPost
        if( AtOneOf( fWhiteSpaceChars ) )
        {
            //std::cout << "start element (2): " << fNameBuffer << std::endl;
            fElementNames.push( fNameBuffer );

            fBeginElement->SetElementName( fNameBuffer );
            ProcessToken( fBeginElement );

            fState = &KSTokenizer::ParseStartElementPost;
            return;
        }

        fState = &KSTokenizer::ParseError;
        return;
    }
    void KSTokenizer::ParseStartElementPost()
    {
        //cout << "in startelementpost";
        //cout << ", current character is <" << fChar << ">" << endl;

        //if at whitespace, then recurse
        if( AtOneOf( fWhiteSpaceChars ) )
        {
            ToNext();
            fState = &KSTokenizer::ParseStartElementPost;
            return;
        }

        //if at "/>", then assign name from stack, then pop stack, then send end element, then prepare value, then ParseBody
        //if at "/" followed by anything else, then ParseError
        if( AtOneOf( fSlash ) )
        {
            ToNext();

            if( AtOneOf( fRightAngle ) )
            {
                fNameBuffer.assign( fElementNames.top() );
                fElementNames.pop();
                //std::cout << "end element (4): " << fNameBuffer << std::endl;

                fEndElement->SetElementName( fNameBuffer );
                ProcessToken( fEndElement );

                fValueBuffer.clear();

                ToNext();
                fState = &KSTokenizer::ParseBody;
                return;
            }

            fState = &KSTokenizer::ParseError;
            return;
        }

        //if at ">", then prepare value, then ParseBody
        if( AtOneOf( fRightAngle ) )
        {
            fValueBuffer.clear();

            ToNext();
            fState = &KSTokenizer::ParseBody;
            return;
        }

        //if at name start, then assign initial char to name, then ParseAttributeName
        if( AtOneOf( fNameStartChars ) )
        {
            fNameBuffer.assign( 1, fChar );

            ToNext();
            fState = &KSTokenizer::ParseAttributeName;
            return;
        }

        fState = &KSTokenizer::ParseError;
        return;
    }
    void KSTokenizer::ParseAttributeName()
    {
        //cout << "in attributename";
        //cout << ", current character is <" << fChar << ">" << endl;
        //if at name, then append char to name buffer, then recurse
        if( AtOneOf( fNameChars ) )
        {
            fNameBuffer.append( 1, fChar );

            ToNext();
            fState = &KSTokenizer::ParseAttributeName;
            return;
        }

        //if at whitespace, then ParseAttributeAssignmentPre
        if( AtOneOf( fWhiteSpaceChars ) )
        {
            ToNext();
            fState = &KSTokenizer::ParseAttributeAssignmentPre;
            return;
        }

        //if at '=', then ParseAttributeAssignementPost
        if( AtOneOf( fEqual ) )
        {
            ToNext();
            fState = &KSTokenizer::ParseAttributeAssignmentPost;
            return;
        }

        fState = &KSTokenizer::ParseError;
        return;
    }
    void KSTokenizer::ParseAttributeAssignmentPre()
    {
        //cout << "in attributeassignmentpre";
        //cout << ", current character is <" << fChar << ">" << endl;
        //if at whitespace, then recurse
        if( AtOneOf( fWhiteSpaceChars ) )
        {
            ToNext();
            fState = &KSTokenizer::ParseAttributeAssignmentPre;
            return;
        }

        //if at '=', then ParseAttributeAssignementPost
        if( AtOneOf( fEqual ) )
        {
            ToNext();
            fState = &KSTokenizer::ParseAttributeAssignmentPost;
            return;
        }

        fState = &KSTokenizer::ParseError;
        return;
    }
    void KSTokenizer::ParseAttributeAssignmentPost()
    {
        //cout << "in attributeassignmentpost";
        //cout << ", current character is <" << fChar << ">" << endl;
        //if at whitespace, then recurse
        if( AtOneOf( fWhiteSpaceChars ) )
        {
            ToNext();
            fState = &KSTokenizer::ParseAttributeAssignmentPost;
            return;
        }

        //if at """, then prepare value, then ParseAttributeValue
        if( AtOneOf( fQuote ) )
        {
            fValueBuffer.clear();

            ToNext();
            fState = &KSTokenizer::ParseAttributeValue;
            return;
        }

        fState = &KSTokenizer::ParseError;
        return;
    }
    void KSTokenizer::ParseAttributeValue()
    {
        //cout << "in attributevalue";
        //cout << ", current character is <" << fChar << ">" << endl;
        //if at whitespace or value, then append char to value, then recurse
        if( AtOneOf( fWhiteSpaceChars ) || AtOneOf( fValueChars ) )
        {
            fValueBuffer.append( 1, fChar );

            ToNext();
            fState = &KSTokenizer::ParseAttributeValue;
            return;
        }

        //if at """, then send attribute token, then ParseStartElementPost
        if( AtOneOf( fQuote ) )
        {
            fAttribute->SetAttributeName( fNameBuffer );
            fAttribute->SetAttributeValue( fValueBuffer );
            ProcessToken( fAttribute );

            ToNext();
            fState = &KSTokenizer::ParseStartElementPost;
            return;
        }

        fState = &KSTokenizer::ParseError;
        return;
    }
    void KSTokenizer::ParseEndElementPre()
    {
        //cout << "in endelementpre";
        //cout << ", current character is <" << fChar << ">" << endl;
        //if at whitespace, then recurse
        if( AtOneOf( fWhiteSpaceChars ) )
        {
            ToNext();
            fState = &KSTokenizer::ParseEndElementPre;
            return;
        }

        //if at name start, then assign initial char to name, then ParseEndElementName
        if( AtOneOf( fNameStartChars ) )
        {
            fNameBuffer.assign( 1, fChar );

            ToNext();
            fState = &KSTokenizer::ParseEndElementName;
            return;
        }

        fState = &KSTokenizer::ParseError;
        return;
    }
    void KSTokenizer::ParseEndElementName()
    {
        //cout << "in endelementname";
        //cout << ", current character is <" << fChar << ">" << endl;
        //if at name, then append char to name, then recurse
        if( AtOneOf( fNameChars ) )
        {
            fNameBuffer.append( 1, fChar );

            ToNext();
            fState = &KSTokenizer::ParseEndElementName;
            return;
        }

        //if at ">", then check and send end element, then prepare value, then ParseBody
        if( AtOneOf( fRightAngle ) )
        {
            //std::cout << "end element (1): " << fNameBuffer << std::endl;
            if( fElementNames.top() != fNameBuffer )
            {
                fErrorBuffer.clear();
                fErrorBuffer = string( "expected closing element name <" ) + fElementNames.top() + string( ">, but got <" ) + fNameBuffer + string( "> instead" );

                fState = &KSTokenizer::ParseError;
                return;
            }
            fElementNames.pop();

            fEndElement->SetElementName( fNameBuffer );
            ProcessToken( fEndElement );

            fValueBuffer.clear();

            ToNext();
            fState = &KSTokenizer::ParseBody;
            return;
        }

        //if at whitespace, then check and send element, then ParseEndElementPost
        if( AtOneOf( fWhiteSpaceChars ) )
        {
            //std::cout << "end element (2): " << fNameBuffer << std::endl;
            if( fElementNames.top() != fNameBuffer )
            {
                fErrorBuffer.clear();
                fErrorBuffer = string( "expected closing element name <" ) + fElementNames.top() + string( ">, but got <" ) + fNameBuffer + string( "> instead" );

                fState = &KSTokenizer::ParseError;
                return;
            }
            fElementNames.pop();

            fEndElement->SetElementName( fNameBuffer );
            ProcessToken( fEndElement );

            ToNext();
            fState = &KSTokenizer::ParseEndElementPost;
            return;
        }

        fState = &KSTokenizer::ParseError;
        return;
    }
    void KSTokenizer::ParseEndElementPost()
    {
        //cout << "in endelementpost";
        //cout << ", current character is <" << fChar << ">" << endl;
        //if at whitespace, recurse
        if( AtOneOf( fWhiteSpaceChars ) )
        {
            ToNext();
            fState = &KSTokenizer::ParseEndElementPost;
            return;
        }

        //if at ">", then prepare value, then ParseBody
        if( AtOneOf( fRightAngle ) )
        {
            fValueBuffer.clear();

            ToNext();
            fState = &KSTokenizer::ParseBody;
            return;
        }

        fState = &KSTokenizer::ParseError;
        return;
    }
    void KSTokenizer::ParseDataValue()
    {
        //cout << "in datavalue";
        //cout << ", current character is <" << fChar << ">" << endl;
        //if at whitespace or value, then append character to value, recurse
        if( AtOneOf( fWhiteSpaceChars ) || AtOneOf( fValueChars ) )
        {
            fValueBuffer.append( 1, fChar );

            ToNext();
            fState = &KSTokenizer::ParseDataValue;
            return;
        }

        //if at "<", then send data, then ParseStartElementPre
        if( AtOneOf( fLeftAngle ) )
        {
            fData->SetDataValue( fValueBuffer );
            ProcessToken( fData );

            ToNext();

            if( AtOneOf( fSlash ) )
            {
                ToNext();
                fState = &KSTokenizer::ParseEndElementPre;
                return;
            }

            fState = &KSTokenizer::ParseStartElementPre;
            return;
        }

        fState = &KSTokenizer::ParseError;
        return;
    }
    void KSTokenizer::ParseCompleteFile()
    {
        //cout << "in complete file";
        //cout << ", current file key is <" << fFile->GetKey() << ">" << endl;
        //if at whitespace, then append char to value, then recurse
        if( fFile->Close() == kFALSE )
        {
            fErrorBuffer.clear();
            fErrorBuffer = string( "unable to close file with key <" ) + fFile->GetKey() + string( ">" );

            fState = &KSTokenizer::ParseError;
            return;
        }

        fBeginFile->SetFilename( fName );
        ProcessToken( fBeginFile );

        fPath = string( "" );
        fName = string( "" );
        fLine = 0;
        fColumn = 0;
        fChar = '\0';

        fState = &KSTokenizer::ParseComplete;
        return;
    }
    void KSTokenizer::ParseComplete()
    {
        //cout << "in complete";
        //cout << ", current file key is <" << fFile->GetKey() << ">" << endl;
        ProcessToken( fEndParsing );
        fState = &KSTokenizer::ParseComplete;
        return;
    }
    void KSTokenizer::ParseComment()
    {
        //TODO: finish this
        return;
    }
    void KSTokenizer::ParseError()
    {
        //if the previous state didn't fill in any details, form a generic error message, then send error, then ParseComplete
        if( fErrorBuffer.empty() )
        {
            if( AtEnd() )
            {
                fErrorBuffer.assign( "unexpected end of file" );
            }
            else
            {
                fErrorBuffer.assign( "unexpected character: <" );
                fErrorBuffer.append( 1, fChar );
                fErrorBuffer.append( ">" );
            }
        }

        fError->SetMessage( fErrorBuffer );
        ProcessToken( fError );

        fState = fFinalState;

        return;
    }

    void KSTokenizer::ToNext()
    {
        //if iterator is already the end, bail out
        if( AtEnd() )
        {
            return;
        }

        //calculate adjustments to the line and column numbers
        Int_t ColumnChange;
        Int_t LineChange;
        if( AtOneOf( fNewLine ) )
        {
            //if the current character is a newline, a successful increment will make the column number 1 and the line number jump by one.
            ColumnChange = 1 - fColumn;
            LineChange = 1;
        }
        else
        {
            //if the current character is not a newline, a successful increment will make the column number jump by one and the line number will stay the same.
            ColumnChange = 1;
            LineChange = 0;
        }

        //increment the iterator
        //cout << "popping the iterator" << endl;
        fChar = fFile->File()->get();

        //make sure that incrementing didn't put the iterator at the end
        if( AtEnd() )
        {
            return;
        }

        //apply the calculated column and line adjustments
        fColumn = fColumn + ColumnChange;
        fLine = fLine + LineChange;

        //GET OUT
        return;
    }
    Bool_t KSTokenizer::AtEnd()
    {
        //if iterator is at EOF, return kTRUE
        if( fFile->File()->eof() == kTRUE )
        {
            return kTRUE;
        }
        return kFALSE;
    }
    Bool_t KSTokenizer::AtOneOf( const string& chars )
    {
        //if iterator is at EOF, return kFALSE
        if( AtEnd() )
        {
            return kFALSE;
        }

        //if iterator is at a character contained in chars, return kTRUE
        if( chars.find( fChar ) != string::npos )
        {
            return kTRUE;
        }

        //otherwise return kFALSE
        return kFALSE;
    }

    const string KSTokenizer::fSpace = string( " " );
    const string KSTokenizer::fTab = string( "\t" );
    const string KSTokenizer::fNewLine = string( "\n" );
    const string KSTokenizer::fCarriageReturn = string( "\r" );

    const string KSTokenizer::fLowerCase = string( "abcdefghijklmnopqrstuvwxyz" );
    const string KSTokenizer::fUpperCase = string( "ABCDEFGHIJKLMNOPQRSTUVWXYZ" );
    const string KSTokenizer::fNumerals = string( "0123456789" );

    const string KSTokenizer::fLeftAngle = string( "<" );
    const string KSTokenizer::fRightAngle = string( ">" );
    const string KSTokenizer::fSlash = string( "/" );
    const string KSTokenizer::fEqual = string( "=" );
    const string KSTokenizer::fQuote = string( "\"" );

    const string KSTokenizer::fLeftBraces = string( "([" );
    const string KSTokenizer::fOperators = string( "+-*/" );
    const string KSTokenizer::fRightBraces = string( ")]" );

    const string KSTokenizer::fParameterLeftBrace = string( "$" );
    const string KSTokenizer::fParameterRightBrace = string( "$" );

    const string KSTokenizer::fWhiteSpaceChars = KSTokenizer::fSpace + KSTokenizer::fTab + KSTokenizer::fNewLine + KSTokenizer::fCarriageReturn;
    const string KSTokenizer::fNameStartChars = KSTokenizer::fLowerCase + KSTokenizer::fUpperCase + string( ":_" );
    const string KSTokenizer::fNameChars = KSTokenizer::fLowerCase + KSTokenizer::fUpperCase + KSTokenizer::fNumerals + string( ":_-." );
    const string KSTokenizer::fValueChars = KSTokenizer::fLowerCase + KSTokenizer::fUpperCase + KSTokenizer::fNumerals + KSTokenizer::fLeftBraces + KSTokenizer::fOperators + KSTokenizer::fRightBraces + KSTokenizer::fParameterLeftBrace + KSTokenizer::fParameterRightBrace + string( ":_.," );

}
