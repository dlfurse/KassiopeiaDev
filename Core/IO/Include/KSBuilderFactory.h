#ifndef KSPROCESSFACTORY_H_
#define KSPROCESSFACTORY_H_

#include "KSProcess.h"

#include <map>
using std::map;

namespace Kassiopeia
{

    class KSProcessorFactory
    {
        public:
            KSProcessorFactory( const string& aKey );
            virtual ~KSProcessorFactory();

        private:
            KSProcessorFactory();
            KSProcessorFactory( const KSProcessorFactory& );

            //************
            //construction
            //************

        public:
            virtual KSProcess* BuildProcess() = 0;

            //**************
            //identification
            //**************

        public:
            void SetKey( const string& aKey );
            const string& GetKey() const;

        private:
            string fKey;

            //*****
            //table
            //*****

        public:
            static void AddFactory( KSProcessorFactory* aFactory );
            static KSProcessorFactory* GetFactory( const string& aKey );
            static void RemoveFactory( KSProcessorFactory* aFactory );

        private:
            typedef map< string, KSProcessorFactory* > FactoryMap;
            typedef FactoryMap::value_type FactoryEntry;
            typedef FactoryMap::iterator FactoryIt;
            typedef FactoryMap::const_iterator FactoryCIt;

            static FactoryMap* fMap;
    };

}

#endif
