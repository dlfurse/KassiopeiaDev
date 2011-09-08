#ifndef KSEMPARTICLE_H_
#define KSEMPARTICLE_H_

#include "KSBasicParticle.h"

#include "KSElectricField.h"
#include "KSMagneticField.h"

//basic variables:
//
//fPosition
//fMomentum

namespace Kassiopeia
{

    class KSElectromagneticParticle :
        public KSBasicParticle
    {
        public:
            friend class KSParticleFactory;

            //*********************
            //particle construction
            //*********************

        public:
            KSElectromagneticParticle( const KSElectromagneticParticle* aParticleToClone );
            virtual ~KSElectromagneticParticle();

        protected:
            KSElectromagneticParticle();

            virtual void EnableAllVariables() const;
            virtual void DisableBasicVariables() const;

            //***************
            //printing system
            //***************

        public:
            virtual void Print() const;

            //*********************************
            //electromagnetic properties system
            //*********************************

        public:

            //electromagnetic field calculators

            void SetMagneticFieldCalculator( KSMagneticField* const );
            void SetElectricFieldCalculator( KSElectricField* const );

            //position (units are in meters)

            virtual void SetPosition( const TVector3& );
            virtual void SetPosition( const Double_t&, const Double_t&, const Double_t& );
            virtual void SetX( const Double_t& );
            virtual void SetY( const Double_t& );
            virtual void SetZ( const Double_t& );

            //momentum (units are kg*m/s)

            virtual void SetMomentum( const TVector3& );
            virtual void SetMomentum( const Double_t&, const Double_t&, const Double_t& );
            virtual void SetPX( const Double_t& );
            virtual void SetPY( const Double_t& );
            virtual void SetPZ( const Double_t& );

            //velocity (units are m/s)

            virtual void SetVelocity( const TVector3& velocity );

            //speed (units are m/s)

            virtual void SetSpeed( const Double_t& speed );

            // lorentz factor (unitless)

            virtual void SetLorentzFactor( const Double_t& lorentzfactor );

            //kinetic energy (units are eV)

            virtual void SetKineticEnergy( const Double_t& energy );

            //polar angle of momentum vector (units are degrees)

            virtual void SetPolarAngleToZ( const Double_t& theta );

            //azimuthal angle of momentum vector (units are degrees)

            virtual void SetAzimuthalAngleToX( const Double_t& phi );

            //magnetic field (units are tesla)

            const TVector3& GetMagneticField() const;

            virtual void SetMagneticField( const TVector3& );

            virtual void RecalculateMagneticField() const;

            //electric field (units are volt/meter)

            const TVector3& GetElectricField() const;

            virtual void SetElectricField( const TVector3& );

            virtual void RecalculateElectricField() const;

            //electric potential (units are volt)

            const Double_t& GetElectricPotential() const;

            virtual void SetElectricPotential( const Double_t& );

            virtual void RecalculateElectricPotential() const;

            //gradient of magnetic field (units are tesla/meter)

            const Double_t& GetGradientB( const TVector3& ) const;

            virtual void SetGradientB( const Double_t& );

            virtual void RecalculateGradientB() const;

            //gradient of electric field (units are volt/meter^2)

            const Double_t& GetGradientE( const TVector3& ) const;

            virtual void SetGradientE( const Double_t& );

            virtual void RecalculateGradientE() const;

            //longitudinal momentum (units are kg*m/s)

            const Double_t& GetLongMomentum() const;

            virtual void SetLongMomentum( const Double_t& );

            virtual void RecalculateLongMomentum() const;

            //transverse momentum (units are kg*m/s)

            const Double_t& GetTransMomentum() const;

            virtual void SetTransMomentum( const Double_t& );

            virtual void RecalculateTransMomentum() const;

            //longitudinal velocity (units are m/s)

            const Double_t& GetLongVelocity() const;

            virtual void SetLongVelocity( const Double_t& );

            virtual void RecalculateLongVelocity() const;

            //transverse velocity (units are m/s)

            const Double_t& GetTransVelocity() const;

            virtual void SetTransVelocity( const Double_t& );

            virtual void RecalculateTransVelocity() const;

            //polar angle to b (units are degrees)

            const Double_t& GetPolarAngleToB() const;

            virtual void SetPolarAngleToB( const Double_t& );

            virtual void RecalculatePolarAngleToB() const;

            //cyclotron frequency (units are 1/s)

            const Double_t& GetCyclotronFrequency() const;

            virtual void SetCyclotronFrequency( const Double_t& );

            virtual void RecalculateCyclotronFrequency() const;

            //orbital magnetic moment (units are A*m^2)

            const Double_t& GetOrbitalMagneticMoment() const;

            virtual void SetOrbitalMagneticMoment( const Double_t& );

            virtual void RecalculateOrbitalMagneticMoment() const;

        public:

            //*******************
            //actual data members
            //*******************

        protected:
            //em field calculators
            KSMagneticField* fMagneticFieldCalculator;
            KSElectricField* fElectricFieldCalculator;

            //em field variables
            mutable TVector3 fMagneticField;
            mutable TVector3 fElectricField;
            mutable Double_t fElectricPotential;
            mutable Double_t fGradientB;
            mutable Double_t fGradientE;

            //em particle variables
            mutable Double_t fLongMomentum;
            mutable Double_t fTransMomentum;
            mutable Double_t fLongVelocity;
            mutable Double_t fTransVelocity;
            mutable Double_t fPolarAngleToB;
            mutable Double_t fCyclotronFrequency;
            mutable Double_t fOrbitalMagneticMoment;
            mutable TVector3 fGuidingCenterPosition;

            //*******************************
            //recalculation function pointers
            //*******************************

        protected:
            //recalculation function pointers for em field variables
            mutable void (KSElectromagneticParticle::*fGetMagneticFieldAction)() const;
            mutable void (KSElectromagneticParticle::*fGetElectricFieldAction)() const;
            mutable void (KSElectromagneticParticle::*fGetElectricPotentialAction)() const;
            mutable void (KSElectromagneticParticle::*fGetGradientBAction)() const;
            mutable void (KSElectromagneticParticle::*fGetGradientEAction)() const;

            //recalculation function pointers for em particle variables
            mutable void (KSElectromagneticParticle::*fGetLongMomentumAction)() const;
            mutable void (KSElectromagneticParticle::*fGetTransMomentumAction)() const;
            mutable void (KSElectromagneticParticle::*fGetLongVelocityAction)() const;
            mutable void (KSElectromagneticParticle::*fGetTransVelocityAction)() const;
            mutable void (KSElectromagneticParticle::*fGetPolarAngleToBAction)() const;
            mutable void (KSElectromagneticParticle::*fGetCyclotronFrequencyAction)() const;
            mutable void (KSElectromagneticParticle::*fGetOrbitalMagneticMomentAction)() const;
            mutable void (KSElectromagneticParticle::*fGetGCPositionAction)() const;
    };

