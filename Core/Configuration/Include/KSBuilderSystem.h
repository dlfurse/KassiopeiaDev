/*!
 * @file KSBuilderSystem.h
 * @brief contains class declaration of KSBuilderSystem
 *
 * @details
 * <b>Revision History:</b>
 * @verbatim
 * Date       Name          Brief description
 * -----------------------------------------------
 * 13 Jul 2010  D.Furse      first version
 * @endverbatim
 */

#ifndef KSBUILDERSYSTEMPROTOTYPE_H_
#define KSBUILDERSYSTEMPROTOTYPE_H_

#include "KSBuilder.h"

/*!
 * @class Kassiopeia::KSBuilderSystem
 * @author Dan Furse
 *
 * @brief templated base class for system builders. These manage a whole family of builders, typically a module.
 *
 * @details
 * <b>Detailed Description:</b><br>
 *
 */
namespace Kassiopeia
{

    template< class XManagerType >
    class KSInitializerPrototype;

    template< class XManagerType >
    class KSBuilderSystem :
        public KSBuilder
    {
        public:
            friend class KSInitializerPrototype< XManagerType >;

        public:
            KSBuilderSystem();
            virtual ~KSBuilderSystem();

        protected:
            static XManagerType* fManager;
    };

    template< class XManagerType >
    KSBuilderSystem< XManagerType >::KSBuilderSystem() :
        KSBuilder()
    {
    }

    template< class XManagerType >
    KSBuilderSystem< XManagerType >::~KSBuilderSystem()
    {
    }

    template< class XManagerType >
    XManagerType* KSBuilderSystem< XManagerType >::fManager = 0;


} // end namespace Kassiopeia

#endif // end ifndef KSBuilderSystem
