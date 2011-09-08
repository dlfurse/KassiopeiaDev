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
            virtual Bool_t MidProcessToken( const KSTokenBeginParsing* aToken );
            virtual Bool_t MidProcessToken( const KSTokenEndParsing* aToken );
            virtual Bool_t MidProcessToken( const KSTokenBeginFile* aToken );
            virtual Bool_t MidProcessToken( const KSTokenEndFile* aToken );
            virtual Bool_t MidProcessToken( const KSTokenBeginElement* aToken );
            virtual Bool_t MidProcessToken( const KSTokenEndElement* aToken );
            virtual Bool_t MidProcessToken( const KSTokenAttribute* aToken );
            virtual Bool_t MidProcessToken( const KSTokenData* aToken );
            virtual Bool_t MidProcessToken( const KSTokenError* aToken );

            virtual Bool_t EndProcessToken( const KSTokenBeginParsing* aToken );
            virtual Bool_t EndProcessToken( const KSTokenEndParsing* aToken );
            virtual Bool_t EndProcessToken( const KSTokenBeginFile* aToken );
            virtual Bool_t EndProcessToken( const KSTokenEndFile* aToken );
            virtual Bool_t EndProcessToken( const KSTokenBeginElement* aToken );
            virtual Bool_t EndProcessToken( const KSTokenEndElement* aToken );
            virtual Bool_t EndProcessToken( const KSTokenAttribute* aToken );
            virtual Bool_t EndProcessToken( const KSTokenData* aToken );
            virtual Bool_t EndProcessToken( const KSTokenError* aToken );

            KSProcessor* fParent;
            KSProcessor* fChild;

            static KSTokenizer* fTokenizer;
    };

}

#endif
