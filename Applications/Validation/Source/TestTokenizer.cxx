#include "KSIOToolbox.h"
#include "KSTextFile.h"
#include "KSTokenizer.h"
#include "KSProcessor.h"
#include "KSVariableProcessor.h"
#include "KSLoopProcessor.h"
#include "KSIncludeProcessor.h"
#include "KSBuilderProcessor.h"
#include "KSToolboxModuleBuilder.h"
#include "KSElement.h"

#include <iostream>
using std::cout;
using std::endl;

namespace Kassiopeia
{
    class KSTestBuilder :
        public KSToolboxModuleBuilder< KSIOToolbox, KSTestBuilder >
    {
        public:
            KSTestBuilder()
            {
            }
            virtual ~KSTestBuilder()
            {
                cout << "test builder is dying!" << endl;
            }

        public:
            virtual Bool_t Start()
            {
                return kTRUE;
            }
            virtual Bool_t End()
            {
                return kTRUE;
            }


            virtual void ProcessToken( KSTokenBeginParsing* /*token*/)
            {
                cout << "got a begin parsing token." << endl;
                return;
            }
            virtual void ProcessToken( KSTokenEndParsing* /*token*/)
            {
                cout << "got an end parsing token." << endl;
                return;
            }
            virtual void ProcessToken( KSTokenBeginFile* token )
            {
                cout << "got a begin file token [file name = " << token->GetFilename() << "]" << endl;
                return;
            }
            virtual void ProcessToken( KSTokenEndFile* token )
            {
                cout << "got an end file token [file name = " << token->GetFilename() << "]" << endl;
                return;
            }
            virtual void ProcessToken( KSTokenBeginElement* token )
            {
                cout << "got a start element token [element name = " << token->GetElementName() << "]" << endl;
                return;
            }
            virtual void ProcessToken( KSTokenEndElement* token )
            {
                if( token->GetElementName() == string("test") )
                {
                    KSBuilder::ProcessToken( token );
                    return;
                }
                cout << "got an end element token [element name = " << token->GetElementName() << "]" << endl;
                return;
            }
            virtual void ProcessToken( KSTokenAttribute* token )
            {
                cout << "got an attribute token [attribute name = " << token->GetAttributeName() << ", attribute value = " << token->GetAttributeValue() << "]" << endl;
                return;
            }
            virtual void ProcessToken( KSTokenData* token )
            {
                cout << "got an area of data:" << endl;
                cout << "  " << token->GetDataValue() << endl;
                return;
            }
            virtual void ProcessToken( KSTokenError* token )
            {
                cout << "got an error token! [error = " << token->GetMessage() << "]" << endl;
                return;
            }
    };

    KSElement< KSBuilderProcessor, KSTestBuilder > sKSTestBuilderElement("test");
}

using namespace Kassiopeia;

int main( int argc, char** argv )
{
    string FileName;
    string IncludedFileName;

    cout << "i am alive!" << endl;

    if( argc < 2 )
    {
        cout << "i can display the processed contents of xml files." << endl;
        cout << "give me an xml file name please!" << endl;
        return -1;
    }
    else
    {
        FileName = string( argv[1] );
        //IncludedFileName = string( argv[2] );
    }

    KSIOToolbox::GetInstance()->SetTerminalVerbosity( 10 );
    KSIOToolbox::GetInstance()->SetLogVerbosity( 10 );

    cout << "trying to open the log file..." << endl;

    KSIOToolbox::GetInstance()->GetLogTextFile()->Open( KSTextFile::eWrite );

    cout << "...done trying to open the log file" << endl;

    KSTextFile File;
    File.SetKey( "InputFile" );
    File.AddToNames( FileName );
    KSIOToolbox::GetInstance()->AddConfigTextFile( &File );

    //KSTextFile IncludedFile;
    //IncludedFile.SetKey( "FirstInclude" );
    //IncludedFile.AddToNames( IncludedFileName );
    //KSIOToolbox::GetInstance()->AddConfigTextFile( &IncludedFile );

    KSTokenizer Tokenizer;
    KSVariableProcessor VariableProcessor;
    Tokenizer.DropProcessor( &VariableProcessor );
    KSLoopProcessor LoopProcessor;
    Tokenizer.DropProcessor( &LoopProcessor );
    KSIncludeProcessor IncludeProcessor;
    Tokenizer.DropProcessor( &IncludeProcessor );
    KSBuilderProcessor BuilderProcessor;
    Tokenizer.DropProcessor( &BuilderProcessor );

    cout << "parsing file..." << endl;

    Tokenizer.ProcessFile( &File );

    cout << "...done parsing file" << endl;

    return 0;
}
