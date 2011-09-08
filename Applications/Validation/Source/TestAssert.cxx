#include "KSAssert.h"
#include "KSTypeLogic.h"

#include <iostream>
using std::cout;
using std::endl;

//#define TESTSTATICASSERTION

using namespace Kassiopeia;

int main()
{

    KSASSERT( 1 < 2, one_is_not_less_than_two )

#ifdef TESTSTATICASSERTION
    KSASSERT( (KSTypeEqual< int, double >::Value), int_and_double_are_not_the_same_types )
#endif

    cout << "to see a compiler error, you somehow have to define the macro TESTSTATICASSERION.  there is probably a way to do this with make." << endl;

    return 0;
}

