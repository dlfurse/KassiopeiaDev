#include "KMathODESolver.h"

namespace Kassiopeia
{

    KMathODESolver::KMathODESolver( const size_t& aSubStepCount ) :
        fSubSteps( aSubStepCount ),
        fODESystem( NULL ),
        fTimeStep( 0. ),
        fInitialConditionArea( NULL ),
        fFinalConditionArea( NULL ),
        fErrorConditionArea( NULL )
    {
    }

    KMathODESolver::~KMathODESolver()
    {
    }
}
