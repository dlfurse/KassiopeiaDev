#ifndef KSBUILDER_H_
#define KSBUILDER_H_

#include "KSProcessor.h"

#include <map>
using std::map;

namespace Kassiopeia
{

    class KSBuilder :
        public KSProcessor
    {
        public:
            KSBuilder();
            virtual ~KSBuilder();

        public:
            virtual void ProcessToken( KSTokenBeginElement* aToken );
            virtual void ProcessToken( KSTokenEndElement* aToken );
            virtual void ProcessToken( KSTokenAttribute* aToken );
            virtual void ProcessToken( KSTokenData* aToken );

        protected:
            virtual Bool_t Start();
            virtual Bool_t AddAttribute( KSTokenAttribute* aToken );
            virtual Bool_t AddData( KSTokenData* aToken );
            virtual Bool_t End();

        protected:
            typedef map< string, KSBuilder* (*)() > FactoryMap;
            typedef FactoryMap::value_type FactoryEntry;
            typedef FactoryMap::iterator FactoryIt;
            typedef FactoryMap::const_iterator FactoryCIt;

            FactoryMap* fMap;
    };

}

#endif
