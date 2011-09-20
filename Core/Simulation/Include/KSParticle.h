#ifndef KSPARTICLE_H_
#define KSPARTICLE_H_

#include "KSConst.h"

#ifdef DEBUG_VERBOSE
#include "KSMessage.h"
#endif

#include "TVector3.h"
#include "TMath.h"

//basic variables:
//
//fPosition
//fMomentum

namespace Kassiopeia
{
    class KSParticleFactory;

    class KSMagneticField;
    class KSElectricField;

    class KSParticle
    {
        public:
            friend class KSParticleFactory;

            //******************************************
            //particle construction and cache management
            //******************************************

        public:
            KSParticle( const KSParticle* aParticleToClone );
            ~KSParticle();

        protected:
            KSParticle();

        public:
            void PullFrom( const KSParticle* aParticleToCopyFrom );
            void PushTo( KSParticle* aParticleToCopyTo ) const;

            void ClearCache() const;
            void DoNothing() const;
            void Print() const;

            //***********
            //calculators
            //***********

        public:
            void SetMagneticFieldCalculator( KSMagneticField* const );
            void SetElectricFieldCalculator( KSElectricField* const );

        protected:
            KSMagneticField* fMagneticFieldCalculator;
            KSElectricField* fElectricFieldCalculator;

            //*****************
            //static properties
            //*****************

        public:
            const Long_t& GetPID() const;
            const Double_t& GetMass() const;
            const Double_t& GetCharge() const;
            const Double_t& GetTotalSpin() const;
            const Double_t& GetLifetime() const;

        protected:
            const Long_t* fPID;
            const Double_t* fMass;
            const Double_t* fCharge;
            const Double_t* fTotalSpin;
            const Double_t* fLifetime;

            //******************
            //dynamic properties
            //******************

        public:

            //time (units are seconds)

            const Double_t& GetT() const;

            void SetT( const Double_t t );

            //position (units are meters)

            const TVector3& GetPosition() const;
            Double_t GetX() const;
            Double_t GetY() const;
            Double_t GetZ() const;

            void SetPosition( const TVector3& position );
            void SetPosition( const Double_t& x, const Double_t& y, const Double_t& z );
            void SetX( const Double_t& x );
            void SetY( const Double_t& y );
            void SetZ( const Double_t& z );

            void RecalculatePosition() const;

            //momentum (units are kg*m/s)

            const TVector3& GetMomentum() const;
            Double_t GetPX() const;
            Double_t GetPY() const;
            Double_t GetPZ() const;

            void SetMomentum( const TVector3& momentum );
            void SetMomentum( const Double_t& px, const Double_t& py, const Double_t& pz );
            void SetPX( const Double_t& px );
            void SetPY( const Double_t& py );
            void SetPZ( const Double_t& pz );

            void RecalculateMomentum() const;

            //velocity (units are m/s)

            const TVector3& GetVelocity() const;

            void SetVelocity( const TVector3& velocity );

            void RecalculateVelocity() const;

            //speed (units are m/s)

            const Double_t& GetSpeed() const;

            void SetSpeed( const Double_t& speed );

            void RecalculateSpeed() const;

            // lorentz factor (unitless)

            const Double_t& GetLorentzFactor() const;

            void SetLorentzFactor( const Double_t& lorentzfactor );

            void RecalculateLorentzFactor() const;

            //kinetic energy (units are eV)

            const Double_t& GetKineticEnergy() const;

            void SetKineticEnergy( const Double_t& energy );

            void RecalculateKineticEnergy() const;

            //polar angle of momentum vector (units are degrees)

            const Double_t& GetPolarAngleToZ() const;

            void SetPolarAngleToZ( const Double_t& NewPolarAngleToZ );

            void RecalculatePolarAngleToZ() const;

            //azimuthal angle of momentum vector (units are degrees)

            const Double_t& GetAzimuthalAngleToX() const;

            void SetAzimuthalAngleToX( const Double_t& NewAzimuthalAngleToX );

            void RecalculateAzimuthalAngleToX() const;

        protected:
            mutable Double_t fTime;
            mutable TVector3 fPosition;
            mutable TVector3 fMomentum;
            mutable TVector3 fVelocity;
            mutable Double_t fLorentzFactor;
            mutable Double_t fSpeed;
            mutable Double_t fKineticEnergy;
            mutable Double_t fPolarAngleToZ;
            mutable Double_t fAzimuthalAngleToX;

        protected:
            mutable void (KSParticle::*fGetPositionAction)() const;
            mutable void (KSParticle::*fGetMomentumAction)() const;
            mutable void (KSParticle::*fGetVelocityAction)() const;
            mutable void (KSParticle::*fGetLorentzFactorAction)() const;
            mutable void (KSParticle::*fGetSpeedAction)() const;
            mutable void (KSParticle::*fGetKineticEnergyAction)() const;
            mutable void (KSParticle::*fGetPolarAngleToZAction)() const;
            mutable void (KSParticle::*fGetAzimuthalAngleToXAction)() const;

