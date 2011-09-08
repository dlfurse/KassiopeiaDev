#ifndef KTRACKEXACTLORENTZODE_H_
#define KTRACKEXACTLORENTZODE_H_

#include "KTrackODE.h"

namespace Kassiopeia
{

    class KTrackLorentzODE :
        public KTrackODE
    {
        public:
            KTrackLorentzODE();
            virtual ~KTrackLorentzODE();

            virtual void CalculateDerivative();
    };

}

#endif
