#ifndef KTRACKPARTICLE_H_
#define KTRACKPARTICLE_H_

#include "KSParticle.h"

#include "KSMagneticField.h"
#include "KSElectricField.h"

#include "TVector3.h"

namespace Kassiopeia
{

    class KTrackParticle
    {
        public:
            KTrackParticle();
            virtual ~KTrackParticle();

            //*************
            //configuration
            //*************

        public:
            virtual void Reset() = 0;
            void SetData( Double_t* aBlock );
            void SetParticle( KSParticle* aParticle );
            void SetMagneticFieldCalculator( KSMagneticField* aCalculator );
            void SetElectricFieldCalculator( KSElectricField* aCalculator );

        protected:
            Double_t* fData;
            KSParticle* fParticle;
            KSMagneticField* fMagneticFieldCalculator;
            KSElectricField* fElectricFieldCalculator;

            //*******
            //actions
            //*******

        public:
            virtual void PullUpdate() = 0;
            virtual void PushUpdate() const = 0;

            //****************
            //static variables
            //****************

        public:
            static const Double_t& GetMass();
            static const Double_t& GetCharge();

            static void SetMass( const Double_t& aMass );
            static void SetCharge( const Double_t& aCharge );

        protected:
            static Double_t fMass;
            static Double_t fCharge;

            //*****************
            //dynamic variables
            //*****************

        public:
            //getters
            virtual const Double_t& GetTime() const = 0;
            virtual const TVector3& GetPosition() const = 0;
            virtual const TVector3& GetMomentum() const = 0;
            virtual const TVector3& GetVelocity() const = 0;
            virtual const Double_t& GetLorentzFactor() const = 0;
            virtual const Double_t& GetKineticEnergy() const = 0;

            virtual const TVector3& GetMagneticField() const = 0;
            virtual const TVector3& GetElectricField() const = 0;
            virtual const Double_t& GetElectricPotential() const = 0;
            virtual const Double_t& GetGradientB( const TVector3& ) const = 0;
            virtual const Double_t& GetGradientE( const TVector3& ) const = 0;

            virtual const Double_t& GetLongMomentum() const = 0;
            virtual const Double_t& GetTransMomentum() const = 0;
            virtual const Double_t& GetLongVelocity() const = 0;
            virtual const Double_t& GetTransVelocity() const = 0;
            virtual const Double_t& GetCyclotronFrequency() const = 0;
            virtual const Double_t& GetOrbitalMagneticMoment() const = 0;

            //setters
            /*
            virtual void SetTime( const Double_t& aTime ) = 0;
            virtual void SetPosition( const TVector3& aPosition ) = 0;
            virtual void SetMomentum( const TVector3& aMomentum ) = 0;
            virtual void SetVelocity( const TVector3& aVelocity ) = 0;
            virtual void SetLorentzFactor( const Double_t& aLorentzFactor ) = 0;
            virtual void SetKineticEnergy( const Double_t& aKineticEnergy ) = 0;

            virtual void SetLongMomentum( const Double_t& aLongMomentum ) = 0;
            virtual void SetTransMomentum( const Double_t& aTransMomentum ) = 0;
            virtual void SetLongVelocity( const Double_t& aLongVelocity ) = 0;
            virtual void SetTransVelocity( const Double_t& aTransVelocity ) = 0;
            virtual void SetCyclotronFrequency( const Double_t& aCyclotronFrequency ) = 0;
            virtual void SetOrbitalMagneticMoment( const Double_t& anOrbitalMagneticMoment ) = 0;
            */

        protected:
            mutable Double_t fTime;
            mutable TVector3 fPosition;
            mutable TVector3 fMomentum;
            mutable TVector3 fVelocity;
            mutable Double_t fLorentzFactor;
            mutable Double_t fKineticEnergy;

            mutable TVector3 fMagneticField;
            mutable TVector3 fElectricField;
            mutable Double_t fElectricPotential;
            mutable Double_t fGradientB;
            mutable Double_t fGradientE;

            mutable Double_t fLongMomentum;
            mutable Double_t fTransMomentum;
            mutable Double_t fLongVelocity;
            mutable Double_t fTransVelocity;
            mutable Double_t fCyclotronFrequency;
            mutable Double_t fOrbitalMagneticMoment;
    };

    inline void KTrackParticle::SetParticle( KSParticle* aParticle )
    {
        fParticle = aParticle;
        Reset();
        return;
    }
    inline void KTrackParticle::SetData( Double_t* aBlock )
    {
        fData = aBlock;
        Reset();
        return;
    }
    inline void KTrackParticle::SetMagneticFieldCalculator( KSMagneticField* aCalculator )
    {
        fMagneticFieldCalculator = aCalculator;
        Reset();
        return;
    }
    inline void KTrackParticle::SetElectricFieldCalculator( KSElectricField* aCalculator )
    {
        fElectricFieldCalculator = aCalculator;
        Reset();
        return;
    }

    inline const Double_t& KTrackParticle::GetMass()
    {
        return fMass;
    }
    inline const Double_t& KTrackParticle::GetCharge()
    {
        return fCharge;
    }
    inline void KTrackParticle::SetMass( const Double_t& aMass )
    {
        fMass = aMass;
        return;
    }
    inline void KTrackParticle::SetCharge( const Double_t& aCharge )
    {
        fCharge = aCharge;
        return;
    }

} /* namespace Kassiopeia */

#endif /* KTRACKPARTICLE_H_ */