    //***********************************************
    //electric and magnetic field setters and getters
    //***********************************************

    inline void KSElectromagneticParticle::SetMagneticFieldCalculator( KSMagneticField* const aMagFieldCalculator )
    {
        fMagneticFieldCalculator = aMagFieldCalculator;
        return;
    }
    inline void KSElectromagneticParticle::SetElectricFieldCalculator( KSElectricField* const anElFieldCalculator )
    {
        fElectricFieldCalculator = anElFieldCalculator;
        return;
    }

    //********
    //position
    //********

    inline void KSElectromagneticParticle::SetPosition( const TVector3& aPosition )
    {
        fPosition = aPosition;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSElectromagneticParticle::SetPosition";
        msg << "KSBasicParticle: [" << this << "] setting fPosition" << ret;
        msg << "[" << fPosition.X() << ", " << fPosition.Y() << ", " << fPosition.Z() << "]" << end;
#endif

        fGetMagneticFieldAction = &KSElectromagneticParticle::RecalculateMagneticField;
        fGetElectricFieldAction = &KSElectromagneticParticle::RecalculateElectricField;
        fGetElectricPotentialAction = &KSElectromagneticParticle::RecalculateElectricPotential;

        fGetLongMomentumAction = &KSElectromagneticParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSElectromagneticParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSElectromagneticParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;

        return;
    }
    inline void KSElectromagneticParticle::SetPosition( const Double_t& anX, const Double_t& aY, const Double_t& aZ )
    {
        fPosition.SetXYZ( anX, aY, aZ );

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSElectromagneticParticle::SetPosition";
        msg << "KSBasicParticle: [" << this << "] setting fPosition" << ret;
        msg << "[" << fPosition.X() << ", " << fPosition.Y() << ", " << fPosition.Z() << "]" << end;
#endif

        fGetMagneticFieldAction = &KSElectromagneticParticle::RecalculateMagneticField;
        fGetElectricFieldAction = &KSElectromagneticParticle::RecalculateElectricField;
        fGetElectricPotentialAction = &KSElectromagneticParticle::RecalculateElectricPotential;

        fGetLongMomentumAction = &KSElectromagneticParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSElectromagneticParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSElectromagneticParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;

        return;
    }
    inline void KSElectromagneticParticle::SetX( const Double_t& anX )
    {
        fPosition.SetX( anX );

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSElectromagneticParticle::SetPosition";
        msg << "KSBasicParticle: [" << this << "] setting fPosition" << ret;
        msg << "[" << fPosition.X() << ", " << fPosition.Y() << ", " << fPosition.Z() << "]" << end;
#endif

        fGetMagneticFieldAction = &KSElectromagneticParticle::RecalculateMagneticField;
        fGetElectricFieldAction = &KSElectromagneticParticle::RecalculateElectricField;
        fGetElectricPotentialAction = &KSElectromagneticParticle::RecalculateElectricPotential;

        fGetLongMomentumAction = &KSElectromagneticParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSElectromagneticParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSElectromagneticParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;

        return;
    }
    inline void KSElectromagneticParticle::SetY( const Double_t& aY )
    {
        fPosition.SetY( aY );

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSElectromagneticParticle::SetPosition";
        msg << "KSBasicParticle: [" << this << "] setting fPosition" << ret;
        msg << "[" << fPosition.X() << ", " << fPosition.Y() << ", " << fPosition.Z() << "]" << end;
#endif

        fGetMagneticFieldAction = &KSElectromagneticParticle::RecalculateMagneticField;
        fGetElectricFieldAction = &KSElectromagneticParticle::RecalculateElectricField;
        fGetElectricPotentialAction = &KSElectromagneticParticle::RecalculateElectricPotential;

        fGetLongMomentumAction = &KSElectromagneticParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSElectromagneticParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSElectromagneticParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;
        return;
    }
    inline void KSElectromagneticParticle::SetZ( const Double_t& aZ )
    {
        fPosition.SetZ( aZ );

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSElectromagneticParticle::SetPosition";
        msg << "KSBasicParticle: [" << this << "] setting fPosition" << ret;
        msg << "[" << fPosition.X() << ", " << fPosition.Y() << ", " << fPosition.Z() << "]" << end;
#endif

        fGetMagneticFieldAction = &KSElectromagneticParticle::RecalculateMagneticField;
        fGetElectricFieldAction = &KSElectromagneticParticle::RecalculateElectricField;
        fGetElectricPotentialAction = &KSElectromagneticParticle::RecalculateElectricPotential;

        fGetLongMomentumAction = &KSElectromagneticParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSElectromagneticParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSElectromagneticParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;

        return;
    }

