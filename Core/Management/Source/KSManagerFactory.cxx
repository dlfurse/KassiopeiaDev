#include "KSManagerFactory.h"
#include "KSManagerFactoryTable.h"

namespace Kassiopeia
{

    KSManagerFactory::KSManagerFactory()
    {
        KSManagerFactoryTable::GetInstance()->Register( this );
    }

    KSManagerFactory::~KSManagerFactory()
    {
        KSManagerFactoryTable::GetInstance()->Unregister( this );
    }

}
