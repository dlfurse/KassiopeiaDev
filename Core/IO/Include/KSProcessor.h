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

            virtual const string& GetTypeName() const = 0;

            void DropProcessor( KSProcessor* aNewProcessor );
            void LiftProcessor( KSProcessor* anOldProcessor );

            virtual void ProcessToken( const KSTokenBeginParsing* aToken );
            virtual void ProcessToken( const KSTokenEndParsing* aToken );
            virtual void ProcessToken( const KSTokenBeginFile* aToken );
            virtual void ProcessToken( const KSTokenEndFile* aToken );
            virtual void ProcessToken( const KSTokenBeginElement* aToken );
            virtual void ProcessToken( const KSTokenEndElement* aToken );
            virtual void ProcessToken( const KSTokenAttribute* aToken );
            virtual void ProcessToken( const KSTokenData* aToken );
            virtual void ProcessToken( const KSTokenError* aToken );

        protected:
            virtual Bool_t ProcessStreamToken( const KSTokenBeginParsing* aToken );
            virtual Bool_t ProcessStreamToken( const KSTokenEndParsing* aToken );
            virtual Bool_t ProcessStreamToken( const KSTokenBeginFile* aToken );
            virtual Bool_t ProcessStreamToken( const KSTokenEndFile* aToken );
            virtual Bool_t ProcessStreamToken( const KSTokenBeginElement* aToken );
            virtual Bool_t ProcessStreamToken( const KSTokenEndElement* aToken );
            virtual Bool_t ProcessStreamToken( const KSTokenAttribute* aToken );
            virtual Bool_t ProcessStreamToken( const KSTokenData* aToken );
            virtual Bool_t ProcessStreamToken( const KSTokenError* aToken );

            virtual Bool_t ProcessEndToken( const KSTokenBeginParsing* aToken );
            virtual Bool_t ProcessEndToken( const KSTokenEndParsing* aToken );
            virtual Bool_t ProcessEndToken( const KSTokenBeginFile* aToken );
            virtual Bool_t ProcessEndToken( const KSTokenEndFile* aToken );
            virtual Bool_t ProcessEndToken( const KSTokenBeginElement* aToken );
            virtual Bool_t ProcessEndToken( const KSTokenEndElement* aToken );
            virtual Bool_t ProcessEndToken( const KSTokenAttribute* aToken );
            virtual Bool_t ProcessEndToken( const KSTokenData* aToken );
            virtual Bool_t ProcessEndToken( const KSTokenError* aToken );

            KSProcessor* fParent;
            KSProcessor* fChild;

            static KSTokenizer* fTokenizer;
    };

}

#endif
