#ifndef KMATHCOMPOSITEODE_H_
#define KMATHCOMPOSITEODE_H_

#include "KMathODE.h"

namespace Kassiopeia
{

    class KMathCompositeODE :
        public KMathODE
    {
        public:
            KMathCompositeODE( const size_t& aDimension );
            virtual ~KMathCompositeODE();

        private:
            KMathCompositeODE();

        public:
            Bool_t AddTerm( KMathODE* aTerm );
            Bool_t RemoveTerm( KMathODE* aTerm );

        public:
            virtual void CalculateDerivative();

        private:
            virtual void SetConditionAreaAction();
            virtual void SetDerivativeAreaAction();

        protected:
            enum
            {
                eMaxTerms = 64
            };
            size_t fCurrentTerm;
            size_t fEndTerm;
            KMathODE* fTerms[eMaxTerms];
            Double_t* fTermDerivatives[eMaxTerms];
    };

}

#endif
