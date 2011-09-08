#include "KMathODEBlock.h"

#include <iostream>
using std::cout;
using std::endl;

using namespace Kassiopeia;

int main()
{

    KMathODEBlock< 3 > BlockOne;
    BlockOne[0] = 1.;
    BlockOne[1] = 2.;
    BlockOne[2] = 3.;

    KMathODEBlock< 3 > BlockTwo;
    BlockTwo[0] = 4.;
    BlockTwo[1] = 5.;
    BlockTwo[2] = 6.;

    KMathODEBlock< 3 > BlockThree;
    BlockThree[0] = 7.;
    BlockThree[1] = 8.;
    BlockThree[2] = 9.;

    KMathODEBlock< 3 > BlockFour;
    BlockFour[0] = 10.;
    BlockFour[1] = 11.;
    BlockFour[2] = 12.;

    KMathODEBlock< 3 > BlockFive;
    BlockFive = BlockOne + (100.*BlockThree) + 2.*(BlockFour/1000.);

    cout << "[ " << BlockFive[0] << ", " << BlockFive[1] << ", " << BlockFive[2] << " ]" << endl;

    return 0;
}

