#include "KSVariableProcessor.h"

#include "KSTokenizer.h"

#include "KSIOToolbox.h"
#include "KSIOMessage.h"

namespace Kassiopeia
{

    KSVariableProcessor::KSVariableProcessor() :
        KSProcessor(),
        fGlobalMap( new VariableMap() ),
        fFileMap( new VariableMap() ),
        fFileMapStack()
    {
        Reset();
    }

    KSVariableProcessor::~KSVariableProcessor()
    {
        delete fGlobalMap;
        delete fFileMap;
    }

    void KSVariableProcessor::ProcessToken( KSTokenBeginFile* aToken )
    {
        if( fState == eInactive )
        {
            fFileMapStack.push( fFileMap );
            fFileMap = new VariableMap();

            KSProcessor::ProcessToken( aToken );
            return;
        }

        iomsg + eWarning;
        iomsg < "KSVariableProcessor::ProcessToken";
        iomsg << "got unknown start of file <" << aToken->GetFilename() << ">" << ret;
        iomsg << "in path <" << fTokenizer->GetFilePath() << "> in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;

        Reset();
        return;
    }
    void KSVariableProcessor::ProcessToken( KSTokenEndFile* aToken )
    {
        if( fState == eInactive )
        {
            delete fFileMap;
            fFileMap = fFileMapStack.top();
            fFileMapStack.pop();

            KSProcessor::ProcessToken( aToken );
            return;
        }

        iomsg + eWarning;
        iomsg < "KSVariableProcessor::ProcessToken";
        iomsg << "got unknown end of file <" << aToken->GetFilename() << ">" << ret;
        iomsg << "in path <" << fTokenizer->GetFilePath() << "> in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;

        Reset();

        return;
    }
    void KSVariableProcessor::ProcessToken( KSTokenBeginElement* aToken )
    {
        if( fState == eInactive )
        {
            if( aToken->GetElementName() == string( "define" ) )
            {
                fState = eActiveDefine;
                return;
            }

            if( aToken->GetElementName() == string( "undefine" ) )
            {
                fState = eActiveUndefine;
                return;
            }

            KSProcessor::ProcessToken( aToken );
            return;
        }

        iomsg + eWarning;
        iomsg < "KSVariableProcessor::ProcessToken";
        iomsg << "got unknown element <" << aToken->GetElementName() << ">" << ret;
        iomsg << "in path <" << fTokenizer->GetFilePath() << "> in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;

        Reset();
        return;
    }
    void KSVariableProcessor::ProcessToken( KSTokenEndElement* aToken )
    {
        if( fState == eActiveDefine )
        {
            VariableIt GlobalIt = fGlobalMap->find( fName );
            if( GlobalIt == fGlobalMap->end() )
            {
                VariableIt FileIt = fFileMap->find( fName );
                if( FileIt == fFileMap->end() )
                {
                    fFileMap->insert( VariableEntry( fName, fValue ) );
                }
                else
                {
                    iomsg + eWarning;
                    iomsg < "KSVariableProcessor::ProcessToken";
                    iomsg << "ignoring redefinition of local variable  <" << fName << "> with new value <" << fValue << ">" << ret;
                    iomsg << "in path <" << fTokenizer->GetFilePath() << "> in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;
                }
            }
            else
            {
                iomsg + eWarning;
                iomsg < "KSVariableProcessor::ProcessToken";
                iomsg << "ignoring redefinition of global variable  <" << fName << "> with new value <" << fValue << ">" << ret;
                iomsg << "in path <" << fTokenizer->GetFilePath() << "> in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;
            }

            Reset();
            return;
        }

        if( fState == eActiveUndefine )
        {
            VariableIt FileIt = fFileMap->find( fName );
            if( FileIt != fFileMap->end() )
            {
                fFileMap->erase( FileIt );
            }
            else
            {
                VariableIt GlobalIt = fGlobalMap->find( fName );
                if( GlobalIt != fGlobalMap->end() )
                {
                    iomsg + eWarning;
                    iomsg < "KSVariableProcessor::ProcessToken";
                    iomsg << "cannot undefine global variable with name <" << fName << ">" << ret;
                    iomsg << "in path <" << fTokenizer->GetFilePath() << "> in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;
                }
                else
                {
                    iomsg + eWarning;
                    iomsg < "KSVariableProcessor::ProcessToken";
                    iomsg << "variable with name <" << fName << "> is not defined in this file" << ret;
                    iomsg << "in path <" << fTokenizer->GetFilePath() << "> in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;
                }
            }

            Reset();
            return;
        }

        KSProcessor::ProcessToken( aToken );
        return;
    }
    void KSVariableProcessor::ProcessToken( KSTokenAttribute* aToken )
    {

        if( fState == eActiveDefine )
        {
            if( aToken->GetAttributeName() == "name" )
            {
                if( fName.size() == 0 )
                {
                    fName = aToken->GetAttributeValue();
                    return;
                }
                else
                {
                    iomsg + eWarning;
                    iomsg < "KSVariableProcessor::ProcessToken";
                    iomsg << "name attribute must appear only once in definition" << ret;
                    iomsg << "in path <" << fTokenizer->GetFilePath() << "> in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;
                    return;
                }
            }

            if( aToken->GetAttributeName() == "value" )
            {
                if( fValue.size() == 0 )
                {
                    fValue = aToken->GetAttributeValue();
                    return;
                }
                else
                {
                    iomsg + eWarning;
                    iomsg < "KSVariableProcessor::ProcessToken";
                    iomsg << "value attribute must appear only once in definition" << ret;
                    iomsg << "in path <" << fTokenizer->GetFilePath() << "> in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;
                    return;
                }
            }

            iomsg + eWarning;
            iomsg < "KSVariableProcessor::ProcessToken";
            iomsg << "ignoring unknown attribute <" << aToken->GetAttributeName() << ">" << ret;
            iomsg << "in path <" << fTokenizer->GetFilePath() << "> in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;

            return;
        }

        if( fState == eActiveUndefine )
        {
            if( aToken->GetAttributeName() == "name" )
            {
                if( fName.size() == 0 )
                {
                    fName = aToken->GetAttributeValue();
                    return;
                }
                else
                {
                    iomsg + eWarning;
                    iomsg < "KSVariableProcessor::ProcessToken";
                    iomsg << "name attribute must appear only once in undefinition" << ret;
                    iomsg << "in path <" << fTokenizer->GetFilePath() << "> in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;
                    return;
                }
            }

            iomsg + eWarning;
            iomsg < "KSVariableProcessor::ProcessToken";
            iomsg << "ignoring unknown attribute <" << aToken->GetAttributeName() << ">" << ret;
            iomsg << "in path <" << fTokenizer->GetFilePath() << "> in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;

            return;
        }

        string Value;
        Value = aToken->GetAttributeValue();
        while( Evaluate( Value ) == true );
        aToken->SetAttributeValue( Value );

        KSProcessor::ProcessToken( aToken );
        return;
    }
    void KSVariableProcessor::ProcessToken( KSTokenData* aToken )
    {
        if( (fState == eActiveDefine) || (fState == eActiveUndefine) )
        {
            iomsg + eWarning;
            iomsg < "KSVariableProcessor::ProcessToken";
            iomsg << "ignoring unknown data <" << aToken->GetDataValue() << ">" << ret;
            iomsg << "in path <" << fTokenizer->GetFilePath() << "> in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;

            Reset();
            return;
        }

        string Value;
        Value = aToken->GetDataValue();
        while( Evaluate( Value ) == true );
        aToken->SetDataValue( Value );

        KSProcessor::ProcessToken( aToken );
        return;
    }

