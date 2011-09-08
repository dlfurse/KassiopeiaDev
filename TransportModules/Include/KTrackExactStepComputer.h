#ifndef KTRACKEXACTSTEPCOMPUTER_H_
#define KTRACKEXACTSTEPCOMPUTER_H_

#include "KTrackStepComputer.h"

namespace Kassiopeia
{

    class KTrackExactStepComputer :
        public KTrackStepComputer
    {
            //************
            //construction
            //************

        public:
            KTrackExactStepComputer( KMathODESolver* aSolver );
            virtual ~KTrackExactStepComputer();

        private:
            KTrackExactStepComputer();
            KTrackExactStepComputer( const KTrackExactStepComputer& );
    };
}

#endif

