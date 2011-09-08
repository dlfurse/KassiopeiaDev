/*!
 * @file KSTokenData
 * @author Dan Furse
 *
 * @brief created on Mar 31, 2011.  contains class declaration for KSTokenData.
 * author: dlfurse
 */

#ifndef KSDATATOKEN_H_
#define KSDATATOKEN_H_

#include "KSToken.h"

#include <sstream>
using std::istringstream;

/*!
 * @class Kassiopeia::KSTokenData
 * @author Dan Furse
 *
 * @brief this class represents data in an XML document.
 *
 */
namespace Kassiopeia
{

    class KSTokenData :
        public KSToken
    {
        public:
            KSTokenData();
            virtual ~KSTokenData();

            void SetDataValue( const string& value );
            const string& GetDataValue() const;

            template< typename XDataType >
            const XDataType GetDataValue() const;

            virtual const string& GetTypeName() const;

        private:
            string fName;
            string fValue;
            static const string fTypeName;
    };

    template< typename XDataType >
    inline const XDataType KSTokenData::GetDataValue() const
    {
        istringstream Converter( fValue );
        XDataType Data;
        Converter >> Data;
        return Data;
    }

}

#endif /* DATATOKEN_H_ */
