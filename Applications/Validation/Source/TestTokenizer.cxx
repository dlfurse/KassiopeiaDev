#include "KSIOToolbox.h"
#include "KSTextFile.h"
#include "KSTokenizer.h"
#include "KSProcessor.h"
#include "KSIncludeProcessor.h"

#include <iostream>
using std::cout;
using std::endl;

namespace Kassiopeia
{
    class KSTestProcessor :
        public KSProcessor
    {
        public:
            KSTestProcessor()
            {
            }
            virtual ~KSTestProcessor()
            {
            }

        public:
            virtual void ProcessToken( const KSTokenBeginParsing* /*token*/)
            {
                cout << "got a begin parsing token." << endl;
                return;
            }
            virtual void ProcessToken( const KSTokenEndParsing* /*token*/)
            {
                cout << "got an end parsing token." << endl;
                return;
            }
            virtual void ProcessToken( const KSTokenBeginFile* token )
            {
                cout << "got a begin file token [file name = " << token->GetFilename() << "]" << endl;
                return;
            }
            virtual void ProcessToken( const KSTokenEndFile* token )
            {
                cout << "got an end file token [file name = " << token->GetFilename() << "]" << endl;
                return;
            }
            virtual void ProcessToken( const KSTokenBeginElement* token )
            {
                cout << "got a start element token [element name = " << token->GetElementName() << "]" << endl;
                return;
            }
            virtual void ProcessToken( const KSTokenEndElement* token )
            {
                cout << "got an end element token [element name = " << token->GetElementName() << "]" << endl;
                return;
            }
            virtual void ProcessToken( const KSTokenAttribute* token )
            {
                cout << "got an attribute token [attribute name = " << token->GetAttributeName() << ", attribute value = " << token->GetAttributeValue() << "]" << endl;
                return;
            }
            virtual void ProcessToken( const KSTokenData* token )
            {
                cout << "got an area of data:" << endl;
                cout << "  " << token->GetDataValue() << endl;
                return;
            }
            virtual void ProcessToken( const KSTokenError* token )
            {
                cout << "got an error token! [error = " << token->GetMessage() << "]" << endl;
                return;
            }
    };
}

using namespace Kassiopeia;

int main( int argc, char** argv )
{
    string FileName;
    string IncludedFileName;

    if( argc < 3 )
    {
        cout << "i can display the contents of xml files that include each other." << endl;
        cout << "give me an two xml file names please, one that uses the <include> tag to include the other!" << endl;
        return -1;
    }
    else
    {
        FileName = string( argv[1] );
        IncludedFileName = string( argv[2] );
    }

    KSIOToolbox::GetInstance()->SetTerminalVerbosity(10);

    KSTextFile File;
    File.SetKey( "InputFile" );
    File.AddToNames( FileName );
    KSIOToolbox::GetInstance()->AddConfigTextFile( &File );

    KSTextFile IncludedFile;
    IncludedFile.SetKey( "FirstInclude" );
    IncludedFile.AddToNames( IncludedFileName );
    KSIOToolbox::GetInstance()->AddConfigTextFile( &IncludedFile );

    KSTokenizer Tokenizer;
    KSIncludeProcessor IncludeProcessor;
    KSTestProcessor Processor;

    Tokenizer.DropProcessor( &IncludeProcessor );
    Tokenizer.DropProcessor( &Processor );
    Tokenizer.ProcessFile( &File );

    return 0;
}
