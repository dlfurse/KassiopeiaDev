#ifndef KSBuilderFactoryBase_h
#define KSBuilderFactoryBase_h

/**
 * @file

 * @brief contains KSBuilderFactory

 * @details
 * <b>Revision History:</b>
 * \verbatim
 * Date       Name          Brief description
 * -----------------------------------------------
 * 13 Jul 2010  D.Furse      first version
 * \endverbatim
 *
 */



/*!
 * @class Kassiopeia::KSBuilderFactory
 @author D. Furse

 @brief base class for all builder Factories

 @details
 <b>Detailed Description:</b><br>


 */

#include <string>
using std::string;

namespace Kassiopeia
{

    class KSBuilder;

    class KSBuilderFactory
    {
        public:
            KSBuilderFactory();
            virtual ~KSBuilderFactory();

            virtual KSBuilder* Build() const = 0;

            virtual const string& GetTypeName() const = 0;
            virtual const string& GetSystemName() const = 0;
    };

} // end namespace Kassiopeia

#endif // end ifndef KSBuilderFactoryBase_h
