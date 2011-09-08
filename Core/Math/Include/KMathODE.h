#ifndef KMATHODE_H_
#define KMATHODE_H_

#include "Rtypes.h"

namespace Kassiopeia
{

    class KMathODE
    {

        public:
            KMathODE( const size_t& aDimension );
            virtual ~KMathODE();

        private:
            KMathODE();
            KMathODE( const KMathODE& );

        public:
            const size_t& GetDimension();

        protected:
            const size_t fDimension;

        public:
            virtual void CalculateDerivative() = 0;

        public:
            void SetConditionArea( Double_t* aConditionArea );
            void SetDerivativeArea( Double_t* aDerivativeArea );

        public:
            Double_t* fConditionArea;
            Double_t* fDerivativeArea;

        private:
            virtual void SetConditionAreaAction() = 0;
            virtual void SetDerivativeAreaAction() = 0;
    };

    inline const size_t& KMathODE::GetDimension()
    {
        return fDimension;
    }

    inline void KMathODE::SetConditionArea( Double_t* aConditionArea )
    {
        fConditionArea = aConditionArea;
        SetConditionAreaAction();
        return;
    }
    inline void KMathODE::SetDerivativeArea( Double_t* aDerivativeArea )
    {
        fDerivativeArea = aDerivativeArea;
        SetDerivativeAreaAction();
        return;
    }

}

#endif
