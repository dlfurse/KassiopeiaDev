/*!
 * @file KSErrorToken.h
 * @brief created on: Apr 6, 2011, contains class declaration of KSErrorToken
 */

#ifndef KSERRORTOKEN_H_
#define KSERRORTOKEN_H_

#include "KSToken.h"

/*!
 * @class Kassiopeia::KSErrorToken
 * @author Dan Furse
 *
 * @brief this class represents a parsing or syntax error found while (trying to) parse a document.
 *
 */
namespace Kassiopeia
{

    class KSErrorToken :
        public KSToken
    {
        public:
            KSErrorToken();
            virtual ~KSErrorToken();

            void SetMessage( const string& message );
            const string& GetMessage() const;

            virtual const string& GetTypeName() const;
            virtual const string& GetSystemName() const;

        private:
            string fMessage;
            static const string fSystemName;
            static const string fTypeName;
    };

}

#endif /* KSXMLERRORTOKEN_H_ */