    void KSVariableProcessor::Reset()
    {
        fName.clear();
        fValue.clear();

        fState = eInactive;

        return;
    }
    bool KSVariableProcessor::Evaluate( string& aString )
    {
        bool BracketFound = false;

        string Buffer;
        stack< string > BufferStack;
        BufferStack.push( "" );

        for( size_t Index = 0; Index < aString.size(); Index++ )
        {
            if( aString[Index] == fStartBracket )
            {
                BracketFound = true;
                BufferStack.top() += Buffer;
                BufferStack.push( "" );
                Buffer.clear();
                continue;
            }

            if( aString[Index] == fEndBracket )
            {
                BufferStack.top() += Buffer;
                Buffer = BufferStack.top();
                BufferStack.pop();
                if( BufferStack.size() == 0 )
                {
                    iomsg + eWarning;
                    iomsg < "KSVariableProcessor::ProcessToken";
                    iomsg << "bracket matching problem at position <" << Index << "> in string <" << aString << ">" << ret;
                    iomsg << "in path <" << fTokenizer->GetFilePath() << "> in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;
                    return false;
                }

                VariableIt GlobalVariable = fGlobalMap->find( Buffer );
                if( GlobalVariable != fGlobalMap->end() )
                {
                    Buffer = GlobalVariable->second;
                }
                else
                {
                    VariableIt FileVariable = fFileMap->find( Buffer );
                    if( FileVariable != fFileMap->end() )
                    {
                        Buffer = FileVariable->second;
                    }
                    else
                    {
                        iomsg + eWarning;
                        iomsg < "KSVariableProcessor::ProcessToken";
                        iomsg << "variable <" << Buffer << ">" << " is not defined" << ret;
                        iomsg << "in path <" << fTokenizer->GetFilePath() << "> in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;
                    }
                }

                BufferStack.top() += Buffer;
                Buffer.clear();
                continue;
            }

            Buffer.append( 1, aString[Index] );
        }

        if( Buffer.size() != 0 )
        {
            BufferStack.top() += Buffer;
        }
        Buffer = BufferStack.top();
        BufferStack.pop();
        if( BufferStack.size() != 0 )
        {
            iomsg + eWarning;
            iomsg < "KSVariableProcessor::ProcessToken";
            iomsg << "bracket matching problem at final position in string <" << aString << ">" << ret;
            iomsg << "in path <" << fTokenizer->GetFilePath() << "> in file <" << fTokenizer->GetFileName() << "> at line <" << fTokenizer->GetFileLine() << ">, column <" << fTokenizer->GetFileColumn() << ">" << eom;
            return false;
        }

        aString = Buffer;
        return BracketFound;
    }

}
