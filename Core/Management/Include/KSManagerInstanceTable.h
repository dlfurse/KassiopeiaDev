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
            KSManager* DemandManager( const string& aTypeName );

            void Register( KSManager* KSManager );
            void Unregister( KSManager* KSManager );

        private:
            typedef map< string, KSManager* > ManagerMap;
            typedef ManagerMap::value_type FactoryEntry;
            typedef ManagerMap::iterator FactoryIt;
            typedef ManagerMap::const_iterator FactoryCIt;

            ManagerMap fMap;
    };

}

#endif
