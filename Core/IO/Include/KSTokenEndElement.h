#ifndef KSTOKENENDELEMENT_H_
#define KSTOKENENDELEMENT_H_
/*!
 * @file KSXMLEndElementToken.h
 * @author Dan Furse
 *
 * @brief created on Apr 1, 2011.  contains class declaration for KSXMLEndElementToken.
 *
 */

#include "KSToken.h"

/*!
 * @class Kassiopeia::KSXMLEndElementToken
 * @author Dan Furse
 *
 * @brief this class represents the end of an XML element.
 *
 */
namespace Kassiopeia
{

    class KSTokenEndElement :
        public KSToken
    {
        public:
            KSTokenEndElement();
            virtual ~KSTokenEndElement();

            void SetElementName( const string& name );
            const string& GetElementName() const;

            virtual const string& GetTypeName() const;

        private:
            string fName;
            static const string fTypeName;
    };

}

#endif
