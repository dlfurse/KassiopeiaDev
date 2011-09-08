#include "KSTokenBeginParsing.h"

namespace Kassiopeia
{

    KSTokenBeginParsing::KSTokenBeginParsing()
    {
    }

    KSTokenBeginParsing::~KSTokenBeginParsing()
    {
    }

    const string& KSTokenBeginParsing::GetTypeName() const
    {
        return fTypeName;
    }

    const string KSTokenBeginParsing::fTypeName = string("StartParsing");

}
