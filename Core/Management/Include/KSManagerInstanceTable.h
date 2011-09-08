#ifndef KSMANAGERINSTANCETABLE_H_
#define KSMANAGERINSTANCETABLE_H_

#include <string>
using std::string;

#include <map>
using std::map;

namespace Kassiopeia
{

    class KSManager;

    class KSManagerInstanceTable
    {
        public:
            static KSManagerInstanceTable* GetInstance();
            virtual ~KSManagerInstanceTable();

        private:
            KSManagerInstanceTable();
            static KSManagerInstanceTable* fInstance;

        public:
            KSManager* GetManager( const string& aTypeName );

            void Register( KSManager* KSManager );
            void Unregister( KSManager* KSManager );

        private:
            typedef map< string, KSManager* > FactoryMap;
            typedef FactoryMap::value_type FactoryEntry;
            typedef FactoryMap::iterator FactoryIt;
            typedef FactoryMap::const_iterator FactoryCIt;

            FactoryMap fMap;
    };

}

#endif
