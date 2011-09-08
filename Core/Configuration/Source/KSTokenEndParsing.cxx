#include "KSTokenEndParsing.h"

namespace Kassiopeia
{

    KSTokenEndParsing::KSTokenEndParsing()
    {
    }

    KSTokenEndParsing::~KSTokenEndParsing()
    {
    }

    const string& KSTokenEndParsing::GetTypeName() const
    {
        return fTypeName;
    }

    const string KSTokenEndParsing::fTypeName = string( "EndParsing" );

}
