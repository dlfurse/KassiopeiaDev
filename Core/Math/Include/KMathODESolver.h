#ifndef KMATHODESOLVER_H_
#define KMATHODESOLVER_H_

#include "Rtypes.h"

namespace Kassiopeia
{

    class KMathODE;

    class KMathODESolver
    {
        public:
            KMathODESolver( const size_t& aSubstepCount );
            virtual ~KMathODESolver();

        private:
            KMathODESolver();
            KMathODESolver( const KMathODESolver& );

        public:
            const size_t& GetSubSteps();

        protected:
            const size_t fSubSteps;

        public:
            virtual void CalculateSolution() = 0;

        public:
            void SetODE( KMathODE* anODE );
            void SetTimeStep( const Double_t& aTimeStep );
            void SetInitialConditionArea( Double_t* anInitialConditionArea );
            void SetFinalConditionArea( Double_t* aFinalConditionArea );
            void SetErrorConditionArea( Double_t* anErrorConditionArea );

        protected:
            KMathODE* fODESystem;
            Double_t fTimeStep;
            Double_t* fInitialConditionArea;
            Double_t* fFinalConditionArea;
            Double_t* fErrorConditionArea;

        private:
            virtual void SetODESystemAction() = 0;
            virtual void SetTimeStepAction() = 0;
            virtual void SetInitialConditionAreaAction() = 0;
            virtual void SetFinalConditionAreaAction() = 0;
            virtual void SetErrorConditionAreaAction() = 0;
    };

    inline void KMathODESolver::SetODE( KMathODE* anODE )
    {
        fODESystem = anODE;
        SetODESystemAction();
        return;
    }
    inline void KMathODESolver::SetTimeStep( const Double_t& aTimeStep )
    {
        fTimeStep = aTimeStep;
        SetTimeStepAction();
        return;
    }
    inline void KMathODESolver::SetInitialConditionArea( Double_t* anInitialConditionArea )
    {
        fInitialConditionArea = anInitialConditionArea;
        SetInitialConditionAreaAction();
        return;
    }
    inline void KMathODESolver::SetFinalConditionArea( Double_t* aFinalConditionArea )
    {
        fFinalConditionArea = aFinalConditionArea;
        SetFinalConditionAreaAction();
        return;
    }
    inline void KMathODESolver::SetErrorConditionArea( Double_t* anErrorConditionArea )
    {
        fErrorConditionArea = anErrorConditionArea;
        SetErrorConditionAreaAction();
        return;
    }

}

#endif
