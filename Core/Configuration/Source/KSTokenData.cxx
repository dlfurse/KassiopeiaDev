#include "KSTokenData.h"

namespace Kassiopeia
{

    KSTokenData::KSTokenData() :
        KSToken(),
        fName( "" ),
        fValue( "" )
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