            //********************************
            //electromagnetic field properties
            //********************************

        public:

            //magnetic field (units are tesla)

            const TVector3& GetMagneticField() const;

            void SetMagneticField( const TVector3& );

            void RecalculateMagneticField() const;

            //electric field (units are volt/meter)

            const TVector3& GetElectricField() const;

            void SetElectricField( const TVector3& );

            void RecalculateElectricField() const;

            //electric potential (units are volt)

            const Double_t& GetElectricPotential() const;

            void SetElectricPotential( const Double_t& );

            void RecalculateElectricPotential() const;

            //gradient of magnetic field (units are tesla/meter)

            const Double_t& GetGradientB( const TVector3& ) const;

            void SetGradientB( const Double_t& );

            void RecalculateGradientB() const;

            //gradient of electric field (units are volt/meter^2)

            const Double_t& GetGradientE( const TVector3& ) const;

            void SetGradientE( const Double_t& );

            void RecalculateGradientE() const;

        protected:
            mutable TVector3 fMagneticField;
            mutable TVector3 fElectricField;
            mutable Double_t fElectricPotential;
            mutable Double_t fGradientB;
            mutable Double_t fGradientE;

        protected:
            mutable void (KSParticle::*fGetMagneticFieldAction)() const;
            mutable void (KSParticle::*fGetElectricFieldAction)() const;
            mutable void (KSParticle::*fGetElectricPotentialAction)() const;
            mutable void (KSParticle::*fGetGradientBAction)() const;
            mutable void (KSParticle::*fGetGradientEAction)() const;

            //**********************************
            //electromagnetic dynamic properties
            //**********************************

        public:

            //longitudinal momentum (units are kg*m/s)

            const Double_t& GetLongMomentum() const;

            void SetLongMomentum( const Double_t& );

            void RecalculateLongMomentum() const;

            //transverse momentum (units are kg*m/s)

            const Double_t& GetTransMomentum() const;

            void SetTransMomentum( const Double_t& );

            void RecalculateTransMomentum() const;

            //longitudinal velocity (units are m/s)

            const Double_t& GetLongVelocity() const;

            void SetLongVelocity( const Double_t& );

            void RecalculateLongVelocity() const;

            //transverse velocity (units are m/s)

            const Double_t& GetTransVelocity() const;

            void SetTransVelocity( const Double_t& );

            void RecalculateTransVelocity() const;

            //polar angle to b (units are degrees)

            const Double_t& GetPolarAngleToB() const;

            void SetPolarAngleToB( const Double_t& );

            void RecalculatePolarAngleToB() const;

            //cyclotron frequency (units are 1/s)

            const Double_t& GetCyclotronFrequency() const;

            void SetCyclotronFrequency( const Double_t& );

            void RecalculateCyclotronFrequency() const;

            //orbital magnetic moment (units are A*m^2)

            const Double_t& GetOrbitalMagneticMoment() const;

            void SetOrbitalMagneticMoment( const Double_t& );

            void RecalculateOrbitalMagneticMoment() const;

        protected:
            mutable Double_t fLongMomentum;
            mutable Double_t fTransMomentum;
            mutable Double_t fLongVelocity;
            mutable Double_t fTransVelocity;
            mutable Double_t fPolarAngleToB;
            mutable Double_t fCyclotronFrequency;
            mutable Double_t fOrbitalMagneticMoment;
            mutable TVector3 fGuidingCenterPosition;

        protected:
            mutable void (KSParticle::*fGetLongMomentumAction)() const;
            mutable void (KSParticle::*fGetTransMomentumAction)() const;
            mutable void (KSParticle::*fGetLongVelocityAction)() const;
            mutable void (KSParticle::*fGetTransVelocityAction)() const;
            mutable void (KSParticle::*fGetPolarAngleToBAction)() const;
            mutable void (KSParticle::*fGetCyclotronFrequencyAction)() const;
            mutable void (KSParticle::*fGetOrbitalMagneticMomentAction)() const;
            mutable void (KSParticle::*fGetGCPositionAction)() const;
    };

    //***********
    //calculators
    //***********

    inline void KSParticle::SetMagneticFieldCalculator( KSMagneticField* const aMagFieldCalculator )
    {
        fMagneticFieldCalculator = aMagFieldCalculator;
        return;
    }
    inline void KSParticle::SetElectricFieldCalculator( KSElectricField* const anElFieldCalculator )
    {
        fElectricFieldCalculator = anElFieldCalculator;
        return;
    }

}

#endif
