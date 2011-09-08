#include "KSMessage.h"
#include <iostream>
using std::cout;
using std::endl;

using namespace Kassiopeia;

class General;
static KSMessageSystem< General > msg;

class Green;
template<> string KSMessageSystem< Green >::fPrefix = string("\33[32;1m\t");
template<> string KSMessageSystem< Green >::fSuffix = string("\33[0m\t");
static KSMessageSystem< Green > greenmsg;

int main()
{
    KSMessageHandler* tMessageHandler = KSMessageHandler::GetInstance();

    tMessageHandler->SetTerminalVerbosity( 2 );

    greenmsg = eWarning;
    greenmsg < "TestMessage::main";
    greenmsg << "now testing color output" << ret;
    greenmsg << "here is another line of text" << end;

    cout << "\33[0m";

    msg = eWarning;
    msg < "TestMessage::main";
    msg << "hello" << end;

    msg = eError;
    msg < "TestMessage::main";
    msg << "goodbye" << end;

    msg = eMessage;
    msg < "TestMessage::main";
    msg << "shouldn\'t get here, as last message was a fatal error!" << end;

    return 0;
}
