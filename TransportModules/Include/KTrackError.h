#ifndef KTRACKERROR_H_
#define KTRACKERROR_H_

#include "Rtypes.h"
#include "TVector3.h"

namespace Kassiopeia
{

    class KTrackError
    {
        public:
            KTrackError();
            virtual ~KTrackError();

            //*************
            //configuration
            //*************

        public:
            virtual void Reset() = 0;
            void SetData( Double_t* aBlock );

        protected:
            Double_t* fData;

            //*****************
            //dynamic variables
            //*****************

        public:
            virtual const Double_t& GetTimeError() = 0;
            virtual const TVector3& GetPositionError() = 0;
            virtual const TVector3& GetMomentumError() = 0;

        protected:
            mutable Double_t fTimeError;
            mutable TVector3 fPositionError;
            mutable TVector3 fMomentumError;
    };

    inline void KTrackError::SetData( Double_t* aBlock )
    {
        fData = aBlock;
        Reset();
        return;
    }

}

#endif
