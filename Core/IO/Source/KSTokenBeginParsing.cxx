#include "KSTokenBeginParsing.h"

namespace Kassiopeia
{

    KSTokenBeginParsing::KSTokenBeginParsing() :
        KSToken()
    {
    }
    KSTokenBeginParsing::KSTokenBeginParsing( const KSTokenBeginParsing& /*aCopy*/ ) :
        KSToken()
    {
    }
    KSTokenBeginParsing::~KSTokenBeginParsing()
    {
    }

    const string& KSTokenBeginParsing::GetTypeName() const
    {
        return fTypeName;
    }
    const string KSTokenBeginParsing::fTypeName = string( "BeginParsing" );

}
