#ifndef KSMANAGERFACTORYTABLE_H_
#define KSMANAGERFACTORYTABLE_H_

#include <string>
using std::string;

#include <map>
using std::map;

namespace Kassiopeia
{

    class KSManagerFactory;

    class KSManagerFactoryTable
    {
        public:
            static KSManagerFactoryTable* GetInstance();
            virtual ~KSManagerFactoryTable();

        private:
            KSManagerFactoryTable();
            static KSManagerFactoryTable* fInstance;


        public:
            KSManagerFactory* GetFactory( const string& aTypeName );

            void Register( KSManagerFactory* aManagerFactory );
            void Unregister( KSManagerFactory* aManagerFactory );

        private:
            typedef map< string, KSManagerFactory* > FactoryMap;
            typedef FactoryMap::value_type FactoryEntry;
            typedef FactoryMap::iterator FactoryIt;
            typedef FactoryMap::const_iterator FactoryCIt;

            FactoryMap fMap;
    };

}

#endif
