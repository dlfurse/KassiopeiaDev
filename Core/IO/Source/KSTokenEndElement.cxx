#include "KSTokenEndElement.h"

namespace Kassiopeia
{

    KSTokenEndElement::KSTokenEndElement() :
        KSToken(),
        fName( "" )
    {
    }
    KSTokenEndElement::~KSTokenEndElement()
    {
    }

    void KSTokenEndElement::SetElementName( const string& name )
    {
        fName = name;
        return;
    }
    const string& KSTokenEndElement::GetElementName() const
    {
        return fName;
    }

    const string& KSTokenEndElement::GetTypeName() const
    {
        return fTypeName;
    }
    const string KSTokenEndElement::fTypeName = string( "EndElement" );

}
