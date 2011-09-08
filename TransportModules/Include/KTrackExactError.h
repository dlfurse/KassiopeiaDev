#ifndef KTRACKEXACTERROR_H_
#define KTRACKEXACTERROR_H_

#include "KTrackError.h"

namespace Kassiopeia
{

    class KTrackExactError :
        public KTrackError
    {
        public:
            KTrackExactError();
            virtual ~KTrackExactError();

            //*************
            //configuration
            //*************

        public:
            virtual void Reset();

            //*****************
            //dynamic variables
            //*****************

        public:
            virtual const Double_t& GetTimeError();
            virtual const TVector3& GetPositionError();
            virtual const TVector3& GetMomentumError();
    };

}

#endif