    //********
    //momentum
    //********

    inline void KSElectromagneticParticle::SetMomentum( const TVector3& aMomentum )
    {
        fMomentum = aMomentum;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSEMParticle::SetMomentum";
        msg << "KSEMParticle: [" << this << "] setting fMomentum" << ret;
        msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << end;
#endif

        fGetVelocityAction = &KSElectromagneticParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSElectromagneticParticle::RecalculateLorentzFactor;
        fGetSpeedAction = &KSElectromagneticParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSElectromagneticParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSElectromagneticParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSElectromagneticParticle::RecalculateAzimuthalAngleToX;

        fGetLongMomentumAction = &KSElectromagneticParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSElectromagneticParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSElectromagneticParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;

        return;
    }
    inline void KSElectromagneticParticle::SetMomentum( const Double_t& anX, const Double_t& aY, const Double_t& aZ )
    {
        fMomentum.SetXYZ( anX, aY, aZ );

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSEMParticle::SetMomentum";
        msg << "KSEMParticle: [" << this << "] setting fMomentum" << ret;
        msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << end;
#endif

        fGetVelocityAction = &KSElectromagneticParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSElectromagneticParticle::RecalculateLorentzFactor;
        fGetSpeedAction = &KSElectromagneticParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSElectromagneticParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSElectromagneticParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSElectromagneticParticle::RecalculateAzimuthalAngleToX;

        fGetLongMomentumAction = &KSElectromagneticParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSElectromagneticParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSElectromagneticParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;

        return;
    }
    inline void KSElectromagneticParticle::SetPX( const Double_t& anX )
    {
        fMomentum.SetX( anX );

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSEMParticle::SetMomentum";
        msg << "KSEMParticle: [" << this << "] setting fMomentum" << ret;
        msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << end;
#endif

        fGetVelocityAction = &KSElectromagneticParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSElectromagneticParticle::RecalculateLorentzFactor;
        fGetSpeedAction = &KSElectromagneticParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSElectromagneticParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSElectromagneticParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSElectromagneticParticle::RecalculateAzimuthalAngleToX;

        fGetLongMomentumAction = &KSElectromagneticParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSElectromagneticParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSElectromagneticParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;

        return;
    }
    inline void KSElectromagneticParticle::SetPY( const Double_t& aY )
    {
        fMomentum.SetY( aY );

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSEMParticle::SetMomentum";
        msg << "KSEMParticle: [" << this << "] setting fMomentum" << ret;
        msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << end;
#endif

        fGetVelocityAction = &KSElectromagneticParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSElectromagneticParticle::RecalculateLorentzFactor;
        fGetSpeedAction = &KSElectromagneticParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSElectromagneticParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSElectromagneticParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSElectromagneticParticle::RecalculateAzimuthalAngleToX;

        fGetLongMomentumAction = &KSElectromagneticParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSElectromagneticParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSElectromagneticParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;

        return;
    }
    inline void KSElectromagneticParticle::SetPZ( const Double_t& aZ )
    {
        fMomentum.SetZ( aZ );

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSEMParticle::SetMomentum";
        msg << "KSEMParticle: [" << this << "] setting fMomentum" << ret;
        msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << end;
#endif

        fGetVelocityAction = &KSElectromagneticParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSElectromagneticParticle::RecalculateLorentzFactor;
        fGetSpeedAction = &KSElectromagneticParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSElectromagneticParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSElectromagneticParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSElectromagneticParticle::RecalculateAzimuthalAngleToX;

        fGetLongMomentumAction = &KSElectromagneticParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSElectromagneticParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSElectromagneticParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;

        return;
    }

    //********
    //velocity
    //********

    inline void KSElectromagneticParticle::SetVelocity( const TVector3& NewVelocity )
    {
        register Double_t Speed = NewVelocity.Mag();
        register Double_t LorentzFactor = 1.0 / TMath::Sqrt( 1.0 - (Speed * Speed / (KSConst::C() * KSConst::C())) );

        fMomentum = GetMass() * LorentzFactor * NewVelocity;
        fVelocity = NewVelocity;
        fLorentzFactor = LorentzFactor;
        fSpeed = Speed;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSEMParticle::SetVelocity";
        msg << "KSEMParticle: [" << this << "] setting fVelocity" << ret;
        msg << "[" << fVelocity.X() << ", " << fVelocity.Y() << ", " << fVelocity.Z() << "]" << ret;
        msg << "KSEMParticle: [" << this << "] fMomentum has been recalculated" << ret;
        msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << ret;
        msg << "KSEMParticle: [" << this << "] fLorentzFactor and fSpeed have been secondarily recalculated" << ret;
        msg << "[" << fLorentzFactor << "]" << ret;
        msg << "[" << fSpeed << "]" << end;
#endif

        fGetVelocityAction = &KSElectromagneticParticle::DoNothing;
        fGetLorentzFactorAction = &KSElectromagneticParticle::DoNothing;
        fGetSpeedAction = &KSElectromagneticParticle::DoNothing;
        fGetKineticEnergyAction = &KSElectromagneticParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSElectromagneticParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSElectromagneticParticle::RecalculateAzimuthalAngleToX;

        fGetLongMomentumAction = &KSElectromagneticParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSElectromagneticParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSElectromagneticParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;

        return;
    }

    //*****
    //speed
    //*****

