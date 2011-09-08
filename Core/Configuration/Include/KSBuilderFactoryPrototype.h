#ifndef KSBuilderFactoryPrototype_h
#define KSBuilderFactoryPrototype_h


/**
 * @file

 * @brief contains KSBuilderFactoryPrototype

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
 * @class Kassiopeia::KSBuilderFactoryPrototype
 @author D. Furse

 @brief templated class prototype for all builder factories

 @details
 <b>Detailed Description:</b><br>


 */


#include "KSBuilderFactory.h"

#include "KSBuilderFactoryTable.h"

namespace Kassiopeia
{

    template< class XBuilderType >
    class KSBuilderFactoryPrototype :
        public KSBuilderFactory
    {
        public:
            KSBuilderFactoryPrototype();
            virtual ~KSBuilderFactoryPrototype();

            KSBuilder* Build() const;

            const string& GetSystemName() const;
            const string& GetTypeName() const;
    };

    template< class XBuilderType >
    KSBuilderFactoryPrototype< XBuilderType >::KSBuilderFactoryPrototype() :
        KSBuilderFactory()
    {
        KSBuilderFactoryTable::GetInstance()->Register( this );
    }
    template< class XBuilderType >
    KSBuilderFactoryPrototype< XBuilderType >::~KSBuilderFactoryPrototype()
    {
    }

    template< class XBuilderType >
    KSBuilder* KSBuilderFactoryPrototype< XBuilderType >::Build() const
    {
        return new XBuilderType();
    }

    template< class XBuilderType >
    const string& KSBuilderFactoryPrototype< XBuilderType >::GetSystemName() const
    {
        return XBuilderType::GetStaticSystemName();
    }
    template< class XBuilderType >
    const string& KSBuilderFactoryPrototype< XBuilderType >::GetTypeName() const
    {
        return XBuilderType::GetStaticTypeName();
    }

} // end namespace Kassiopeia

#endif // end ifndef KSBuilderFactoryPrototype
