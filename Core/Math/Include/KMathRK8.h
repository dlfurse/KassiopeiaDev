#ifndef KMATHRK8_H_
#define KMATHRK8_H_

#include "KMathODESolver.h"

namespace Kassiopeia
{

    class KMathRK8 :
        public KMathODESolver
    {
        public:
            KMathRK8();
            virtual ~KMathRK8();

        private:
            enum
            {
                eSubsteps = 13,
                eConditions = eSubsteps + 1
            };

            virtual void CalculateSolution();

            virtual void SetODESystemAction();
            virtual void SetTimeStepAction();
            virtual void SetInitialConditionAreaAction();
            virtual void SetFinalConditionAreaAction();
            virtual void SetErrorConditionAreaAction();


            Double_t fSum;
            Double_t* fDerivativeAreas[eSubsteps];
            Double_t* fConditionAreas[eConditions];

            static const Double_t fA[eSubsteps][eSubsteps];
        };

    } // end namespace Kassiopeia

#endif // end ifndef KMathRK8_h