    inline void KSElectromagneticParticle::SetSpeed( const Double_t& NewSpeed )
    {
        register Double_t LorentzFactor = 1.0 / TMath::Sqrt( 1.0 - NewSpeed * NewSpeed / (KSConst::C() * KSConst::C()) );
        register Double_t MomentumMagnitude = GetMass() * KSConst::C() * TMath::Sqrt( LorentzFactor * LorentzFactor - 1.0 );

        fMomentum.SetMag( MomentumMagnitude );
        fLorentzFactor = LorentzFactor;
        fSpeed = NewSpeed;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSEMParticle::SetSpeed";
        msg << "KSEMParticle: [" << this << "] setting fSpeed" << ret;
        msg << "[" << fSpeed << "]" << ret;
        msg << "KSEMParticle: [" << this << "] fMomentum has been recalculated" << ret;
        msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << ret;
        msg << "KSEMParticle: [" << this << "] fLorentzFactor has been secondarily recalculated" << ret;
        msg << "[" << fLorentzFactor << "]" << end;
#endif

        fGetVelocityAction = &KSElectromagneticParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSElectromagneticParticle::DoNothing;
        fGetSpeedAction = &KSElectromagneticParticle::DoNothing;
        fGetKineticEnergyAction = &KSElectromagneticParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSElectromagneticParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSElectromagneticParticle::RecalculateAzimuthalAngleToX;

        fGetLongMomentumAction = &KSElectromagneticParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSElectromagneticParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSElectromagneticParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;

        return;
    }

    //**************
    //lorentz factor
    //**************

    inline void KSElectromagneticParticle::SetLorentzFactor( const Double_t& NewLorentzFactor )
    {
        register Double_t MomentumMagnitude = GetMass() * KSConst::C() * TMath::Sqrt( NewLorentzFactor * NewLorentzFactor - 1.0 );

        fMomentum.SetMag( MomentumMagnitude );
        fLorentzFactor = NewLorentzFactor;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSEMParticle::SetLorentzFactor";
        msg << "KSEMParticle: [" << this << "] setting fLorentzFactor" << ret;
        msg << "[" << fLorentzFactor << "]" << ret;
        msg << "KSEMParticle: [" << this << "] fMomentum has been recalculated" << ret;
        msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << end;
#endif

        fGetVelocityAction = &KSElectromagneticParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSElectromagneticParticle::DoNothing;
        fGetSpeedAction = &KSElectromagneticParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSElectromagneticParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSElectromagneticParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSElectromagneticParticle::RecalculateAzimuthalAngleToX;

        fGetLongMomentumAction = &KSElectromagneticParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSElectromagneticParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSElectromagneticParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;

        return;
    }

    //**************
    //kinetic energy
    //**************

    inline void KSElectromagneticParticle::SetKineticEnergy( const Double_t& NewKineticEnergy )
    {
        register Double_t NewKineticEnergy_SI = NewKineticEnergy * KSConst::Q();
        register Double_t MomentumMagnitude = (NewKineticEnergy_SI / KSConst::C()) * TMath::Sqrt( 1.0 + (2.0 * GetMass() * KSConst::C() * KSConst::C()) / NewKineticEnergy_SI );

        fMomentum.SetMag( MomentumMagnitude );
        fKineticEnergy = NewKineticEnergy;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSEMParticle::SetKineticEnergy";
        msg << "KSEMParticle: [" << this << "] setting fKineticEnergy" << ret;
        msg << "[" << fKineticEnergy << "]" << ret;
        msg << "KSEMParticle: [" << this << "] fMomentum has been recalculated" << ret;
        msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << end;
#endif

        fGetVelocityAction = &KSElectromagneticParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSElectromagneticParticle::RecalculateLorentzFactor;
        fGetSpeedAction = &KSElectromagneticParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSElectromagneticParticle::DoNothing;
        fGetPolarAngleToZAction = &KSElectromagneticParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSElectromagneticParticle::RecalculateAzimuthalAngleToX;

        fGetLongMomentumAction = &KSElectromagneticParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSElectromagneticParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSElectromagneticParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;

        return;
    }

    //****************
    //polar angle to z
    //****************

    inline void KSElectromagneticParticle::SetPolarAngleToZ( const Double_t& NewPolarAngleToZ )
    {
        register Double_t MomentumMagnitude = fMomentum.Mag();
        register Double_t NewPolarAngleToZ_SI = NewPolarAngleToZ / 180. * KSConst::Pi();

        fMomentum.SetXYZ( MomentumMagnitude * TMath::Sin( NewPolarAngleToZ_SI ) * TMath::Cos( GetAzimuthalAngleToX() ), MomentumMagnitude * TMath::Sin( NewPolarAngleToZ_SI ) * TMath::Sin( GetAzimuthalAngleToX() ), MomentumMagnitude * TMath::Cos( NewPolarAngleToZ_SI ) );
        fPolarAngleToZ = NewPolarAngleToZ;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSEMParticle::SetPolarAngleToZ";
        msg << "KSEMParticle: [" << this << "] setting fPolarAngleToZ" << ret;
        msg << "[" << fPolarAngleToZ << "]" << end;
#endif

        fGetVelocityAction = &KSElectromagneticParticle::RecalculateVelocity;
        //fGetLorentzFactorAction unchanged
        //fGetSpeedAction unchanged
        //fGetKineticEnergyAction unchanged
        fGetPolarAngleToZAction = &KSElectromagneticParticle::DoNothing;
        //fGetAzimuthalAngleToXAction unchanged

        fGetLongMomentumAction = &KSElectromagneticParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSElectromagneticParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSElectromagneticParticle::RecalculatePolarAngleToB;
        //fGetCyclotronFrequencyAction unchanged
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;

        return;
    }

    //********************
    //azimuthal angle to x
    //********************

