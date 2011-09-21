#ifndef KSTOKENSTARTELEMENT_H_
#define KSTOKENSTARTELEMENT_H_
/*!
 * @file KSStartElementToken.h
 * @author Dan Furse
 *
 * @brief created on Mar 31, 2011.  contains class declaration of KSTokenBeginElement.
 *
 */

#include "KSToken.h"

/*!
 * @class Kassiopeia::KSTokenBeginElement
 * @author Dan Furse
 *
 * @brief this class represents the beginning of an XML element.
 *
 */
namespace Kassiopeia
{

    class KSTokenBeginElement :
        public KSToken
    {
        public:
            KSTokenBeginElement();
            KSTokenBeginElement( const KSTokenBeginElement& aCopy );
            virtual ~KSTokenBeginElement();

            void SetElementName( const string& name );
            const string& GetElementName() const;

            virtual const string& GetTypeName() const;

        private:
            string fName;
            static const string fTypeName;
    };

}

#endif
