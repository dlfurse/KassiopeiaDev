#include "KSIOMessage.h"
#include "KSIOToolbox.h"

#include "KSTextFile.h"

using namespace Kassiopeia;

int main()
{

    iomsg + eWarning;
    iomsg < "TestMessage::main" < end;
    iomsg << "now testing color output" << ret;
    iomsg << "here is another line of text" << end;

    iomsg + eWarning;
    iomsg < "TestMessage::main" < end;
    iomsg << "hello" << end;

    iomsg + eError;
    iomsg < "TestMessage::main" < end;
    iomsg << "i ran into some kind of trouble" << end;

    iomsg + eNormal;
    iomsg < "TestMessage::main" < end;
    iomsg << "this thing!" << end;

    KSIOToolbox* tIOTB = KSIOToolbox::GetInstance();

    tIOTB->SetTerminalVerbosity( 10 );
    tIOTB->SetLogVerbosity( 10 );
    tIOTB->GetLogTextFile()->AddToPaths(".");
    tIOTB->GetLogTextFile()->Open( KSFile::eWrite );

    iomsg + 6;
    iomsg < "TestMessage::main" < end;
    iomsg << "this is a bizarro message" << end;

    tIOTB->GetLogTextFile()->Close();

    return 0;
}