    inline void KSElectromagneticParticle::SetAzimuthalAngleToX( const Double_t& NewAzimuthalAngleToX )
    {
        register Double_t NewAzimuthalAngleToX_SI = (KSConst::Pi() / 180.) * NewAzimuthalAngleToX;
        register Double_t PolarAngleToZ_SI = (KSConst::Pi() / 180.) * GetPolarAngleToZ();
        register Double_t MomentumMagnitude = fMomentum.Mag();

        fMomentum.SetXYZ( MomentumMagnitude * TMath::Sin( PolarAngleToZ_SI ) * TMath::Cos( NewAzimuthalAngleToX_SI ), MomentumMagnitude * TMath::Sin( PolarAngleToZ_SI ) * TMath::Sin( NewAzimuthalAngleToX_SI ), MomentumMagnitude * TMath::Cos( PolarAngleToZ_SI ) );
        fAzimuthalAngleToX = NewAzimuthalAngleToX;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSEMParticle::SetAzimuthalAngleToX";
        msg << "KSEMParticle: [" << this << "] setting fAzimuthalAngleToX" << ret;
        msg << "[" << fAzimuthalAngleToX << "]" << end;
#endif

        fGetVelocityAction = &KSElectromagneticParticle::RecalculateVelocity;
        //fGetLorentzFactorAction unchanged
        //fGetSpeedAction unchanged
        //fGetKineticEnergyAction unchanged
        //fGetPolarAngleToZAction unchanged
        fGetAzimuthalAngleToXAction = &KSElectromagneticParticle::DoNothing;

        fGetLongMomentumAction = &KSElectromagneticParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSElectromagneticParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSElectromagneticParticle::RecalculatePolarAngleToB;
        //fGetCyclotronFrequencyAction unchanged
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;

        return;
    }

    //**************
    //magnetic field
    //**************

    inline const TVector3& KSElectromagneticParticle::GetMagneticField() const
    {
        (this->*fGetMagneticFieldAction)();
        return fMagneticField;
    }

    inline void KSElectromagneticParticle::SetMagneticField( const TVector3& aMagneticField )
    {
        fMagneticField = aMagneticField;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSElectromagneticParticle::SetMagneticField";
        msg << "KSElectromagneticParticle: [" << this << "] setting fMagneticField" << ret;
        msg << "[" << fMagneticField.X() << ", " << fMagneticField.Y() << ", " << fMagneticField.Z() << "]" << end;
#endif

        fGetMagneticFieldAction = &KSElectromagneticParticle::DoNothing;

        return;
    }

    inline void KSElectromagneticParticle::RecalculateMagneticField() const
    {
        fMagneticFieldCalculator->GetField( fMagneticField, GetPosition(), GetT() );
        fGetMagneticFieldAction = &KSElectromagneticParticle::DoNothing;
    }

    //**************
    //electric field
    //**************

    inline const TVector3& KSElectromagneticParticle::GetElectricField() const
    {
        (this->*fGetElectricFieldAction)();
        return fElectricField;
    }
    inline void KSElectromagneticParticle::RecalculateElectricField() const
    {
        fElectricFieldCalculator->GetField( fElectricField, GetPosition(), GetT() );
        fGetElectricFieldAction = &KSElectromagneticParticle::DoNothing;
    }

    inline void KSElectromagneticParticle::SetElectricField( const TVector3& aElectricField )
    {
        fElectricField = aElectricField;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSElectromagneticParticle::SetElectricField";
        msg << "KSElectromagneticParticle: [" << this << "] setting fElectricField" << ret;
        msg << "[" << fElectricField.X() << ", " << fElectricField.Y() << ", " << fElectricField.Z() << "]" << end;
#endif

        fGetElectricFieldAction = &KSElectromagneticParticle::DoNothing;

        return;
    }

    //******************
    //electric potential
    //******************

    inline const Double_t& KSElectromagneticParticle::GetElectricPotential() const
    {
        (this->*fGetElectricPotentialAction)();
        return fElectricPotential;
    }

    inline void KSElectromagneticParticle::SetElectricPotential( const Double_t& anElectricPotential )
    {
        fElectricPotential = anElectricPotential;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSElectromagneticParticle::SetElectricPotential";
        msg << "KSElectromagneticParticle: [" << this << "] setting fElectricPotential" << ret;
        msg << "[" << fElectricPotential << "]" << end;
#endif

        fGetElectricPotentialAction = &KSElectromagneticParticle::DoNothing;

        return;
    }

    inline void KSElectromagneticParticle::RecalculateElectricPotential() const
    {
        fElectricFieldCalculator->GetPhi( fElectricPotential, GetPosition(), GetT() );
        fGetElectricPotentialAction = &KSElectromagneticParticle::DoNothing;
    }

    //***********************
    //magnetic field gradient
    //***********************

    inline const Double_t& KSElectromagneticParticle::GetGradientB( const TVector3& Direction ) const
    {
        static Double_t Epsilon = 1.0e-6;
        TVector3 BAhead;
        TVector3 BBehind;
        fMagneticFieldCalculator->GetField( BAhead, GetPosition() + Epsilon * Direction, GetT() );
        fMagneticFieldCalculator->GetField( BBehind, GetPosition() - Epsilon * Direction, GetT() );

        fGradientB = ((BAhead.Mag() - BBehind.Mag()) / (2.0 * Epsilon));

        return fGradientB;
    }

    inline void KSElectromagneticParticle::SetGradientB( const Double_t& )
    {

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSElectromagneticParticle::SetElectricPotential";
        msg << "KSElectromagneticParticle: [" << this << "] setting fElectricPotential" << ret;
        msg << "[" << fElectricPotential << "]" << end;
#endif

        return;
    }

    inline void KSElectromagneticParticle::RecalculateGradientB() const
    {
        return;
    }

    //***********************
    //electric field gradient
    //***********************

