#include "KSTextFile.h"
#include "KSTokenizer.h"
#include "KSProcessor.h"

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
            virtual const string& GetTypeName() const
            {
                return fTypeName;
            }

        private:
            static const string fTypeName;

        public:
            virtual void ProcessToken( const KSTokenBeginParsing* /*token*/ )
            {
                cout << "got an a begin parsing token." << endl;
                return;
            }
            virtual void ProcessToken( const KSTokenEndParsing* /*token*/ )
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

    const string KSTestProcessor::fTypeName = string("TestProcessor");

}

using namespace Kassiopeia;

int main( int argc, char** argv )
{
    string FileName;

    if( argc < 2 )
    {
        cout << "give me an xml file name" << endl;
        return -1;
    }
    else
    {
        FileName = string( argv[1] );
    }

    KSTextFile File;
    KSTokenizer Tokenizer;
    KSTestProcessor Processor;

    File.AddToPaths( "." );
    File.AddToBases( FileName );
    Tokenizer.DropProcessor( &Processor );
    Tokenizer.ProcessFile( &File );

    return 0;

}
