#ifndef KSSTEP_H_
#define KSSTEP_H_

#include "KSQueue.h"

#include "Rtypes.h"
#include "TVector3.h"

namespace Kassiopeia
{

    class KSParticle;
    class KSTrack;

    class KSStep
    {
        public:
            KSStep();
            ~KSStep();

            void SetInitialParticle( KSParticle* const anInitialParticle );
            KSParticle* GetInitialParticle() const;

            void SetFinalParticle( KSParticle* const aFinalParticle );
            KSParticle* GetFinalParticle() const;

        private:
            Int_t fTrackId;
            Int_t fStepId;

            Double_t fElapsedLength;
            Double_t fElapsedTime;

            Bool_t fRadiationOccurred;
            Double_t fRadiationDeltaE;

            Bool_t fScatteringOccurred;
            Double_t fScatteringDeltaE;

            Bool_t fDecayOccurred;
            Double_t fDecayDeltaE;

            KSParticle* fInitialParticle;
            KSParticle* fFinalParticle;

            KSQueue< KSTrack* >* fSecondaryQueue;
    };

    inline void KSStep::SetInitialParticle( KSParticle* const anInitialParticle )
    {
        fInitialParticle = anInitialParticle;
        return;
    }
    inline KSParticle* KSStep::GetInitialParticle() const
    {
        return fInitialParticle;
    }

    inline void KSStep::SetFinalParticle( KSParticle* const aFinalParticle )
    {
        fFinalParticle = aFinalParticle;
        return;
    }
    inline KSParticle* KSStep::GetFinalParticle() const
    {
        return fFinalParticle;
    }

}

#endif