    inline const Double_t& KSElectromagneticParticle::GetGradientE( const TVector3& Direction ) const
    {
        static Double_t Epsilon = 1.0e-6;
        TVector3 EAhead;
        TVector3 EBehind;
        fElectricFieldCalculator->GetField( EAhead, GetPosition() + Epsilon * Direction, GetT() );
        fElectricFieldCalculator->GetField( EBehind, GetPosition() - Epsilon * Direction, GetT() );

        fGradientE = ((EAhead.Mag() - EBehind.Mag()) / (2.0 * Epsilon));

        return fGradientE;
    }

    inline void KSElectromagneticParticle::SetGradientE( const Double_t& )
    {
        return;
    }

    inline void KSElectromagneticParticle::RecalculateGradientE() const
    {
        return;
    }

    //*********************
    //longitudinal momentum
    //*********************

    inline void KSElectromagneticParticle::SetLongMomentum( const Double_t& aNewLongMomentum )
    {
        TVector3 LongMomentumVector = GetMagneticField();
        LongMomentumVector.SetMag( aNewLongMomentum - GetLongMomentum() );

        fMomentum += LongMomentumVector;
        fLongMomentum = aNewLongMomentum;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSEMParticle::SetLongMomentum";
        msg << "KSEMParticle: [" << this << "] setting fLongMomentum" << ret;
        msg << "[" << fLongMomentum << "]" << ret;
        msg << "KSEMParticle: [" << this << "] fMomentum has been recalculated" << ret;
        msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << end;
#endif

        fGetVelocityAction = &KSElectromagneticParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSElectromagneticParticle::RecalculateLorentzFactor;
        fGetSpeedAction = &KSElectromagneticParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSElectromagneticParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSElectromagneticParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSElectromagneticParticle::RecalculateAzimuthalAngleToX;

        fGetLongMomentumAction = &KSElectromagneticParticle::DoNothing;
        //fGetTransMomentumAction unchanged
        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSElectromagneticParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        //fGetOrbitalMagneticMomentAction unchanged

        return;
    }
    inline const Double_t& KSElectromagneticParticle::GetLongMomentum() const
    {
        (this->*fGetLongMomentumAction)();
        return fLongMomentum;
    }
    inline void KSElectromagneticParticle::RecalculateLongMomentum() const
    {
        fLongMomentum = GetMagneticField().Unit().Dot( fMomentum );

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSEMParticle::RecalculateLongMomentum";
        msg << "KSEMParticle: [" << this << "] recalculating fLongMomentum" << ret;
        msg << "[" << fLongMomentum << "]" << end;
#endif

        fGetLongMomentumAction = &KSElectromagneticParticle::DoNothing;

        return;
    }

    //*******************
    //transverse momentum
    //*******************

    inline void KSElectromagneticParticle::SetTransMomentum( const Double_t& NewTransMomentum )
    {
        TVector3 LongMomentumVector = GetLongMomentum() * GetMagneticField().Unit();
        TVector3 TransMomentumVector = fMomentum - LongMomentumVector;
        TransMomentumVector.SetMag( NewTransMomentum );

        fMomentum = LongMomentumVector + TransMomentumVector;
        fTransMomentum = NewTransMomentum;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSEMParticle::SetTransMomentum";
        msg << "KSEMParticle: [" << this << "] setting fTransMomentum" << ret;
        msg << "[" << fTransMomentum << "]" << ret;
        msg << "KSEMParticle: [" << this << "] fMomentum has been recalculated" << ret;
        msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << end;
#endif

        fGetVelocityAction = &KSElectromagneticParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSElectromagneticParticle::RecalculateLorentzFactor;
        fGetSpeedAction = &KSElectromagneticParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSElectromagneticParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSElectromagneticParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSElectromagneticParticle::RecalculateAzimuthalAngleToX;

        //fGetLongMomentumAction unchanged
        fGetTransMomentumAction = &KSElectromagneticParticle::DoNothing;
        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSElectromagneticParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;

        return;
    }
    inline const Double_t& KSElectromagneticParticle::GetTransMomentum() const
    {
        (this->*fGetTransMomentumAction)();
        return fTransMomentum;
    }
    inline void KSElectromagneticParticle::RecalculateTransMomentum() const
    {
        fTransMomentum = TMath::Sqrt( fMomentum.Mag2() - GetLongMomentum() * GetLongMomentum() );

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSEMParticle::RecalculateTransMomentum";
        msg << "KSEMParticle: [" << this << "] recalculating fTransMomentum" << ret;
        msg << "[" << fTransMomentum << "]" << end;
#endif

        fGetTransMomentumAction = &KSElectromagneticParticle::DoNothing;

        return;
    }

    //*********************************************************************************
    //longitudinal velocity
    //*********************************************************************************

