#include "KSTokenAttribute.h"

namespace Kassiopeia
{

    KSTokenAttribute::KSTokenAttribute() :
        KSToken(),
        fName( "" ),
        fValue( "" )
    {
    }
    KSTokenAttribute::~KSTokenAttribute()
    {
    }

    void KSTokenAttribute::SetAttributeName( const string& name )
    {
        fName = name;
    }
    const string& KSTokenAttribute::GetAttributeName() const
    {
        return fName;
    }

    void KSTokenAttribute::SetAttributeValue( const string& value )
    {
        fValue = value;
    }
    const string& KSTokenAttribute::GetAttributeValue() const
    {
        return fValue;
    }

    const string& KSTokenAttribute::GetTypeName() const
    {
        return fTypeName;
    }
    const string KSTokenAttribute::fTypeName = string( "Attribute" );

}
