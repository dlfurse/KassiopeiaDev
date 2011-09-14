#include "KSParticleFactoryTable.h"

#include "KSParticleFactory.h"
//#include "KSMessage.h"

namespace Kassiopeia
{

    static KSParticleFactoryTable* sParticleFactoryTable = 0;

    KSParticleFactoryTable::KSParticleFactoryTable() :
        fMap( new ParticleMap() )
    {
    }
    KSParticleFactoryTable::~KSParticleFactoryTable()
    {
        if( fMap != 0 )
        {
            ParticleMapIt MapIt;
            for( MapIt = fMap->begin(); MapIt != fMap->end(); MapIt++ )
            {
                if( MapIt->second != NULL )
                {
                    delete MapIt->second;
                    MapIt->second = NULL;
                }
            }
            delete fMap;
        }
    }

    KSParticleFactoryTable* KSParticleFactoryTable::GetInstance()
    {
        if( sParticleFactoryTable == 0 )
        {
            sParticleFactoryTable = new KSParticleFactoryTable();
        }
        return sParticleFactoryTable;
    }

    void KSParticleFactoryTable::Register( const KSParticleFactory* const aParticleFactory )
    {
        ParticleMapIt MapIt = fMap->find( aParticleFactory->GetPID() );
        if( MapIt != fMap->end() )
        {
            //msg = eWarning;
            //msg < "KSParticleFactoryTable::Register";
            //msg << "a factory for pid " << aParticleFactory->GetPID() << " is already registered, the old one will be deleted and the new one registered in its place" << end;

            if( MapIt->second != NULL )
            {
                delete MapIt->second;
                MapIt->second = NULL;
            }
            fMap->erase( MapIt );
        }

        fMap->insert( ParticleMap::value_type( aParticleFactory->GetPID(), aParticleFactory ) );
        return;
    }
    void KSParticleFactoryTable::Print()
    {
        //msg = eMessage;
        //msg < "KSParticleFactoryTable::Print";
        for( ParticleMap::iterator MapIt = fMap->begin(); MapIt != fMap->end(); MapIt++ )
        {
            //msg << "\t" << MapIt->second->GetPID() << ret;
        }
        //msg << end;

        return;
    }

    const KSParticleFactory* KSParticleFactoryTable::GetParticleFactory( const Long_t& aParticleID ) const
    {
        ParticleMapCIt MapCIt = fMap->find( aParticleID );
        if( MapCIt == fMap->end() )
        {
            //msg = eWarning;
            //msg < "KSParticleFactoryTable::GetParticleFactory";
            //msg << aParticleID << " was not found, ghost particle factory returned instead" << end;

            MapCIt = fMap->find( 0 );
        }

        return (MapCIt->second);
    }

}
