#include "KSXMLTokenizer.h"
#include "KSXMLReceiver.h"

#include <iostream>
using std::cout;
using std::endl;

namespace Kassiopeia
{

    class TestReceiver :
        public KSReceiver,
        public KSXMLReceiver
    {
        public:
            TestReceiver()
            {
            }
            virtual ~TestReceiver()
            {
            }

            virtual void ReceiveToken( const KSErrorToken* token )
            {
                cout << "got an error token! [error =" << token->GetMessage() << "]" << endl;
                return;
            }
            virtual void ReceiveToken( const KSTokenBeginParsing* token )
            {
                cout << "got an a begin parsing token." << endl;
                return;
            }
            virtual void ReceiveToken( const KSEndParsingToken* token )
            {
                cout << "got an end parsing token." << endl;
                return;
            }
            virtual void ReceiveToken( const KSTokenBeginFile* token )
            {
                cout << "got a begin file token." << endl;
                return;
            }
            virtual void ReceiveToken( const KSTokenEndFile* token )
            {
                cout << "got an end file token" << endl;
                return;
            }

            virtual void ReceiveToken( const KSTokenBeginElement* token )
            {
                cout << "got a start element token [element name = " << token->GetElementName() << "]" << endl;
                return;
            }
            virtual void ReceiveToken( const KSAttributeToken* token )
            {
                cout << "got an attribute token [attribute name = " << token->GetAttributeName() << ", attribute value = " << token->GetAttributeValue() << "]" << endl;
                return;
            }
            virtual void ReceiveToken( const KSTokenEndElement* token )
            {
                cout << "got an end element token [element name = " << token->GetElementName() << "]" << endl;
                return;
            }
            virtual void ReceiveToken( const KSDataToken* token )
            {
                cout << "got an area of data:" << endl;
                cout << "  " << token->GetDataValue() << endl;
                return;
            }
            virtual void ReceiveToken( const KSTokenError* token )
            {
                cout << "got an xml error token! [error = " << token->GetMessage() << "]" << endl;
                return;
            }
    };

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

    KSTokenizer Tokenizer;
    TestReceiver Receiver;

    Tokenizer.SetReceiver( &Receiver );
    Tokenizer.Read( FileName );

    return 0;

}
