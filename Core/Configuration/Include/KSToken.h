#ifndef KSTOKEN_H_
#define KSTOKEN_H_

/*!
 * @file KSToken.h
 * @brief contains declaration of class KSToken
 * @details
 *
 *
 * <b>Revision History:</b>
 * @verbatim
 * Date          Name          Brief description
 * -----------------------------------------------
 * 09 Mar 2010   N. Oblath     First version
 * 01 Apr 2011   D. Furse      Added some other identifying functions to the interface
 * 04 Sep 2011   D. Furse      Simplification from removal of old data types
 * @endverbatim
 */

#include <string>
using std::string;

/*!
 * @class Kassiopeia::KSToken
 * @author N. Oblath
 *
 * @brief this class represents a parsed token of XML information from an input file.
 * @details
 * <b>Detailed Description:</b><br>
 *
 */
namespace Kassiopeia
{

    class KSToken
    {
        public:
            KSToken();
            virtual ~KSToken();

            virtual const string& GetTypeName() const = 0;
    };

}

#endif
