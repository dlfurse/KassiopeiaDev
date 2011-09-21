#ifndef KSLOOPPROCESSOR_H_
#define KSLOOPPROCESSOR_H_

#include "KSProcessor.h"

#include <stack>
using std::stack;

#include <vector>
using std::vector;

#include <sstream>
using std::stringstream;

namespace Kassiopeia
{

    class KSLoopProcessor :
        public KSProcessor
    {
        public:
            KSLoopProcessor();
            virtual ~KSLoopProcessor();

            virtual void ProcessToken( KSTokenBeginElement* aToken );
            virtual void ProcessToken( KSTokenEndElement* aToken );
            virtual void ProcessToken( KSTokenAttribute* aToken );
            virtual void ProcessToken( KSTokenData* aToken );

        private:
            void Reset();
            void Dispatch( KSToken* aToken );

            typedef enum
            {
                eInactive, eActive, eCollecting
            } State;
            State fState;
            UInt_t fCount;
            string fVariable;
            Int_t fEndValue;
            Int_t fStartValue;
            Int_t fStepValue;

            typedef vector< KSToken* > TokenVector;
            typedef TokenVector::iterator TokenIt;
            typedef TokenVector::const_iterator TokenCIt;
            TokenVector fTokens;

            typedef struct
            {
                public:
                    string fVariable;
                    Int_t fEndValue;
                    Int_t fStartValue;
                    Int_t fStepValue;
                    TokenVector fTokens;

            } Loop;
            stack< Loop* > fLoopStack;
    };

}

#endif
