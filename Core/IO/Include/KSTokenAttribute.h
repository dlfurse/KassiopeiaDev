#ifndef KSTOKENATTRIBUTE_H_
#define KSTOKENATTRIBUTE_H_
/*!
 * @file KSTokenAttribute.h
 * @author Dan Furse
 *
 * @brief created on Mar 31, 2011.  contains class definition for KSTokenAttribute.
 *
 */

#include "KSToken.h"

#include <sstream>
using std::istringstream;

/*!
 * @class Kassiopeia::KSTokenAttribute
 * @author Dan Furse
 *
 * @brief this class represents an XML attribute.
 *
 */
namespace Kassiopeia
{
    class KSTokenAttribute :
        public KSToken
    {
        public:
            KSTokenAttribute();
            KSTokenAttribute( const KSTokenAttribute& aCopy );
            virtual ~KSTokenAttribute();

            void SetAttributeName( const string& name );
            const string& GetAttributeName() const;

            void SetAttributeValue( const string& value );
            const string& GetAttributeValue() const;

            template< typename XValueType >
            const XValueType GetAttributeValue() const;

            virtual const string& GetTypeName() const;

        private:
            string fName;
            string fValue;
            static const string fTypeName;
    };

    template< typename XValueType >
    inline const XValueType KSTokenAttribute::GetAttributeValue() const
    {
        istringstream Converter( fValue );
        XValueType Value;
        Converter >> Value;
        return Value;
    }

}

#endif /* ATTRIBUTETOKEN_H_ */
