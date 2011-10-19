#include "KSManagerFactory.h"
#include "KSManagerFactoryTable.h"

namespace Kassiopeia
{

    KSManagerFactory::KSManagerFactory( const string& aKey, KSManager* (*aConstructor)() )
    {
        fKey = aKey;
        fConstructor = aConstructor;
        KSManagerFactoryTable::GetInstance()->Register( this );
    }
    KSManagerFactory::~KSManagerFactory()
    {
        KSManagerFactoryTable::GetInstance()->Unregister( this );
    }

    const string& KSManagerFactory::GetManagerKey() const
    {
        return fKey;
    }
    KSManager* KSManagerFactory::BuildManager() const
    {
        return (*fConstructor)();
    }

}
