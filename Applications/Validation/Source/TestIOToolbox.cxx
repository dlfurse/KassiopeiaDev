#include "KSIOToolbox.h"
#include "KSTextFile.h"

using namespace Kassiopeia;

int main()
{
    KSTextFile* IOConfigFile = new KSTextFile();
    IOConfigFile->SetKey( "io" );
    IOConfigFile->AddToBases( "UserConfiguration.xml" );

    KSIOToolbox::GetInstance()->SetTerminalVerbosity( 10 );
    KSIOToolbox::GetInstance()->AddConfigTextFile( IOConfigFile );

    KSManager* IOToolboxMgr = KSIOToolbox::GetInstance();
    IOToolboxMgr->Setup();
    IOToolboxMgr->Prepare();
    IOToolboxMgr->Shutdown();
    delete IOToolboxMgr;

    return 0;
}
