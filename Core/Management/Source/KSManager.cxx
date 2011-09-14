#include "KSManager.h"

#include "KSManagerInstanceTable.h"

namespace Kassiopeia
{

    KSManager::KSManager( const string& aKey ) :
        fKey( aKey ),
        fState( eInstantiated )
    {
        KSManagerInstanceTable::GetInstance()->Register( this );
    }

    KSManager::~KSManager()
    {
        KSManagerInstanceTable::GetInstance()->Unregister( this );
    }


    void KSManager::Setup()
    {
        if( fState == eInstantiated )
        {
            SetupManagerDependencies();
            SetupManagerSubclass();
            fState = eSetup;
        }
        return;
    }

    void KSManager::Prepare()
    {
        if( fState == eSetup )
        {
            PrepareManagerDependencies();
            PrepareManagerSubclass();
            fState = ePrepared;
        }
        return;
    }

    void KSManager::Shutdown()
    {
        if( fState == ePrepared )
        {
            ShutdownManagerDependencies();
            ShutdownManagerSubclass();
            fState = eShutdown;
        }
        return;
    }

    void KSManager::Abort()
    {
        if( fState == ePrepared )
        {
            AbortManagerDependencies();
            AbortManagerSubclass();
            fState = eShutdown;
        }
        return;
    }


    void KSManager::SetupManagerDependencies()
    {
        DependencyIt It;
        for( It = fMap.begin(); It != fMap.end(); It++ )
        {
            It->second = KSManagerInstanceTable::GetInstance()->GetManager( It->first );
        }
    }

    void KSManager::PrepareManagerDependencies()
    {
        DependencyIt It;
        for( It = fMap.begin(); It != fMap.end(); It++ )
        {
            It->second->Prepare();
        }
    }

    void KSManager::ShutdownManagerDependencies()
    {
        DependencyIt It;
        for( It = fMap.begin(); It != fMap.end(); It++ )
        {
            It->second->Shutdown();
        }
    }

    void KSManager::AbortManagerDependencies()
    {
        DependencyIt It;
        for( It = fMap.begin(); It != fMap.end(); It++ )
        {
            It->second->Abort();
        }
    }


    void KSManager::AddDependency( const string& aTypeName )
    {
        DependencyIt It = fMap.find( aTypeName );
        if( It != fMap.end() )
        {
            fMap.insert( DependencyEntry( aTypeName, NULL ));
        }
        return;
    }
    Bool_t KSManager::IsDependentOn( const string& aTypeName )
    {
        DependencyIt It = fMap.find( aTypeName );
        if( It != fMap.end() )
        {
            return kTRUE;
        }
        return kFALSE;
    }

} // end Kassiopeia namespace
