#ifndef KASSIOPEIA_DATASTRUCTURE_PARTICLEFACTORYTABLE_H
#define KASSIOPEIA_DATASTRUCTURE_PARTICLEFACTORYTABLE_H 1

/**
 * @file

 * @brief contains KSParticleFactoryTable
 * @details
 * <b>Revision History:</b>
 *   \verbatim
 *   Date       Name          Brief description
 *   -----------------------------------------------
 *   10/02/08   D. Furse      First Version
 *   10/03/09   D. Furse      Loki removed, TVector3s in
 *   \endverbatim
 */

/*!
 @class Kassiopeia::KSParticleFactoryTable
 @author D. Furse

 @brief The KSParticleFactoryTable class is a singleton lookup table for particle
 factories

 @details
 <b>Building and Usage:</b><br>
 This class is a singleton.  To get its pointer, simply use
 KSParticleFactoryTable::GetInstance().  Once the pointer is obtained, a particle
 may be built either by Katrin particle ID number or by name.  For instance, to
 build an electron, one can use GetParticleFactory("electron"), by name or
 GetParticleFactory(11), by its ID.

 <b>Architecture and Design</b><br>
 This class really just serves as a central location where particle factories
 are stored, giving a user the ability to make a new particle safely at any
 time.  Inside, the design is quite simple, consisting of two maps (one for ID
 lookup and one for name lookup) wrapped in a singleton class.

 Note that the lookup methods check if the lookup key really exists in the map
 first, and they deliver a null pointer if there is no such particle defined.


 */

#include "Rtypes.h"

#include <map>

namespace Kassiopeia
{

    class KSParticleFactory;

    class KSParticleFactoryTable
    {
        public:
            typedef std::map< Long_t, const KSParticleFactory* > ParticleMap;
            typedef ParticleMap::iterator ParticleMapIt;
            typedef ParticleMap::const_iterator ParticleMapCIt;

        public:
            static KSParticleFactoryTable* GetInstance();
            ~KSParticleFactoryTable();

            void Register( const KSParticleFactory* const );
            void Print();

            const KSParticleFactory* GetParticleFactory( const Long_t& ) const;

        private:
            KSParticleFactoryTable();

            ParticleMap* fMap;
    };
}

#endif
