#include "KSTokenData.h"

namespace Kassiopeia
{

    KSTokenData::KSTokenData() :
        KSToken(),
        fValue( "" )
    {
    }
    KSTokenData::KSTokenData( const KSTokenData& aCopy ) :
        KSToken(),
        fValue( aCopy.fValue )
    {
    }
    KSTokenData::~KSTokenData()
    {
    }

    void KSTokenData::SetDataValue( const string& value )
    {
        fValue = value;
    }
    const string& KSTokenData::GetDataValue() const
    {
        return fValue;
    }

    const string& KSTokenData::GetTypeName() const
    {
        return fTypeName;
    }
    const string KSTokenData::fTypeName = string( "Data" );

}