    inline void KSElectromagneticParticle::SetLongVelocity( const Double_t& NewLongVelocity )
    {
        TVector3 LongVelocityVector = GetMagneticField();
        LongVelocityVector.SetMag( NewLongVelocity - GetLongVelocity() );

        fVelocity += LongVelocityVector;
        fSpeed = fVelocity.Mag();
        fLorentzFactor = 1.0 / TMath::Sqrt( 1.0 - (fSpeed * fSpeed / (KSConst::C() * KSConst::C())) );
        fMomentum = (GetMass() * fLorentzFactor) * fVelocity;
        fLongVelocity = NewLongVelocity;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSEMParticle::SetLongVelocity";
        msg << "KSEMParticle: [" << this << "] setting fLongVelocity" << ret;
        msg << "[" << fLongVelocity << "]" << ret;
        msg << "KSEMParticle: [" << this << "] fMomentum has been recalculated" << ret;
        msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << ret;
        msg << "KSEMParticle: [" << this << "] fVelocity, fLorentzFactor and fSpeed have been secondarily recalculated" << ret;
        msg << "[" << fVelocity.X() << ", " << fVelocity.Y() << ", " << fVelocity.Z() << "]" << ret;
        msg << "[" << fLorentzFactor << "]" << ret;
        msg << "[" << fSpeed << "]" << end;
#endif

        fGetVelocityAction = &KSElectromagneticParticle::DoNothing;
        fGetLorentzFactorAction = &KSElectromagneticParticle::DoNothing;
        fGetSpeedAction = &KSElectromagneticParticle::DoNothing;
        fGetKineticEnergyAction = &KSElectromagneticParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSElectromagneticParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSElectromagneticParticle::RecalculateAzimuthalAngleToX;

        fGetLongMomentumAction = &KSElectromagneticParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSElectromagneticParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSElectromagneticParticle::DoNothing;
        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSElectromagneticParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;

        return;
    }
    inline const Double_t& KSElectromagneticParticle::GetLongVelocity() const
    {
        (this->*fGetLongVelocityAction)();
        return fLongVelocity;
    }
    inline void KSElectromagneticParticle::RecalculateLongVelocity() const
    {
        fLongVelocity = GetLongMomentum() / (GetMass() * GetLorentzFactor());

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSEMParticle::RecalculateLongVelocity";
        msg << "KSEMParticle: [" << this << "] recalculating fLongVelocity" << ret;
        msg << "[" << fLongVelocity << "]" << end;
#endif

        fGetLongVelocityAction = &KSElectromagneticParticle::DoNothing;

        return;
    }

    //*******************
    //transverse velocity
    //*******************

    inline void KSElectromagneticParticle::SetTransVelocity( const Double_t& NewTransVelocity )
    {
        TVector3 TransVelocityVector = GetVelocity() - GetLongVelocity() * GetMagneticField().Unit();
        TransVelocityVector.SetMag( NewTransVelocity - GetTransVelocity() );

        fVelocity += TransVelocityVector;
        fSpeed = fVelocity.Mag();
        fLorentzFactor = 1.0 / TMath::Sqrt( 1.0 - (fSpeed * fSpeed / (KSConst::C() * KSConst::C())) );
        fMomentum = (GetMass() * fLorentzFactor) * fVelocity;
        fTransVelocity = NewTransVelocity;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSEMParticle::SetTransVelocity";
        msg << "KSEMParticle: [" << this << "] setting fTransVelocity" << ret;
        msg << "[" << fTransVelocity << "]" << ret;
        msg << "KSEMParticle: [" << this << "] fMomentum has been recalculated" << ret;
        msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << ret;
        msg << "KSEMParticle: [" << this << "] fVelocity, fLorentzFactor and fSpeed have been secondarily recalculated" << ret;
        msg << "[" << fVelocity.X() << ", " << fVelocity.Y() << ", " << fVelocity.Z() << "]" << ret;
        msg << "[" << fLorentzFactor << "]" << ret;
        msg << "[" << fSpeed << "]";
#endif

        fGetVelocityAction = &KSElectromagneticParticle::DoNothing;
        fGetLorentzFactorAction = &KSElectromagneticParticle::DoNothing;
        fGetSpeedAction = &KSElectromagneticParticle::DoNothing;
        fGetKineticEnergyAction = &KSElectromagneticParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSElectromagneticParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSElectromagneticParticle::RecalculateAzimuthalAngleToX;

        fGetLongMomentumAction = &KSElectromagneticParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSElectromagneticParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSElectromagneticParticle::DoNothing;
        fGetPolarAngleToBAction = &KSElectromagneticParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;

        return;
    }
    inline const Double_t& KSElectromagneticParticle::GetTransVelocity() const
    {
        (this->*fGetTransVelocityAction)();
        return fTransVelocity;
    }
    inline void KSElectromagneticParticle::RecalculateTransVelocity() const
    {
        fTransVelocity = GetTransMomentum() / (GetMass() * GetLorentzFactor());

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSEMParticle::RecalculateTransVelocity";
        msg << "KSEMParticle: [" << this << "] recalculating fTransVelocity" << ret;
        msg << "[" << fTransVelocity << "]" << end;
#endif

        fGetTransVelocityAction = &KSElectromagneticParticle::DoNothing;

        return;
    }

    //****************
    //polar angle to B
    //****************

    inline void KSElectromagneticParticle::SetPolarAngleToB( const Double_t& NewPolarAngleToB )
    {
        register Double_t NewPolarAngleToB_SI = (KSConst::Pi() / 180.) * NewPolarAngleToB;
        register Double_t MomentumMagnitude = fMomentum.Mag();
        TVector3 LongUnit = GetMagneticField().Unit();
        TVector3 TransUnit = (fMomentum - GetLongMomentum() * LongUnit).Unit();

        fMomentum = MomentumMagnitude * TMath::Cos( NewPolarAngleToB_SI ) * LongUnit + MomentumMagnitude * TMath::Sin( NewPolarAngleToB_SI ) * TransUnit;
        fPolarAngleToB = NewPolarAngleToB;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSEMParticle::SetPolarAngleToB";
        msg << "KSEMParticle: [" << this << "] setting fPolarAngleToB" << ret;
        msg << "[" << fPolarAngleToB << "]" << end;
#endif

        fGetVelocityAction = &KSElectromagneticParticle::RecalculateVelocity;
        //fGetLorentzFactorAction unchanged
        //fGetSpeedAction unchanged
        //fGetKineticEnergyAction unchanged
        fGetPolarAngleToZAction = &KSElectromagneticParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSElectromagneticParticle::RecalculateAzimuthalAngleToX;

        fGetLongMomentumAction = &KSElectromagneticParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSElectromagneticParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSElectromagneticParticle::DoNothing;
        //fGetCyclotronFrequencyAction unchanged
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;

        return;
    }
    inline const Double_t& KSElectromagneticParticle::GetPolarAngleToB() const
    {
        (this->*fGetPolarAngleToBAction)();
        return fPolarAngleToB;
    }
    inline void KSElectromagneticParticle::RecalculatePolarAngleToB() const
    {
        fPolarAngleToB = TMath::ACos( (fMomentum * fMagneticField) / (fMagneticField.Mag() * fMomentum.Mag()) ) * 180. / KSConst::Pi();

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSEMParticle::RecalculatePolarAngleToB";
        msg << "KSEMParticle: [" << this << "] recalculating fPolarAngleToB" << ret;
        msg << "[" << fPolarAngleToB << "]" << end;
#endif

        fGetPolarAngleToBAction = &KSElectromagneticParticle::DoNothing;

        return;
    }

