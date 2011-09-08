#ifndef KSTRACK_H_
#define KSTRACK_H_

#include "KSQueue.h"

#include "Rtypes.h"
#include "TVector3.h"

#include <string>
using std::string;

namespace Kassiopeia
{

    class KSParticle;

    class KSTrack
    {
        public:
            KSTrack();
            ~KSTrack();

            void SetEventId( const Int_t& id );
            const Int_t& GetEventId() const;

            void SetTrackId( const Int_t& id );
            const Int_t& GetTrackId() const;

            void SetParentTrackId( const Int_t& id );
            const Int_t& GetParentTrackId() const;

            void SetPrimaryTrackId( const Int_t& id );
            const Int_t& GetPrimaryTrackId() const;

            void SetCreationName( const string& id );
            const string& GetCreationName() const;

            void SetExitName( const string& id );
            const string& GetExitName() const;

            void SetTotalRadiationDeltaE( const Double_t& eloss_synch );
            const Double_t& GetTotalRadiationDeltaE() const;

            void SetTotalScatteringDeltaE( const Double_t& eloss_scatter );
            const Double_t& GetTotalScatteringDeltaE() const;

            void SetTotalDecayDeltaE( const Double_t& eloss_decay );
            const Double_t& GetTotalDecayDeltaE() const;

            void SetTotalLength( const Double_t& length );
            const Double_t& GetTotalLength() const;

            void SetTotalTime( const Double_t& time );
            const Double_t& GetTotalTime() const;

            void SetTotalSteps( const UInt_t& steps );
            const UInt_t& GetTotalSteps() const;

            void SetTotalSecondaries( const UInt_t& secondaries );
            const UInt_t& GetTotalSecondaries() const;

            void SetInitialParticle( KSParticle* const initial );
            KSParticle* GetInitialParticle() const;

            void SetFinalParticle( KSParticle* const final );
            KSParticle* GetFinalParticle() const;

            KSQueue< KSTrack* >* GetSecondaryQueue() const;

        private:
            Int_t fEventId;
            Int_t fTrackId;
            Int_t fParentTrackId;
            Int_t fPrimaryTrackId;
            string fCreationName;
            string fExitName;
            UInt_t fTotalSteps;
            UInt_t fTotalSecondaries;
            Double_t fTotalLength;
            Double_t fTotalTime;
            Double_t fTotalRadiationDeltaE;
            Double_t fTotalScatteringDeltaE;
            Double_t fTotalDecayDeltaE;

            KSParticle* fInitialParticle;
            KSParticle* fFinalParticle;

            KSQueue< KSTrack* >* fSecondaryQueue;
    };

    inline void KSTrack::SetEventId( const Int_t& id )
    {
        fEventId = id;
        return;
    }
    inline const Int_t& KSTrack::GetEventId() const
    {
        return fEventId;
    }

    inline void KSTrack::SetTrackId( const Int_t& id )
    {
        fTrackId = id;
        return;
    }
    inline const Int_t& KSTrack::GetTrackId() const
    {
        return fTrackId;
    }

    inline void KSTrack::SetPrimaryTrackId( const Int_t& id )
    {
        fPrimaryTrackId = id;
        return;
    }
    inline const Int_t& KSTrack::GetPrimaryTrackId() const
    {
        return fPrimaryTrackId;
    }

    inline void KSTrack::SetParentTrackId( const Int_t& id )
    {
        fParentTrackId = id;
        return;
    }
    inline const Int_t& KSTrack::GetParentTrackId() const
    {
        return fParentTrackId;
    }

    inline void KSTrack::SetCreationName( const string& name )
    {
        fCreationName = name;
        return;
    }
    inline const string& KSTrack::GetCreationName() const
    {
        return fCreationName;
    }

    inline void KSTrack::SetInitialParticle( KSParticle* const initial )
    {
        fInitialParticle = initial;
        return;
    }
    inline KSParticle* KSTrack::GetInitialParticle() const
    {
        return fInitialParticle;
    }

    inline void KSTrack::SetFinalParticle( KSParticle* const final )
    {
        fFinalParticle = final;
        return;
    }
    inline KSParticle* KSTrack::GetFinalParticle() const
    {
        return fFinalParticle;
    }

    inline void KSTrack::SetExitName( const string& name )
    {
        fExitName = name;
        return;
    }
    inline const string& KSTrack::GetExitName() const
    {
        return fExitName;
    }

    inline void KSTrack::SetTotalSteps( const UInt_t& steps )
    {
        fTotalSteps = steps;
        return;
    }
    inline const UInt_t& KSTrack::GetTotalSteps() const
    {
        return fTotalSteps;
    }

    inline void KSTrack::SetTotalSecondaries( const UInt_t& secondaries )
    {
        fTotalSecondaries = secondaries;
        return;
    }
    inline const UInt_t& KSTrack::GetTotalSecondaries() const
    {
        return fTotalSecondaries;
    }

    inline void KSTrack::SetTotalRadiationDeltaE( const Double_t& eloss_synch )
    {
        fTotalRadiationDeltaE = eloss_synch;
        return;
    }
    inline const Double_t& KSTrack::GetTotalRadiationDeltaE() const
    {
        return fTotalRadiationDeltaE;
    }

    inline void KSTrack::SetTotalScatteringDeltaE( const Double_t& eloss_scatter )
    {
        fTotalScatteringDeltaE = eloss_scatter;
        return;
    }
    inline const Double_t& KSTrack::GetTotalScatteringDeltaE() const
    {
        return fTotalScatteringDeltaE;
    }

    inline void KSTrack::SetTotalDecayDeltaE( const Double_t& eloss_decay )
    {
        fTotalDecayDeltaE = eloss_decay;
        return;
    }
    inline const Double_t& KSTrack::GetTotalDecayDeltaE() const
    {
        return fTotalDecayDeltaE;
    }

    inline void KSTrack::SetTotalLength( const Double_t& length )
    {
        fTotalLength = length;
        return;
    }
    inline const Double_t& KSTrack::GetTotalLength() const
    {
        return fTotalLength;
    }

    inline void KSTrack::SetTotalTime( const Double_t& time )
    {
        fTotalTime = time;
        return;
    }
    inline const Double_t& KSTrack::GetTotalTime() const
    {
        return fTotalTime;
    }

    inline KSQueue< KSTrack* >* KSTrack::GetSecondaryQueue() const
    {
        return fSecondaryQueue;
    }

} // end Kassiopeia namespace

#endif  // KSTrack_h
