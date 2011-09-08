#ifndef KTRACKEXACTPARTICLE_H_
#define KTRACKEXACTPARTICLE_H_

#include "KTrackParticle.h"

#include "KSConst.h"

#include "TMath.h"

namespace Kassiopeia
{

    class KTrackExactParticle :
        public KTrackParticle
    {
        public:
            KTrackExactParticle();
            virtual ~KTrackExactParticle();

            //*************
            //configuration
            //*************

        public:
            virtual void Reset();

            //*******
            //actions
            //*******

        public:
            virtual void PullUpdate();
            virtual void PushUpdate() const;

            //*****************
            //dynamic variables
            //*****************

        public:
            //setters
            virtual const Double_t& GetTime() const;
            virtual const TVector3& GetPosition() const;
            virtual const TVector3& GetMomentum() const;
            virtual const TVector3& GetVelocity() const;
            virtual const Double_t& GetLorentzFactor() const;
            virtual const Double_t& GetKineticEnergy() const;

            virtual const TVector3& GetMagneticField() const;
            virtual const TVector3& GetElectricField() const;
            virtual const Double_t& GetElectricPotential() const;
            virtual const Double_t& GetGradientB( const TVector3& aDirection ) const;
            virtual const Double_t& GetGradientE( const TVector3& aDirection ) const;

            virtual const Double_t& GetLongMomentum() const;
            virtual const Double_t& GetTransMomentum() const;
            virtual const Double_t& GetLongVelocity() const;
            virtual const Double_t& GetTransVelocity() const;
            virtual const Double_t& GetCyclotronFrequency() const;
            virtual const Double_t& GetOrbitalMagneticMoment() const;

            /*
            virtual void SetTime( const Double_t& aTime );
            virtual void SetPosition( const TVector3& aPosition );
            virtual void SetMomentum( const TVector3& aMomentum );
            virtual void SetVelocity( const TVector3& aVelocity );
            virtual void SetLorentzFactor( const Double_t& aLorentzFactor );
            virtual void SetKineticEnergy( const Double_t& aKineticEnergy );

            virtual void SetLongMomentum( const Double_t& aLongMomentum );
            virtual void SetTransMomentum( const Double_t& aTransMomentum );
            virtual void SetLongVelocity( const Double_t& aLongVelocity );
            virtual void SetTransVelocity( const Double_t& aTransVelocity );
            virtual void SetCyclotronFrequency( const Double_t& aCyclotronFrequency );
            virtual void SetOrbitalMagneticMoment( const Double_t& anOrbitalMagneticMoment );
            */

        private:
            void DoNothing() const;
            void RecalculateMagneticField() const;
            void RecalculateElectricField() const;
            void RecalculateElectricPotential() const;

            mutable void (KTrackExactParticle::*fGetMagneticFieldPtr)() const;
            mutable void (KTrackExactParticle::*fGetElectricFieldPtr)() const ;
            mutable void (KTrackExactParticle::*fGetElectricPotentialPtr)() const;
    };

} /* namespace Kassiopeia */
#endif /* KTRACKEXACTPARTICLE_H_ */
