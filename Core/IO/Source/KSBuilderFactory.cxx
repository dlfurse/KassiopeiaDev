#include "KSProcessorFactory.h"

namespace Kassiopeia
{

    KSProcessorFactory::KSProcessorFactory( const string& aKey )
    {
        SetKey( aKey );
        AddFactory( this );
    }
    KSProcessorFactory::~KSProcessorFactory()
    {
        RemoveFactory( this );
    }

    void KSProcessorFactory::SetKey( const string& aKey )
    {
        fKey = aKey;
    }
    const string& KSProcessorFactory::GetKey() const
    {
        return fKey;
    }

    KSProcessorFactory::FactoryMap* KSProcessorFactory::fMap = NULL;
    void KSProcessorFactory::AddFactory( KSProcessorFactory* aFactory )
    {
        if( fMap == NULL )
        {
            fMap = new FactoryMap();
        }
        else
        {
            if( fMap->find( aFactory->GetKey() ) == fMap->end() )
            {
                fMap->insert( FactoryEntry( aFactory->GetKey(), aFactory ) );
                return;
            }
        }
        return;
    }
    KSProcessorFactory* KSProcessorFactory::GetFactory( const string& aKey )
    {
        if( fMap == NULL )
        {
            fMap = new FactoryMap();
        }
        else
        {
            FactoryIt It = fMap->find( aKey );
            if( It != fMap->end() )
            {
                return It->second;
            }
        }
        return NULL;
    }
    void KSProcessorFactory::RemoveFactory( KSProcessorFactory* aFactory )
    {
        if( fMap == NULL )
        {
            fMap = new FactoryMap();
        }
        else
        {
            FactoryIt It = fMap->find( aFactory->GetKey() );
            if( fMap->find( aFactory->GetKey() ) == fMap->end() )
            {
                fMap->erase( It );
            }
        }
        return;
    }

}
