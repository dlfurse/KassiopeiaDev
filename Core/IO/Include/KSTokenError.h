/*!
 * @file KSTokenError
 * @author Dan Furse
 *
 * @brief created on Apr 7, 2011, contains class definition for KSXMLErrorToken
 */

#ifndef KSTOKENERROR_H_
#define KSTOKENERROR_H_

#include "KSToken.h"

/*!
 * @class KSTokenError
 * @author Dan Furse
 *
 * @brief this class represents an XML parsing error
 *
 */
namespace Kassiopeia
{

    class KSTokenError :
        public KSToken
    {
        public:
            KSTokenError();
            virtual ~KSTokenError();

            void SetMessage( const string& message );
            const string& GetMessage() const;

            virtual const string& GetTypeName() const;

        private:
            string fMessage;
            static const string fTypeName;
    };

}

#endif