    //*******************
    //cyclotron frequency
    //*******************

    inline void KSElectromagneticParticle::SetCyclotronFrequency( const Double_t& NewCyclotronFrequency )
    {
        register Double_t LorentzFactor = (GetCharge() * GetMagneticField().Mag()) / (2.0 * KSConst::Pi() * GetMass() * NewCyclotronFrequency);
        register Double_t MomentumMagnitude = GetMass() * KSConst::C() * TMath::Sqrt( LorentzFactor * LorentzFactor - 1.0 );

        fMomentum.SetMag( MomentumMagnitude );
        fLorentzFactor = LorentzFactor;
        fCyclotronFrequency = NewCyclotronFrequency;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSEMParticle::SetCyclotronFrequency";
        msg << "KSEMParticle: [" << this << "] setting fCyclotronFrequency" << ret;
        msg << "[" << fCyclotronFrequency << "]" << ret;
        msg << "KSEMParticle: [" << this << "] fMomentum has been recalculated" << ret;
        msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << ret;
        msg << "KSEMParticle: [" << this << "] fLorentzFactor has been secondarily recalculated" << ret;
        msg << "[" << fLorentzFactor << "]" << end;
#endif

        fGetVelocityAction = &KSElectromagneticParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSElectromagneticParticle::DoNothing;
        fGetSpeedAction = &KSElectromagneticParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSElectromagneticParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSElectromagneticParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSElectromagneticParticle::RecalculateAzimuthalAngleToX;

        fGetLongMomentumAction = &KSElectromagneticParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSElectromagneticParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSElectromagneticParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::DoNothing;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;

        return;
    }
    inline void KSElectromagneticParticle::RecalculateCyclotronFrequency() const
    {
        fCyclotronFrequency = (TMath::Abs( GetCharge() ) * GetMagneticField().Mag()) / (2.0 * KSConst::Pi() * GetMass() * GetLorentzFactor());

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSEMParticle::RecalculateCyclotronFrequency";
        msg << "KSEMParticle: [" << this << "] recalculating fCyclotronFrequency" << ret;
        msg << "[" << fCyclotronFrequency << "]" << end;
#endif

        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::DoNothing;

        return;
    }
    inline const Double_t& KSElectromagneticParticle::GetCyclotronFrequency() const
    {
        (this->*fGetCyclotronFrequencyAction)();
        return fCyclotronFrequency;
    }

    //***********************
    //orbital magnetic moment
    //***********************

    inline const Double_t& KSElectromagneticParticle::GetOrbitalMagneticMoment() const
    {

        (this->*fGetOrbitalMagneticMomentAction)();
        return fOrbitalMagneticMoment;
    }
    inline void KSElectromagneticParticle::SetOrbitalMagneticMoment( const Double_t& NewOrbitalMagneticMoment )
    {
        register Double_t TransMomentumMagnitude = TMath::Sqrt( 2.0 * GetMass() * GetMagneticField().Mag() * NewOrbitalMagneticMoment );
        TVector3 TransMomentumVector = fMomentum - GetLongMomentum() * GetMagneticField().Unit();
        TransMomentumVector.SetMag( TransMomentumMagnitude - GetTransMomentum() );

        fMomentum += TransMomentumVector;
        fTransMomentum = TransMomentumMagnitude;
        fOrbitalMagneticMoment = NewOrbitalMagneticMoment;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSEMParticle::SetOrbitalMagneticMoment";
        msg << "KSEMParticle: [" << this << "] setting fOrbitalMagneticMoment" << ret;
        msg << "[" << fOrbitalMagneticMoment << "]" << ret;
        msg << "KSEMParticle: [" << this << "] fMomentum has been recalculated" << ret;
        msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << ret;
        msg << "KSEMParticle: [" << this << "] fTransMomentum has been secondarily recalculated" << ret;
        msg << "[" << fTransMomentum << "]" << end;
#endif

        fGetVelocityAction = &KSElectromagneticParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSElectromagneticParticle::RecalculateLorentzFactor;
        fGetSpeedAction = &KSElectromagneticParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSElectromagneticParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSElectromagneticParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSElectromagneticParticle::RecalculateAzimuthalAngleToX;

        //fGetLongMomentumAction unchanged
        fGetTransMomentumAction = &KSElectromagneticParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSElectromagneticParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::DoNothing;

        return;
    }
    inline void KSElectromagneticParticle::RecalculateOrbitalMagneticMoment() const
    {
        fOrbitalMagneticMoment = (GetTransMomentum() * GetTransMomentum()) / (2.0 * GetMass() * GetMagneticField().Mag());

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSEMParticle::RecalculateOrbitalMagneticMoment";
        msg << "KSEMParticle: [" << this << "] recalculating fOrbitalMagneticMoment" << ret;
        msg << "[" << fOrbitalMagneticMoment << "]" << end;
#endif

        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::DoNothing;

        return;
    }

}
#endif // KSEMPARTICLE_H_
