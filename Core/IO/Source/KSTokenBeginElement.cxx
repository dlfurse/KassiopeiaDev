#include "KSTokenBeginElement.h"

namespace Kassiopeia
{

    KSTokenBeginElement::KSTokenBeginElement() :
        KSToken(),
        fName( "" )
    {
    }
    KSTokenBeginElement::KSTokenBeginElement(const KSTokenBeginElement& aCopy) :
        KSToken(),
        fName( aCopy.fName )
    {
    }
    KSTokenBeginElement::~KSTokenBeginElement()
    {
    }

    void KSTokenBeginElement::SetElementName( const string& name )
    {
        fName = name;
        return;
    }
    const string& KSTokenBeginElement::GetElementName() const
    {
        return fName;
    }

    const string& KSTokenBeginElement::GetTypeName() const
    {
        return fTypeName;
    }
    const string KSTokenBeginElement::fTypeName = string( "BeginElement" );

}
