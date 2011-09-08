#ifndef KMATHRK86_H_
#define KMATHRK86_H_

#include "KMathODESolver.h"

namespace Kassiopeia
{

    class KMathRK86 :
        public KMathODESolver
    {
        public:
            KMathRK86();
            virtual ~KMathRK86();

        private:
            enum
            {
                eSubsteps = 12,
                eConditions = eSubsteps + 1
            };

            virtual void CalculateSolution();

            virtual void SetODESystemAction();
            virtual void SetTimeStepAction();
            virtual void SetInitialConditionAreaAction();
            virtual void SetFinalConditionAreaAction();
            virtual void SetErrorConditionAreaAction();

            Double_t fSum6;
            Double_t fSum8;
            Double_t* fConditionAreas[eConditions];
            Double_t* fDerivativeAreas[eSubsteps];

            static const Double_t fA[eSubsteps - 1][eSubsteps - 1];
            static const Double_t fAFinal6[eSubsteps];
            static const Double_t fAFinal8[eSubsteps];
        };

    } // end namespace Kassiopeia

#endif // end ifndef KMathRK86_h
