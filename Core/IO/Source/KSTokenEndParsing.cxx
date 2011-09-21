#include "KSTokenEndParsing.h"

namespace Kassiopeia
{

    KSTokenEndParsing::KSTokenEndParsing() :
        KSToken()
    {
    }
    KSTokenEndParsing::KSTokenEndParsing( const KSTokenEndParsing& /*aCopy*/ ) :
        KSToken()
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
