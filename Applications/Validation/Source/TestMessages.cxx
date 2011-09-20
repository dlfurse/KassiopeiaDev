#include "KSIOMessage.h"
#include "KSIOToolbox.h"

#include "KSTextFile.h"

using namespace Kassiopeia;

int main()
{

    iomsg + eWarning;
    iomsg < "TestMessage::main";
    iomsg << "now testing color output" << ret;
    iomsg << "here is another line of text" << eom;

    iomsg + eWarning;
    iomsg < "TestMessage::main";
    iomsg << "hello" << eom;

    iomsg + eError;
    iomsg < "TestMessage::main";
    iomsg << "i ran into some kind of trouble" << eom;

    iomsg + eNormal;
    iomsg < "TestMessage::main";
    iomsg << "this thing!" << eom;

    KSIOToolbox* tIOTB = KSIOToolbox::GetInstance();

    tIOTB->SetTerminalVerbosity( 10 );
    tIOTB->SetLogVerbosity( 10 );
    tIOTB->GetLogTextFile()->AddToPaths(".");
    tIOTB->GetLogTextFile()->Open( KSFile::eWrite );

    iomsg + 6;
    iomsg < "TestMessage::main";
    iomsg << "this is a bizarro message" << eom;

    tIOTB->GetLogTextFile()->Close();

    return 0;
}
