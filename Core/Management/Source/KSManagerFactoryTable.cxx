#include "KSManagerFactoryTable.h"

#include "KSManagerFactory.h"

namespace Kassiopeia
{

    KSManagerFactoryTable* KSManagerFactoryTable::fInstance = NULL;
    KSManagerFactoryTable* KSManagerFactoryTable::GetInstance()
    {
        if( fInstance == NULL )
        {
            fInstance = new KSManagerFactoryTable();
        }
        return fInstance;
    }

    KSManagerFactoryTable::KSManagerFactoryTable() :
        fMap()
    {
    }
    KSManagerFactoryTable::~KSManagerFactoryTable()
    {
    }

    KSManagerFactory* KSManagerFactoryTable::GetFactory( const string& aTypeName )
    {
        FactoryIt It = fMap.find( aTypeName );
        if( It != fMap.end() )
        {
            return It->second;
        }
        return NULL;
    }

    void KSManagerFactoryTable::Register( KSManagerFactory* aManagerFactory )
    {
        FactoryIt It = fMap.find( aManagerFactory->GetManagerKey() );
        if( It != fMap.end() )
        {
            fMap.insert( FactoryEntry( aManagerFactory->GetManagerKey(), aManagerFactory ) );
        }
        return;
    }
    void KSManagerFactoryTable::Unregister( KSManagerFactory* aManagerFactory )
    {
        FactoryIt It = fMap.find( aManagerFactory->GetManagerKey() );
        if( It != fMap.end() )
        {
            fMap.erase( It );
        }
        return;
    }

}
