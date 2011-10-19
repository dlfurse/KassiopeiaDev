#include "KSManagerInstanceTable.h"
#include "KSManager.h"

#include "KSManagerFactoryTable.h"
#include "KSManagerFactory.h"

namespace Kassiopeia
{

    KSManagerInstanceTable* KSManagerInstanceTable::fInstance = NULL;
    KSManagerInstanceTable* KSManagerInstanceTable::GetInstance()
    {
        if( fInstance == NULL )
        {
            fInstance = new KSManagerInstanceTable();
        }
        return fInstance;
    }

    KSManagerInstanceTable::KSManagerInstanceTable() :
        fMap()
    {
    }
    KSManagerInstanceTable::~KSManagerInstanceTable()
    {
    }

    KSManager* KSManagerInstanceTable::GetManager( const string& aTypeName )
    {
        FactoryIt It = fMap.find( aTypeName );
        if( It != fMap.end() )
        {
            return It->second;
        }
        return NULL;
    }
    KSManager* KSManagerInstanceTable::DemandManager( const string& aTypeName )
    {
        FactoryIt It = fMap.find( aTypeName );
        if( It != fMap.end() )
        {
            return It->second;
        }

        KSManagerFactory* aFactory = KSManagerFactoryTable::GetInstance()->GetFactory( aTypeName );
        if( aFactory != NULL )
        {
            return aFactory->BuildManager();
        }

        return NULL;
    }

    void KSManagerInstanceTable::Register( KSManager* aManager )
    {
        FactoryIt It = fMap.find( aManager->GetKey() );
        if( It == fMap.end() )
        {
            fMap.insert( FactoryEntry( aManager->GetKey(), aManager ) );
        }
        return;
    }
    void KSManagerInstanceTable::Unregister( KSManager* aManager )
    {
        FactoryIt It = fMap.find( aManager->GetKey() );
        if( It != fMap.end() )
        {
            fMap.erase( It );
        }
        return;
    }

} /* namespace Kassiopeia */
