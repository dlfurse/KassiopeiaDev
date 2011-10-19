#ifndef KSELEMENT_H_
#define KSELEMENT_H_

#include <string>
using std::string;

namespace Kassiopeia
{

    class KSBuilder;

    template< class XParentType, class XChildType >
    class KSElement
    {
        public:
            KSElement( const string& aKey );
            ~KSElement();

            static KSBuilder* Create();
    };

    template< class XParentType, class XChildType >
    KSElement< XParentType, XChildType >::KSElement( const string& aKey )
    {
        XParentType::SetElement( aKey, &Create );
    }
    template< class XParentType, class XChildType >
    KSElement< XParentType, XChildType >::~KSElement()
    {
    }
    template< class XParentType, class XChildType >
    KSBuilder* KSElement< XParentType, XChildType >::Create()
    {
        return new XChildType();
    }

}

#endif
