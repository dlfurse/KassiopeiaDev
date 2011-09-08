/*!
 * @file
 * @brief contains KSInitializerPrototype
 *
 * @details
 * <b>Revision History:</b>
 * @verbatim
 * Date         Name          Brief description
 * -----------------------------------------------
 * 13 Jul 2010  D. Furse      first version
 * @endverbatim
 */

#ifndef KSINITIALIZERPROTOTYPE_H_
#define KSINITIALIZERPROTOTYPE_H_

#include "KSInitializer.h"

#include "KSBuilderSystem.h"

/*!
 * @class Kassiopeia::KSInitializerPrototype
 * @author D. Furse
 *
 * @brief this class is a prototype of an initializer templated with the type of manager it serves.
 *
 * @details
 * <b>Detailed Description:</b><br>
 *
 */
namespace Kassiopeia
{

    template< class XManagerType >
    class KSInitializerPrototype :
        public KSInitializer
    {
        public:
            typedef KSBuilderSystem< XManagerType > BuilderSystem;

        public:
            KSInitializerPrototype( XManagerType* manager );
            virtual ~KSInitializerPrototype();

            virtual const string& GetSystemName() const;
            static const string& GetStaticSystemName();

            virtual const string& GetTypeName() const;
            static const string& GetStaticTypeName();

        protected:
            const static string fName;

        private:
            KSInitializerPrototype();
    };

    template< class XManagerType >
    KSInitializerPrototype< XManagerType >::KSInitializerPrototype( XManagerType* manager )
    {
        //KSBuilderSystem< XManagerType >::fSystemName = fName;
        KSBuilderSystem< XManagerType >::fManager = manager;
    }

    template< class XManagerType >
    KSInitializerPrototype< XManagerType >::~KSInitializerPrototype()
    {
    }

    template< class XManagerType >
    const string& KSInitializerPrototype< XManagerType >::GetSystemName() const
    {
        return fName;
    }

    template< class XManagerType >
    const string& KSInitializerPrototype< XManagerType >::GetStaticSystemName()
    {
        return fName;
    }

    template< class XManagerType >
    const string& KSInitializerPrototype< XManagerType >::GetTypeName() const
    {
        return fName;
    }

    template< class XManagerType >
    const string& KSInitializerPrototype< XManagerType >::GetStaticTypeName()
    {
        return fName;
    }

} // end namespace Kassiopeia

#endif // end ifndef KSInitializerPrototype_h
