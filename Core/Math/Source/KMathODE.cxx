#include "KMathODE.h"

namespace Kassiopeia
{

    KMathODE::KMathODE( const size_t& aDimension ) :
        fDimension( aDimension ),
        fConditionArea( NULL ),
        fDerivativeArea( NULL )
    {
    }

    KMathODE::~KMathODE()
    {
    }
}

//end namespace Kassiopeia
