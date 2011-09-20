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

            void DropProcessor( KSProcessor* aNewProcessor );
            void LiftProcessor( KSProcessor* anOldProcessor );

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
            virtual Bool_t ProcessStreamToken( KSTokenBeginParsing* aToken );
            virtual Bool_t ProcessStreamToken( KSTokenEndParsing* aToken );
            virtual Bool_t ProcessStreamToken( KSTokenBeginFile* aToken );
            virtual Bool_t ProcessStreamToken( KSTokenEndFile* aToken );
            virtual Bool_t ProcessStreamToken( KSTokenBeginElement* aToken );
            virtual Bool_t ProcessStreamToken( KSTokenEndElement* aToken );
            virtual Bool_t ProcessStreamToken( KSTokenAttribute* aToken );
            virtual Bool_t ProcessStreamToken( KSTokenData* aToken );
            virtual Bool_t ProcessStreamToken( KSTokenError* aToken );

            virtual Bool_t ProcessEndToken( KSTokenBeginParsing* aToken );
            virtual Bool_t ProcessEndToken( KSTokenEndParsing* aToken );
            virtual Bool_t ProcessEndToken( KSTokenBeginFile* aToken );
            virtual Bool_t ProcessEndToken( KSTokenEndFile* aToken );
            virtual Bool_t ProcessEndToken( KSTokenBeginElement* aToken );
            virtual Bool_t ProcessEndToken( KSTokenEndElement* aToken );
            virtual Bool_t ProcessEndToken( KSTokenAttribute* aToken );
            virtual Bool_t ProcessEndToken( KSTokenData* aToken );
            virtual Bool_t ProcessEndToken( KSTokenError* aToken );

            KSProcessor* fParent;
            KSProcessor* fChild;

            static KSTokenizer* fTokenizer;
    };

}

#endif
