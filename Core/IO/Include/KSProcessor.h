#ifndef KSPROCESSOR_H_
#define KSPROCESSOR_H_

#include "KSTokenBeginParsing.h"
#include "KSTokenEndParsing.h"
#include "KSTokenBeginFile.h"
#include "KSTokenEndFile.h"
#include "KSTokenBeginElement.h"
#include "KSTokenEndElement.h"
#include "KSTokenAttribute.h"
#include "KSTokenData.h"
#include "KSTokenError.h"

#include "Rtypes.h"

namespace Kassiopeia
{

    class KSTokenizer;

    class KSProcessor
    {
        public:
            KSProcessor();
            virtual ~KSProcessor();

            virtual void DropProcessor( KSProcessor* aNewProcessor );
            virtual void LiftProcessor( KSProcessor* anOldProcessor );

            virtual void ProcessToken( KSTokenBeginParsing* aToken );
            virtual void ProcessToken( KSTokenEndParsing* aToken );
            virtual void ProcessToken( KSTokenBeginFile* aToken );
            virtual void ProcessToken( KSTokenEndFile* aToken );
            virtual void ProcessToken( KSTokenBeginElement* aToken );
            virtual void ProcessToken( KSTokenEndElement* aToken );
            virtual void ProcessToken( KSTokenAttribute* aToken );
            virtual void ProcessToken( KSTokenData* aToken );
            virtual void ProcessToken( KSTokenError* aToken );

        protected:
            KSProcessor* fParent;
            KSProcessor* fChild;

            static KSTokenizer* fTokenizer;
    };

}

#endif
