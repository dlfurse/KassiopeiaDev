#ifndef KSADIABATICPARTICLE_H_
#define KSADIABATICPARTICLE_H_

#include "KSElectromagneticParticle.h"

//basic variables:
//
//fPosition
//fLongMomentum
//fTransMomentum
//fGCtoParticleVector

namespace Kassiopeia
{

    class KSAdiabaticParticle :
        public KSElectromagneticParticle
    {
        public:
            friend class KSParticleFactory;

            //*********************
            //particle construction
            //*********************

        public:
            KSAdiabaticParticle( const KSAdiabaticParticle* aParticleToClone );
            virtual ~KSAdiabaticParticle();

        protected:
            KSAdiabaticParticle();

            //****************
            //cache management
            //****************

        protected:
            virtual void EnableAllVariables() const;
            virtual void DisableBasicVariables() const;

            //***************
            //printing system
            //***************

        public:
            virtual void Print() const;

            //***************************
            //adiabatic properties system
            //***************************

        public:

            //position (units are in meters)

            virtual void SetPosition( const TVector3& );
            virtual void SetPosition( const Double_t&, const Double_t&, const Double_t& );
            virtual void SetX( const Double_t& x );
            virtual void SetY( const Double_t& y );
            virtual void SetZ( const Double_t& z );

            //momentum (units are kg*m/s)

            virtual void SetMomentum( const TVector3& );
            virtual void SetMomentum( const Double_t&, const Double_t&, const Double_t& );
            virtual void SetPX( const Double_t& px );
            virtual void SetPY( const Double_t& py );
            virtual void SetPZ( const Double_t& pz );

            virtual void RecalculateMomentum() const;

            //velocity (units are m/s)

            virtual void SetVelocity( const TVector3& );

            virtual void RecalculateVelocity() const;

            // lorentz factor (unitless)

            virtual void SetLorentzFactor( const Double_t& );

            virtual void RecalculateLorentzFactor() const;

            //speed (units are m/s)

            virtual void SetSpeed( const Double_t& );

            virtual void RecalculateSpeed() const;

            //kinetic energy (units are eV)

            virtual void SetKineticEnergy( const Double_t& );

            virtual void RecalculateKineticEnergy() const;

            //polar angle of momentum vector (units are degrees)

            virtual void SetPolarAngleToZ( const Double_t& theta );

            virtual void RecalculatePolarAngleToZ() const;

            //azimuthal angle of momentum vector (units are degrees)

            virtual void SetAzimuthalAngleToX( const Double_t& phi );

            virtual void RecalculateAzimuthalAngleToX() const;

            //longitudinal momentum (units are kg*m/s)

            virtual void SetLongMomentum( const Double_t& );

            virtual void RecalculateLongMomentum() const;

            //transverse momentum (units are kg*m/s)

            virtual void SetTransMomentum( const Double_t& );

            virtual void RecalculateTransMomentum() const;

            //longitudinal velocity (units are m/s)

            virtual void SetLongVelocity( const Double_t& );

            virtual void RecalculateLongVelocity() const;

            //transverse velocity (units are m/s)

            virtual void SetTransVelocity( const Double_t& );

            virtual void RecalculateTransVelocity() const;

            //polar angle to b (units are degrees)

            virtual void SetPolarAngleToB( const Double_t& );

            virtual void RecalculatePolarAngleToB() const;

            //cyclotron frequency (units are 1/s)

            virtual void SetCyclotronFrequency( const Double_t& );

            virtual void RecalculateCyclotronFrequency() const;

            //orbital magnetic moment (units are A*m^2)

            virtual void SetOrbitalMagneticMoment( const Double_t& );

            virtual void RecalculateOrbitalMagneticMoment() const;

            //guiding center to particle direction (units are meters)

            const TVector3& GetGCtoParticleVector() const;

            void SetGCtoParticleVector( const TVector3& );

            void RecalculateGCtoParticleVector() const;

            //guiding center to particle orthogonal direction (unist are meters)

            const TVector3& GetGCtoParticleOrthVector() const;

            void SetGCtoParticleOrthVector( const TVector3& );

            void RecalculateGCtoParticleOrthVector() const;

            //*******************
            //actual data members
            //*******************

        protected:
            //vector pointing orthogonal to fGCtoParticleVector and magnetic field is cached since it's a dependent variable
            //vector pointing from guiding center to real particle position is not cached since it's a basic variable

            mutable TVector3 fGCtoParticleVector;
            mutable TVector3 fGCtoParticleOrthVector;

            //*******************************
            //recalculation function pointers
            //*******************************

        protected:
            mutable void (KSAdiabaticParticle::*fGetGCtoParticleVectorAction)() const;
            mutable void (KSAdiabaticParticle::*fGetGCtoParticleOrthVectorAction)() const;
    };

    //********
    //position
    //********

    inline void KSAdiabaticParticle::SetPosition( const TVector3& aPosition )
    {
        //Setting the position changes the guiding center position, which is a basic variable

        fPosition = aPosition;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KTrackAdiabaticStepParticle::SetPosition";
        msg << "KTrackAdiabaticStepParticle: setting fPosition" << ret;
        msg << "[" << fPosition.X() << ", " << fPosition.Y() << ", " << fPosition.Z() << "]" << end;
#endif

        //the fields need to be recalculated
        fGetMagneticFieldAction = &KSElectromagneticParticle::RecalculateMagneticField;
        fGetElectricFieldAction = &KSElectromagneticParticle::RecalculateElectricField;
        fGetElectricPotentialAction = &KSElectromagneticParticle::RecalculateElectricPotential;

        //cyclotron frequency, orbital magnetic moment, gc position and gc to particle orth vector all depend directly on the magnetic field
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;
        fGetGCtoParticleOrthVectorAction = &KSAdiabaticParticle::RecalculateGCtoParticleOrthVector;

        //momentum and velocity both depend directly on gc to particle orth vector
        fGetMomentumAction = &KSBasicParticle::RecalculateMomentum;
        fGetVelocityAction = &KSBasicParticle::RecalculateVelocity;

        //polar angle to z and azimuthal angle to x both depend directly on momentum
        fGetPolarAngleToZAction = &KSBasicParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSBasicParticle::RecalculateAzimuthalAngleToX;

        return;
    }
    inline void KSAdiabaticParticle::SetPosition( const Double_t& anX, const Double_t& aY, const Double_t& aZ )
    {
        //Setting the position changes the guiding center position, which is a basic variable

        fPosition.SetXYZ( anX, aY, aZ );

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KTrackAdiabaticStepParticle::SetPosition";
        msg << "KTrackAdiabaticStepParticle: setting fPosition" << ret;
        msg << "[" << fPosition.X() << ", " << fPosition.Y() << ", " << fPosition.Z() << "]" << end;
#endif

        //the fields need to be recalculated
        fGetMagneticFieldAction = &KSElectromagneticParticle::RecalculateMagneticField;
        fGetElectricFieldAction = &KSElectromagneticParticle::RecalculateElectricField;
        fGetElectricPotentialAction = &KSElectromagneticParticle::RecalculateElectricPotential;

        //cyclotron frequency, orbital magnetic moment, gc position and gc to particle orth vector all depend directly on the magnetic field
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;
        fGetGCtoParticleOrthVectorAction = &KSAdiabaticParticle::RecalculateGCtoParticleOrthVector;

        //momentum and velocity both depend directly on gc to particle orth vector
        fGetMomentumAction = &KSBasicParticle::RecalculateMomentum;
        fGetVelocityAction = &KSBasicParticle::RecalculateVelocity;

        //polar angle to z and azimuthal angle to x both depend directly on momentum
        fGetPolarAngleToZAction = &KSBasicParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSBasicParticle::RecalculateAzimuthalAngleToX;

        return;
    }
    inline void KSAdiabaticParticle::SetX( const Double_t& anX )
    {
        //Setting the position changes the guiding center position, which is a basic variable

        fPosition.SetX( anX );

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KTrackAdiabaticStepParticle::SetPosition";
        msg << "KTrackAdiabaticStepParticle: setting fPosition" << ret;
        msg << "[" << fPosition.X() << ", " << fPosition.Y() << ", " << fPosition.Z() << "]" << end;
#endif

        //the fields need to be recalculated
        fGetMagneticFieldAction = &KSElectromagneticParticle::RecalculateMagneticField;
        fGetElectricFieldAction = &KSElectromagneticParticle::RecalculateElectricField;
        fGetElectricPotentialAction = &KSElectromagneticParticle::RecalculateElectricPotential;

        //cyclotron frequency, orbital magnetic moment, gc position and gc to particle orth vector all depend directly on the magnetic field
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;
        fGetGCtoParticleOrthVectorAction = &KSAdiabaticParticle::RecalculateGCtoParticleOrthVector;

        //momentum and velocity both depend directly on gc to particle orth vector
        fGetMomentumAction = &KSBasicParticle::RecalculateMomentum;
        fGetVelocityAction = &KSBasicParticle::RecalculateVelocity;

        //polar angle to z and azimuthal angle to x both depend directly on momentum
        fGetPolarAngleToZAction = &KSBasicParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSBasicParticle::RecalculateAzimuthalAngleToX;

        return;
    }
    inline void KSAdiabaticParticle::SetY( const Double_t& aY )
    {
        //Setting the position changes the guiding center position, which is a basic variable

        fPosition.SetY( aY );

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KTrackAdiabaticStepParticle::SetPosition";
        msg << "KTrackAdiabaticStepParticle: setting fPosition" << ret;
        msg << "[" << fPosition.X() << ", " << fPosition.Y() << ", " << fPosition.Z() << "]" << end;
#endif

        //the fields need to be recalculated
        fGetMagneticFieldAction = &KSElectromagneticParticle::RecalculateMagneticField;
        fGetElectricFieldAction = &KSElectromagneticParticle::RecalculateElectricField;
        fGetElectricPotentialAction = &KSElectromagneticParticle::RecalculateElectricPotential;

        //cyclotron frequency, orbital magnetic moment, gc position and gc to particle orth vector all depend directly on the magnetic field
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;
        fGetGCtoParticleOrthVectorAction = &KSAdiabaticParticle::RecalculateGCtoParticleOrthVector;

        //momentum and velocity both depend directly on gc to particle orth vector
        fGetMomentumAction = &KSBasicParticle::RecalculateMomentum;
        fGetVelocityAction = &KSBasicParticle::RecalculateVelocity;

        //polar angle to z and azimuthal angle to x both depend directly on momentum
        fGetPolarAngleToZAction = &KSBasicParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSBasicParticle::RecalculateAzimuthalAngleToX;

        return;
    }
    inline void KSAdiabaticParticle::SetZ( const Double_t& aZ )
    {
        //Setting the position changes the guiding center position, which is a basic variable

        fPosition.SetZ( aZ );

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KTrackAdiabaticStepParticle::SetPosition";
        msg << "KTrackAdiabaticStepParticle: setting fPosition" << ret;
        msg << "[" << fPosition.X() << ", " << fPosition.Y() << ", " << fPosition.Z() << "]" << end;
#endif

        //the fields need to be recalculated
        fGetMagneticFieldAction = &KSElectromagneticParticle::RecalculateMagneticField;
        fGetElectricFieldAction = &KSElectromagneticParticle::RecalculateElectricField;
        fGetElectricPotentialAction = &KSElectromagneticParticle::RecalculateElectricPotential;

        //cyclotron frequency, orbital magnetic moment, gc position and gc to particle orth vector all depend directly on the magnetic field
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;
        fGetGCtoParticleOrthVectorAction = &KSAdiabaticParticle::RecalculateGCtoParticleOrthVector;

        //momentum and velocity both depend directly on gc to particle orth vector
        fGetMomentumAction = &KSBasicParticle::RecalculateMomentum;
        fGetVelocityAction = &KSBasicParticle::RecalculateVelocity;

        //polar angle to z and azimuthal angle to x both depend directly on momentum
        fGetPolarAngleToZAction = &KSBasicParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSBasicParticle::RecalculateAzimuthalAngleToX;

        return;
    }

    //********
    //momentum
    //********

    inline void KSAdiabaticParticle::SetMomentum( const TVector3& newMomentum )
    {
        //Setting the momentum changes the guiding center position.
        //Therefore, the real particle position is computed
        //and with newMomentum the new guiding center position is calculated.

        TVector3 RealPosition = fPosition + (fTransMomentum / (TMath::Abs( GetCharge() ) * GetMagneticField().Mag())) * fGCtoParticleVector;
        TVector3 MagFieldAtRealPos;
        fMagneticFieldCalculator->GetField( MagFieldAtRealPos, RealPosition, fTime );
        fPosition = RealPosition + (1. / (GetCharge() * MagFieldAtRealPos.Mag2())) * newMomentum.Cross( MagFieldAtRealPos );

        //The vector pointing from the guiding center to the particle
        //is correspondingly recalculated.
        fGCtoParticleVector = (RealPosition - fPosition).Unit();

        //The new longitudinal and transverse components of the momentum
        //are also recalculated.
        fMagneticFieldCalculator->GetField( fMagneticField, fPosition, fTime );
        fLongMomentum = newMomentum * fMagneticField.Unit();
        fTransMomentum = (newMomentum - fLongMomentum * fMagneticField.Unit()).Mag();

        //Finally, the new momentum is saved.
        fMomentum = newMomentum;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KTrackAdiabaticStepParticle::SetMomentum";
        msg << "KTrackAdiabaticStepParticle: setting fMomentum" << ret;
        msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << ret;
        msg << "KTrackAdiabaticStepParticle: fPosition, fLongMomentum, fTransMomentum, and fGCtoParticleVector have been recalculated" << ret;
        msg << "[" << fPosition.X() << ", " << fPosition.Y() << ", " << fPosition.Z() << "]" << ret;
        msg << "[" << fLongMomentum << "]" << ret;
        msg << "[" << fTransMomentum << "]" << ret;
        msg << "[" << fGCtoParticleVector.X() << ", " << fGCtoParticleVector.Y() << ", " << fGCtoParticleVector.Z() << "]" << ret;
        msg << "KTrackAdiabaticStepParticle: fMagneticField has been secondarily recalculated" << ret;
        msg << "[" << fMagneticField.X() << ", " << fMagneticField.Y() << ", " << fMagneticField.Z() << "]" << end;
#endif

        //The momentum is cached.
        fGetMomentumAction = &KSBasicParticle::DoNothing;

        //Position changed, so fields must be recalculated, except for the
        //magnetic field which was just recalculated to decompose momentum into
        //longitudinal and transverse components.
        fGetMagneticFieldAction = &KSBasicParticle::DoNothing;
        fGetElectricFieldAction = &KSElectromagneticParticle::RecalculateElectricField;
        fGetElectricPotentialAction = &KSElectromagneticParticle::RecalculateElectricPotential;

        //Every other variable must be recalculated.
        fGetVelocityAction = &KSBasicParticle::RecalculateVelocity;
        fGetSpeedAction = &KSBasicParticle::RecalculateSpeed;
        fGetLorentzFactorAction = &KSBasicParticle::RecalculateLorentzFactor;
        fGetKineticEnergyAction = &KSBasicParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSBasicParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSBasicParticle::RecalculateAzimuthalAngleToX;

        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSElectromagneticParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;

        fGetGCtoParticleOrthVectorAction = &KSAdiabaticParticle::RecalculateGCtoParticleOrthVector;

        return;
    }
    inline void KSAdiabaticParticle::SetMomentum( const Double_t& anX, const Double_t& aY, const Double_t& aZ )
    {
        //Setting the momentum changes the guiding center position.
        //Therefore, the real particle position is computed
        //and with newMomentum the new guiding center position is calculated.

        //Finally, the new momentum is saved.
        fMomentum.SetXYZ( anX, aY, aZ );

        TVector3 RealPosition = fPosition + (fTransMomentum / (TMath::Abs( GetCharge() ) * GetMagneticField().Mag())) * fGCtoParticleVector;
        TVector3 MagFieldAtRealPos;
        fMagneticFieldCalculator->GetField( MagFieldAtRealPos, RealPosition, fTime );
        fPosition = RealPosition + (1. / (GetCharge() * MagFieldAtRealPos.Mag2())) * fMomentum.Cross( MagFieldAtRealPos );

        //The vector pointing from the guiding center to the particle
        //is correspondingly recalculated.
        fGCtoParticleVector = (RealPosition - fPosition).Unit();

        //The new longitudinal and transverse components of the momentum
        //are also recalculated.
        fMagneticFieldCalculator->GetField( fMagneticField, fPosition, fTime );
        fLongMomentum = fMomentum * fMagneticField.Unit();
        fTransMomentum = (fMomentum - fLongMomentum * fMagneticField.Unit()).Mag();

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KTrackAdiabaticStepParticle::SetMomentum";
        msg << "KTrackAdiabaticStepParticle: setting fMomentum" << ret;
        msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << ret;
        msg << "KTrackAdiabaticStepParticle: fPosition, fLongMomentum, fTransMomentum, and fGCtoParticleVector have been recalculated" << ret;
        msg << "[" << fPosition.X() << ", " << fPosition.Y() << ", " << fPosition.Z() << "]" << ret;
        msg << "[" << fLongMomentum << "]" << ret;
        msg << "[" << fTransMomentum << "]" << ret;
        msg << "[" << fGCtoParticleVector.X() << ", " << fGCtoParticleVector.Y() << ", " << fGCtoParticleVector.Z() << "]" << ret;
        msg << "KTrackAdiabaticStepParticle: fMagneticField has been secondarily recalculated" << ret;
        msg << "[" << fMagneticField.X() << ", " << fMagneticField.Y() << ", " << fMagneticField.Z() << "]" << end;
#endif

        //The momentum is cached.
        fGetMomentumAction = &KSBasicParticle::DoNothing;

        //Position changed, so fields must be recalculated, except for the
        //magnetic field which was just recalculated to decompose momentum into
        //longitudinal and transverse components.
        fGetMagneticFieldAction = &KSBasicParticle::DoNothing;
        fGetElectricFieldAction = &KSElectromagneticParticle::RecalculateElectricField;
        fGetElectricPotentialAction = &KSElectromagneticParticle::RecalculateElectricPotential;

        //Every other variable must be recalculated.
        fGetVelocityAction = &KSBasicParticle::RecalculateVelocity;
        fGetSpeedAction = &KSBasicParticle::RecalculateSpeed;
        fGetLorentzFactorAction = &KSBasicParticle::RecalculateLorentzFactor;
        fGetKineticEnergyAction = &KSBasicParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSBasicParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSBasicParticle::RecalculateAzimuthalAngleToX;

        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSElectromagneticParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;

        fGetGCtoParticleOrthVectorAction = &KSAdiabaticParticle::RecalculateGCtoParticleOrthVector;

        return;
    }
    inline void KSAdiabaticParticle::SetPX( const Double_t& anX )
    {
        //Setting the momentum changes the guiding center position.
        //Therefore, the real particle position is computed
        //and with newMomentum the new guiding center position is calculated.

        //First, the new momentum is saved.
        fMomentum.SetXYZ( anX, fMomentum.Y(), fMomentum.Z() );

        TVector3 RealPosition = fPosition + (fTransMomentum / (TMath::Abs( GetCharge() ) * GetMagneticField().Mag())) * fGCtoParticleVector;
        TVector3 MagFieldAtRealPos;
        fMagneticFieldCalculator->GetField( MagFieldAtRealPos, RealPosition, fTime );
        fPosition = RealPosition + (1. / (GetCharge() * MagFieldAtRealPos.Mag2())) * fMomentum.Cross( MagFieldAtRealPos );

        //The vector pointing from the guiding center to the particle
        //is correspondingly recalculated.
        fGCtoParticleVector = (RealPosition - fPosition).Unit();

        //The new longitudinal and transverse components of the momentum
        //are also recalculated.
        fMagneticFieldCalculator->GetField( fMagneticField, fPosition, fTime );
        fLongMomentum = fMomentum * fMagneticField.Unit();
        fTransMomentum = (fMomentum - fLongMomentum * fMagneticField.Unit()).Mag();

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KTrackAdiabaticStepParticle::SetMomentum";
        msg << "KTrackAdiabaticStepParticle: setting fMomentum" << ret;
        msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << ret;
        msg << "KTrackAdiabaticStepParticle: fPosition, fLongMomentum, fTransMomentum, and fGCtoParticleVector have been recalculated" << ret;
        msg << "[" << fPosition.X() << ", " << fPosition.Y() << ", " << fPosition.Z() << "]" << ret;
        msg << "[" << fLongMomentum << "]" << ret;
        msg << "[" << fTransMomentum << "]" << ret;
        msg << "[" << fGCtoParticleVector.X() << ", " << fGCtoParticleVector.Y() << ", " << fGCtoParticleVector.Z() << "]" << ret;
        msg << "KTrackAdiabaticStepParticle: fMagneticField has been secondarily recalculated" << ret;
        msg << "[" << fMagneticField.X() << ", " << fMagneticField.Y() << ", " << fMagneticField.Z() << "]" << end;
#endif

        //The momentum is cached.
        fGetMomentumAction = &KSBasicParticle::DoNothing;

        //Position changed, so fields must be recalculated, except for the
        //magnetic field which was just recalculated to decompose momentum into
        //longitudinal and transverse components.
        fGetMagneticFieldAction = &KSBasicParticle::DoNothing;
        fGetElectricFieldAction = &KSElectromagneticParticle::RecalculateElectricField;
        fGetElectricPotentialAction = &KSElectromagneticParticle::RecalculateElectricPotential;

        //Every other variable must be recalculated.
        fGetVelocityAction = &KSBasicParticle::RecalculateVelocity;
        fGetSpeedAction = &KSBasicParticle::RecalculateSpeed;
        fGetLorentzFactorAction = &KSBasicParticle::RecalculateLorentzFactor;
        fGetKineticEnergyAction = &KSBasicParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSBasicParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSBasicParticle::RecalculateAzimuthalAngleToX;

        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSElectromagneticParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;

        fGetGCtoParticleOrthVectorAction = &KSAdiabaticParticle::RecalculateGCtoParticleOrthVector;

        return;
    }
    inline void KSAdiabaticParticle::SetPY( const Double_t& aY )
    {
        //Setting the momentum changes the guiding center position.
        //Therefore, the real particle position is computed
        //and with newMomentum the new guiding center position is calculated.

        //First, the new momentum is saved.
        fMomentum.SetXYZ( fMomentum.X(), aY, fMomentum.Z() );
        TVector3 RealPosition = fPosition + (fTransMomentum / (TMath::Abs( GetCharge() ) * GetMagneticField().Mag())) * fGCtoParticleVector;
        TVector3 MagFieldAtRealPos;
        fMagneticFieldCalculator->GetField( MagFieldAtRealPos, RealPosition, fTime );
        fPosition = RealPosition + (1. / (GetCharge() * MagFieldAtRealPos.Mag2())) * fMomentum.Cross( MagFieldAtRealPos );

        //The vector pointing from the guiding center to the particle
        //is correspondingly recalculated.
        fGCtoParticleVector = (RealPosition - fPosition).Unit();

        //The new longitudinal and transverse components of the momentum
        //are also recalculated.
        fMagneticFieldCalculator->GetField( fMagneticField, fPosition, fTime );
        fLongMomentum = fMomentum * fMagneticField.Unit();
        fTransMomentum = (fMomentum - fLongMomentum * fMagneticField.Unit()).Mag();

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KTrackAdiabaticStepParticle::SetMomentum";
        msg << "KTrackAdiabaticStepParticle: setting fMomentum" << ret;
        msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << ret;
        msg << "KTrackAdiabaticStepParticle: fPosition, fLongMomentum, fTransMomentum, and fGCtoParticleVector have been recalculated" << ret;
        msg << "[" << fPosition.X() << ", " << fPosition.Y() << ", " << fPosition.Z() << "]" << ret;
        msg << "[" << fLongMomentum << "]" << ret;
        msg << "[" << fTransMomentum << "]" << ret;
        msg << "[" << fGCtoParticleVector.X() << ", " << fGCtoParticleVector.Y() << ", " << fGCtoParticleVector.Z() << "]" << ret;
        msg << "KTrackAdiabaticStepParticle: fMagneticField has been secondarily recalculated" << ret;
        msg << "[" << fMagneticField.X() << ", " << fMagneticField.Y() << ", " << fMagneticField.Z() << "]" << end;
#endif

        //The momentum is cached.
        fGetMomentumAction = &KSBasicParticle::DoNothing;

        //Position changed, so fields must be recalculated, except for the
        //magnetic field which was just recalculated to decompose momentum into
        //longitudinal and transverse components.
        fGetMagneticFieldAction = &KSBasicParticle::DoNothing;
        fGetElectricFieldAction = &KSElectromagneticParticle::RecalculateElectricField;
        fGetElectricPotentialAction = &KSElectromagneticParticle::RecalculateElectricPotential;

        //Every other variable must be recalculated.
        fGetVelocityAction = &KSBasicParticle::RecalculateVelocity;
        fGetSpeedAction = &KSBasicParticle::RecalculateSpeed;
        fGetLorentzFactorAction = &KSBasicParticle::RecalculateLorentzFactor;
        fGetKineticEnergyAction = &KSBasicParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSBasicParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSBasicParticle::RecalculateAzimuthalAngleToX;

        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSElectromagneticParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;

        fGetGCtoParticleOrthVectorAction = &KSAdiabaticParticle::RecalculateGCtoParticleOrthVector;

        return;
    }
    inline void KSAdiabaticParticle::SetPZ( const Double_t& aZ )
    {
        //Setting the momentum changes the guiding center position.
        //Therefore, the real particle position is computed
        //and with newMomentum the new guiding center position is calculated.

        //First, the new momentum is saved.
        fMomentum.SetXYZ( fMomentum.X(), fMomentum.Y(), aZ );
        TVector3 RealPosition = fPosition + (fTransMomentum / (TMath::Abs( GetCharge() ) * GetMagneticField().Mag())) * fGCtoParticleVector;
        TVector3 MagFieldAtRealPos;
        fMagneticFieldCalculator->GetField( MagFieldAtRealPos, RealPosition, fTime );
        fPosition = RealPosition + (1. / (GetCharge() * MagFieldAtRealPos.Mag2())) * fMomentum.Cross( MagFieldAtRealPos );

        //The vector pointing from the guiding center to the particle
        //is correspondingly recalculated.
        fGCtoParticleVector = (RealPosition - fPosition).Unit();

        //The new longitudinal and transverse components of the momentum
        //are also recalculated.
        fMagneticFieldCalculator->GetField( fMagneticField, fPosition, fTime );
        fLongMomentum = fMomentum * fMagneticField.Unit();
        fTransMomentum = (fMomentum - fLongMomentum * fMagneticField.Unit()).Mag();

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KTrackAdiabaticStepParticle::SetMomentum";
        msg << "KTrackAdiabaticStepParticle: setting fMomentum" << ret;
        msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << ret;
        msg << "KTrackAdiabaticStepParticle: fPosition, fLongMomentum, fTransMomentum, and fGCtoParticleVector have been recalculated" << ret;
        msg << "[" << fPosition.X() << ", " << fPosition.Y() << ", " << fPosition.Z() << "]" << ret;
        msg << "[" << fLongMomentum << "]" << ret;
        msg << "[" << fTransMomentum << "]" << ret;
        msg << "[" << fGCtoParticleVector.X() << ", " << fGCtoParticleVector.Y() << ", " << fGCtoParticleVector.Z() << "]" << ret;
        msg << "KTrackAdiabaticStepParticle: fMagneticField has been secondarily recalculated" << ret;
        msg << "[" << fMagneticField.X() << ", " << fMagneticField.Y() << ", " << fMagneticField.Z() << "]" << end;
#endif

        //The momentum is cached.
        fGetMomentumAction = &KSBasicParticle::DoNothing;

        //Position changed, so fields must be recalculated, except for the
        //magnetic field which was just recalculated to decompose momentum into
        //longitudinal and transverse components.
        fGetMagneticFieldAction = &KSBasicParticle::DoNothing;
        fGetElectricFieldAction = &KSElectromagneticParticle::RecalculateElectricField;
        fGetElectricPotentialAction = &KSElectromagneticParticle::RecalculateElectricPotential;

        //Every other variable must be recalculated.
        fGetVelocityAction = &KSBasicParticle::RecalculateVelocity;
        fGetSpeedAction = &KSBasicParticle::RecalculateSpeed;
        fGetLorentzFactorAction = &KSBasicParticle::RecalculateLorentzFactor;
        fGetKineticEnergyAction = &KSBasicParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSBasicParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSBasicParticle::RecalculateAzimuthalAngleToX;

        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSElectromagneticParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;

        fGetGCtoParticleOrthVectorAction = &KSAdiabaticParticle::RecalculateGCtoParticleOrthVector;

        return;
    }

    inline void KSAdiabaticParticle::RecalculateMomentum() const
    {
        //The momentum is calculated from the magnetic field and longitudinal and transverse momentum.

        TVector3 BHat = GetMagneticField().Unit();
        fMomentum = fLongMomentum * BHat + (fTransMomentum * GetCharge() / TMath::Abs( GetCharge() )) * (fGCtoParticleVector.Cross( BHat ));

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KTrackAdiabaticStepParticle::RecalculateMomementum";
        msg << "KTrackAdiabaticStepParticle: recalculating fMomentum" << ret;
        msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << end;
#endif

        //setting the pointer of momentum to cached
        fGetMomentumAction = &KSBasicParticle::DoNothing;

        return;
    }

    //********
    //velocity
    //********

    inline void KSAdiabaticParticle::SetVelocity( const TVector3& newVelocity )
    {
        //Setting the velocity changes the lorentz factor and the momentum.

        fLorentzFactor = 1. / (TMath::Sqrt( 1. - newVelocity * newVelocity / (KSConst::C() * KSConst::C()) ));
        fMomentum = GetMass() * fLorentzFactor * newVelocity;

        //If the momentum is changed also the guiding center position is changed
        TVector3 RealPosition = fPosition + (fTransMomentum / (TMath::Abs( GetCharge() ) * GetMagneticField().Mag())) * fGCtoParticleVector;
        TVector3 MagFieldAtRealPos;
        fMagneticFieldCalculator->GetField( MagFieldAtRealPos, RealPosition, fTime );
        fPosition = RealPosition + (1. / (GetCharge() * MagFieldAtRealPos.Mag2())) * fMomentum.Cross( MagFieldAtRealPos );

        //The vector pointing from the guiding center to the particle
        //is correspondingly recalculated.
        fGCtoParticleVector = (RealPosition - fPosition).Unit();

        //The new longitudinal and transverse components of the momentum
        //are also recalculated.
        fMagneticFieldCalculator->GetField( fMagneticField, fPosition, fTime );
        fLongMomentum = fMomentum * fMagneticField.Unit();
        fTransMomentum = (fMomentum - fLongMomentum * fMagneticField.Unit()).Mag();

        //Finally, the new velocity is saved.
        fVelocity = newVelocity;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KTrackAdiabaticStepParticle::SetVelocity";
        msg << "KTrackAdiabaticStepParticle: setting fVelocity" << ret;
        msg << "[" << fVelocity.X() << ", " << fVelocity.Y() << ", " << fVelocity.Z() << "]" << ret;
        msg << "KTrackAdiabaticStepParticle: fPosition, fLongMomentum, fTransMomentum, and fGCtoParticleVector have been recalculated" << ret;
        msg << "[" << fPosition.X() << ", " << fPosition.Y() << ", " << fPosition.Z() << "]" << ret;
        msg << "[" << fLongMomentum << "]" << ret;
        msg << "[" << fTransMomentum << "]" << ret;
        msg << "[" << fGCtoParticleVector.X() << ", " << fGCtoParticleVector.Y() << ", " << fGCtoParticleVector.Z() << "]" << ret;
        msg << "KTrackAdiabaticStepParticle: fMomentum, fLorentzFactor and fMagneticField have been secondarily recalculated" << ret;
        msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << ret;
        msg << "[" << fLorentzFactor << "]" << ret;
        msg << "[" << fMagneticField.X() << ", " << fMagneticField.Y() << ", " << fMagneticField.Z() << "]" << end;
#endif

        //all fields except for the magnetic field have to be recalculated
        fGetMagneticFieldAction = &KSBasicParticle::DoNothing;
        fGetElectricFieldAction = &KSElectromagneticParticle::RecalculateElectricField;
        fGetElectricPotentialAction = &KSElectromagneticParticle::RecalculateElectricPotential;

        //momentum, velocity, and the lorentz factor are cached:
        fGetMomentumAction = &KSBasicParticle::DoNothing;
        fGetVelocityAction = &KSBasicParticle::DoNothing;
        fGetLorentzFactorAction = &KSBasicParticle::DoNothing;

        //all other variables must be recalculated:
        fGetSpeedAction = &KSBasicParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSBasicParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSBasicParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSBasicParticle::RecalculateAzimuthalAngleToX;

        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetPolarAngleToBAction = &KSElectromagneticParticle::RecalculatePolarAngleToB;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;
        fGetGCtoParticleOrthVectorAction = &KSAdiabaticParticle::RecalculateGCtoParticleOrthVector;

        return;
    }

    inline void KSAdiabaticParticle::RecalculateVelocity() const
    {
        //Velocity is computed from the momentum and lorentz factor.

        fVelocity = 1. / (GetLorentzFactor() * GetMass()) * GetMomentum();

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KTrackAdiabaticStepParticle::RecalculateVelocity";
        msg << "KTrackAdiabaticStepParticle: recalculating fVelocity" << ret;
        msg << "[" << fVelocity.X() << ", " << fVelocity.Y() << ", " << fVelocity.Z() << "]" << end;
#endif

        fGetVelocityAction = &KSBasicParticle::DoNothing;

        return;
    }

    //**********************
    //lorentz factor (gamma)
    //**********************

    inline void KSAdiabaticParticle::SetLorentzFactor( const Double_t& newLorentzFactor )
    {
        //Setting the lorentz factor changes the absolute value of the momentum.
        //Therefore, transverse and longitudinal momentum have to be rescaled correspondingly.

        Double_t MomentumMagnitude = GetMass() * KSConst::C() * TMath::Sqrt( newLorentzFactor * newLorentzFactor - 1. );
        Double_t OldMomentumMagnitude = TMath::Sqrt( fTransMomentum * fTransMomentum + fLongMomentum * fLongMomentum );
        Double_t Ratio = OldMomentumMagnitude / MomentumMagnitude;
        fTransMomentum = fTransMomentum / Ratio;
        fLongMomentum = fLongMomentum / Ratio;

        //lorentz factor is set to its new value
        fLorentzFactor = newLorentzFactor;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KTrackAdiabaticStepParticle::SetLorentzFactor";
        msg << "KTrackAdiabaticStepParticle: setting fLorentzFactor" << ret;
        msg << "[" << fLorentzFactor << "]" << ret;
        msg << "KTrackAdiabaticStepParticle: fLongMomentum and fTransMomentum have been recalculated" << ret;
        msg << "[" << fLongMomentum << "]" << ret;
        msg << "[" << fTransMomentum << "]" << end;
#endif

        //lorentz factor is cached
        fGetLorentzFactorAction = &KSBasicParticle::DoNothing;

        //these quantities have to be recalculated:
        fGetVelocityAction = &KSBasicParticle::RecalculateVelocity;
        fGetSpeedAction = &KSBasicParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSBasicParticle::RecalculateKineticEnergy;

        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;

        return;
    }
    inline void KSAdiabaticParticle::RecalculateLorentzFactor() const
    {
        //The lorentz factor is computed from the longitudinal and transverse momentum.

        fLorentzFactor = TMath::Sqrt( 1. + (fLongMomentum * fLongMomentum + fTransMomentum * fTransMomentum) / (GetMass() * GetMass() * KSConst::C() * KSConst::C()) );

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KTrackAdiabaticStepParticle::RecalculateLorentzFactor";
        msg << "KTrackAdiabaticStepParticle: recalculating fLorentzFactor" << ret;
        msg << "[" << fLorentzFactor << "]" << end;
#endif

        fGetLorentzFactorAction = &KSBasicParticle::DoNothing;

        return;
    }

    //*****
    //speed
    //*****

    inline void KSAdiabaticParticle::SetSpeed( const Double_t& newSpeed )
    {
        //Setting the speed changes the lorentz factor and the magnitude of the momentum.
        //Longitudinal and transverse are correspodingly rescaled.

        fLorentzFactor = 1. / (TMath::Sqrt( 1. - newSpeed * newSpeed / (KSConst::C() * KSConst::C()) ));
        Double_t MomentumMagnitude = GetMass() * KSConst::C() * TMath::Sqrt( fLorentzFactor * fLorentzFactor - 1. );
        Double_t OldMomentumMagnitude = TMath::Sqrt( GetTransMomentum() * GetTransMomentum() + GetLongMomentum() * GetLongMomentum() );
        Double_t Ratio = OldMomentumMagnitude / MomentumMagnitude;
        fTransMomentum = GetTransMomentum() / Ratio;
        fLongMomentum = GetLongMomentum() / Ratio;

        //speed is set to its new value
        fSpeed = newSpeed;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KTrackAdiabaticStepParticle::SetSpeed";
        msg << "KTrackAdiabaticStepParticle: setting fSpeed" << ret;
        msg << "[" << fSpeed << "]" << ret;
        msg << "KTrackAdiabaticStepParticle: fLongMomentum and fTransMomentum have been recalculated" << ret;
        msg << "[" << fLongMomentum << "]" << ret;
        msg << "[" << fTransMomentum << "]" << ret;
        msg << "KTrackAdiabaticStepParticle: fLorentzFactor has been secondarily recalculated" << ret;
        msg << "[" << fLorentzFactor << "]" << end;
#endif

        //lorentz factor and speed are cached
        fGetSpeedAction = &KSBasicParticle::DoNothing;
        fGetLorentzFactorAction = &KSBasicParticle::DoNothing;

        //these quantities have to be recalculated:
        fGetVelocityAction = &KSBasicParticle::RecalculateVelocity;
        fGetKineticEnergyAction = &KSBasicParticle::RecalculateKineticEnergy;

        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;

        return;
    }
    inline void KSAdiabaticParticle::RecalculateSpeed() const
    {
        //Speed is computed from the longitudinal and tranversal velocity.

        fSpeed = TMath::Sqrt( GetTransVelocity() * GetTransVelocity() + GetLongVelocity() * GetLongVelocity() );

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KTrackAdiabaticStepParticle::RecalculateSpeed";
        msg << "KTrackAdiabaticStepParticle: recalculating fSpeed" << ret;
        msg << "[" << fSpeed << "]" << end;
#endif

        fGetSpeedAction = &KSBasicParticle::DoNothing;

        return;
    }

    //**************
    //kinetic energy
    //**************

    inline void KSAdiabaticParticle::SetKineticEnergy( const Double_t& newKineticEnergy )
    {
        //Setting the kinetic energy changes the absolute value of the momentum.
        //Transversal and longitudinal momentum are rescaled correspondingly:

        Double_t newKineticEnergy_SI = newKineticEnergy * KSConst::Q();
        Double_t MomentumMagnitude = (newKineticEnergy_SI / KSConst::C()) * TMath::Sqrt( 1. + (2. * GetMass() * KSConst::C() * KSConst::C()) / newKineticEnergy_SI );
        Double_t OldMomentumMagnitude = TMath::Sqrt( GetTransMomentum() * GetTransMomentum() + GetLongMomentum() * GetLongMomentum() );
        Double_t ratio = OldMomentumMagnitude / MomentumMagnitude;
        fTransMomentum = GetTransMomentum() / ratio;
        fLongMomentum = GetLongMomentum() / ratio;

        //kinetic energy is set to its new value
        fKineticEnergy = newKineticEnergy;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KTrackAdiabaticStepParticle::SetKineticEnergy";
        msg << "KTrackAdiabaticStepParticle: setting fKineticEnergy" << ret;
        msg << "[" << fKineticEnergy << "]" << ret;
        msg << "KTrackAdiabaticStepParticle: fLongMomentum and fTransMomentum have been recalculated" << ret;
        msg << "[" << fLongMomentum << "]" << ret;
        msg << "[" << fTransMomentum << "]" << end;
#endif

        //kinetic energy is cached
        fGetKineticEnergyAction = &KSBasicParticle::DoNothing;

        //these quantities have to be recalculated:
        fGetVelocityAction = &KSBasicParticle::RecalculateVelocity;
        fGetSpeedAction = &KSBasicParticle::RecalculateSpeed;
        fGetLorentzFactorAction = &KSBasicParticle::RecalculateLorentzFactor;

        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;

        return;
    }
    inline void KSAdiabaticParticle::RecalculateKineticEnergy() const
    {
        // the kinetic energy is computed from the longitudinal and transverse momentum and converted to electron volts
        fKineticEnergy = (1. / KSConst::Q()) * ((fLongMomentum * fLongMomentum + fTransMomentum * fTransMomentum) / ((GetLorentzFactor() + 1.) * GetMass()));

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KTrackAdiabaticStepParticle::RecalculateKineticEnergy";
        msg << "KTrackAdiabaticStepParticle: recalculating fKineticEnergy" << ret;
        msg << "[" << fKineticEnergy << "]" << end;
#endif

        fGetKineticEnergyAction = &KSBasicParticle::DoNothing;

        return;
    }

    //*********************
    //longitudinal momentum
    //*********************

    inline void KSAdiabaticParticle::SetLongMomentum( const Double_t& newLongMomentum )
    {
        //Longitudinal momentum is a basic property of the AdiabaticParticle.
        //No other basic properties of the particle need to be updated when setting the longitudinal momentum.

        fLongMomentum = newLongMomentum;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KTrackAdiabaticStepParticle::SetLongMomentum";
        msg << "KTrackAdiabaticStepParticle: setting fLongMomentum" << ret;
        msg << "[" << fLongMomentum << "]" << end;
#endif

        //by changing the longitudinal momentum, these quantities have to be recalculated:
        fGetMomentumAction = &KSBasicParticle::RecalculateMomentum;
        fGetVelocityAction = &KSBasicParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSBasicParticle::RecalculateLorentzFactor;
        fGetSpeedAction = &KSBasicParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSBasicParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSBasicParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSBasicParticle::RecalculateAzimuthalAngleToX;

        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSElectromagneticParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;

        return;
    }
    inline void KSAdiabaticParticle::RecalculateLongMomentum() const
    {
        //should not be called, basic variable!!!
        return;
    }

    //*******************
    //transverse momentum
    //*******************

    inline void KSAdiabaticParticle::SetTransMomentum( const Double_t& newTransMomentum )
    {
        //Transverse momentum is a basic property of the AdiabaticParticle.
        //No other basic properties of the particle need to be updated when setting the transverse momentum.

        fTransMomentum = newTransMomentum;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KTrackAdiabaticStepParticle::SetTransMomentum";
        msg << "KTrackAdiabaticStepParticle: setting fTransMomentum" << ret;
        msg << "[" << fTransMomentum << "]" << end;
#endif

        //by changing the transverse momentum, these quantities have to be recalculated:
        fGetMomentumAction = &KSBasicParticle::RecalculateMomentum;
        fGetVelocityAction = &KSBasicParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSBasicParticle::RecalculateLorentzFactor;
        fGetSpeedAction = &KSBasicParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSBasicParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSBasicParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSBasicParticle::RecalculateAzimuthalAngleToX;

        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetPolarAngleToBAction = &KSElectromagneticParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;

        return;
    }
    inline void KSAdiabaticParticle::RecalculateTransMomentum() const
    {
        //should not be called, basic variable!!!
        return;
    }

    //*********************
    //longitudinal velocity
    //*********************

    inline void KSAdiabaticParticle::SetLongVelocity( const Double_t& newLongVelocity )
    {
        //Setting the longitudinal velocity changes the lorentz factor and therefore the transverse and longitudinal momentum

        Double_t NewLorentzFactor = 1. / TMath::Sqrt( 1. - (GetTransVelocity() * GetTransVelocity() + newLongVelocity * newLongVelocity) / (KSConst::C() * KSConst::C()) );
        fTransMomentum = GetMass() * NewLorentzFactor * GetTransVelocity();
        fLongMomentum = GetMass() * NewLorentzFactor * newLongVelocity;
        fLorentzFactor = NewLorentzFactor;
        fLongVelocity = newLongVelocity;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KTrackAdiabaticStepParticle::SetLongVelocity";
        msg << "KTrackAdiabaticStepParticle: setting fLongVelocity" << ret;
        msg << "[" << fLongVelocity << '\n';;
        msg << "KTrackAdiabaticStepParticle: fLongMomentum and fTransMomentum have been recalculated" << ret;
        msg << "[" << fLongMomentum << "]" << ret;
        msg << "[" << fTransMomentum << "]" << ret;
        msg << "KTrackAdiabaticStepParticle: fLorentzFactor has been secondarily recalculated" << ret;
        msg << "[" << fLorentzFactor << "]" << end;
#endif

        //longitudinal velocity and lorentz factor are cached
        fGetLongVelocityAction = &KSBasicParticle::DoNothing;
        fGetLorentzFactorAction = &KSBasicParticle::DoNothing;

        //these quantities have to be recalculated:
        fGetMomentumAction = &KSBasicParticle::RecalculateMomentum;
        fGetVelocityAction = &KSBasicParticle::RecalculateVelocity;
        fGetSpeedAction = &KSBasicParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSBasicParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSBasicParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSBasicParticle::RecalculateAzimuthalAngleToX;

        fGetPolarAngleToBAction = &KSElectromagneticParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;

        return;
    }
    inline void KSAdiabaticParticle::RecalculateLongVelocity() const
    {
        //Longitudinal velocity is computed from the longitudinal momentum and the lorentz factor.

        fLongVelocity = fLongMomentum / (GetLorentzFactor() * GetMass());

#ifdef DEBUG_VERBOSE
        msg < "KTrackAdiabaticStepParticle::RecalculateLongVelocity";
        E = KSException::eKTrackDebug;
        msg << "KTrackAdiabaticStepParticle: recalculating fLongVelocity" << ret;
        msg << "[" << fLongVelocity << "]";
        CatchException(E);
#endif

        fGetLongVelocityAction = &KSBasicParticle::DoNothing;

        return;
    }

    //*******************
    //transverse velocity
    //*******************

    inline void KSAdiabaticParticle::SetTransVelocity( const Double_t& newTransVelocity )
    {
        //Setting the tranverse velocity changes the lorentz factor and therefore the longitudinal and transverse momentum.

        Double_t NewLorentzFactor = 1. / TMath::Sqrt( 1. - (newTransVelocity * newTransVelocity + GetLongVelocity() * GetLongVelocity()) / (KSConst::C() * KSConst::C()) );
        fTransMomentum = GetMass() * NewLorentzFactor * newTransVelocity;
        fLongMomentum = GetMass() * NewLorentzFactor * GetLongVelocity();
        fLorentzFactor = NewLorentzFactor;

        fTransVelocity = newTransVelocity;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KTrackAdiabaticStepParticle::SetTransVelocity";
        msg << "KTrackAdiabaticStepParticle: setting fTransVelocity" << ret;
        msg << "[" << fTransVelocity << "]" << ret;
        msg << "KTrackAdiabaticStepParticle: fLongMomentum and fTransMomentum have been recalculated" << ret;
        msg << "[" << fLongMomentum << "]" << ret;
        msg << "[" << fTransMomentum << "]" << ret;
        msg << "KTrackAdiabaticStepParticle: fLorentzFactor has been secondarily recalculated" << ret;
        msg << "[" << fLorentzFactor << "]" << end;
#endif

        //transverse velocity and lorentz factor are cached
        fGetTransVelocityAction = &KSBasicParticle::DoNothing;
        fGetLorentzFactorAction = &KSBasicParticle::DoNothing;

        //these quantities have to be recalculated:
        fGetMomentumAction = &KSBasicParticle::RecalculateMomentum;
        fGetVelocityAction = &KSBasicParticle::RecalculateVelocity;
        fGetSpeedAction = &KSBasicParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSBasicParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSBasicParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSBasicParticle::RecalculateAzimuthalAngleToX;

        fGetPolarAngleToBAction = &KSElectromagneticParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;

        return;
    }
    inline void KSAdiabaticParticle::RecalculateTransVelocity() const
    {
        //Transverse velocity is computed from transverse momentum and the lorentz factor.

        fTransVelocity = fTransMomentum / (GetLorentzFactor() * GetMass());

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KTrackAdiabaticStepParticle::RecalculateTransVelocity";
        msg << "KTrackAdiabaticStepParticle: recalculating fTransVelocity" << ret;
        msg << "[" << fTransVelocity << "]" << end;
#endif

        fGetTransVelocityAction = &KSBasicParticle::DoNothing;

        return;
    }

    //****************
    //polar angle to B
    //****************

    inline void KSAdiabaticParticle::SetPolarAngleToB( const Double_t& newPolarAngleToB )
    {
        //setting the polar angle to b changes the ratio of the longitudinal and transverse momenta while preserving the kinetic energy
        register Double_t NewPolarAngleToB_SI = (KSConst::Pi() / 180.) * newPolarAngleToB;
        register Double_t MomentumMagnitude = TMath::Sqrt( fLongMomentum * fLongMomentum + fTransMomentum * fTransMomentum );
        fLongMomentum = MomentumMagnitude * TMath::Cos( NewPolarAngleToB_SI );
        fTransMomentum = MomentumMagnitude * TMath::Cos( NewPolarAngleToB_SI );

        fPolarAngleToB = newPolarAngleToB;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSAdiabaticParticle::SetPolarAngleToB";
        msg << "KSAdiabaticParticle:: recalculating fPolarAngleToB" << ret;
        msg << "[" << fPolarAngleToB << "]" << end;
#endif

        //polar angle to b is cached:
        fGetPolarAngleToBAction = &KSBasicParticle::DoNothing;

        //these quantities have to be recalculated:
        fGetMomentumAction = &KSBasicParticle::RecalculateMomentum;
        fGetVelocityAction = &KSBasicParticle::RecalculateVelocity;

        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;

        return;
    }
    inline void KSAdiabaticParticle::RecalculatePolarAngleToB() const
    {
        //polar angle to b is computed from the ratio of transverse momentum to longitudinal momentum

        fPolarAngleToB = (180. / KSConst::Pi()) * TMath::ACos( fTransMomentum / TMath::Sqrt( fLongMomentum * fLongMomentum + fTransMomentum * fTransMomentum ) );

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KTrackAdiabaticStepParticle::RecalculatePolarAngleToB";
        msg << "KTrackAdiabaticStepParticle: recalculating fPolarAngleToB;" << ret;
        msg << "[" << fPolarAngleToB << "]" << end;
#endif

        fGetPolarAngleToBAction = &KSBasicParticle::DoNothing;

        return;
    }

    //*******************
    //cyclotron frequency
    //*******************

    inline void KSAdiabaticParticle::SetCyclotronFrequency( const Double_t& newCyclotronFrequency )
    {
        //Setting the Cyclotron frequency changes the lorentz factor and the magnitude of the momentum.
        //Longitudinal and transverse are correspodingly rescaled.

        fLorentzFactor = newCyclotronFrequency * GetMass() / (TMath::Abs( GetCharge() ) * GetMagneticField().Mag());
        Double_t MomentumMagnitude = GetMass() * KSConst::C() * TMath::Sqrt( fLorentzFactor * fLorentzFactor - 1. );
        Double_t OldMomentumMagnitude = TMath::Sqrt( GetTransMomentum() * GetTransMomentum() + GetLongMomentum() * GetLongMomentum() );
        Double_t Ratio = OldMomentumMagnitude / MomentumMagnitude;
        fTransMomentum = GetTransMomentum() / Ratio;
        fLongMomentum = GetLongMomentum() / Ratio;

        //Cyclotron frequency is set to its new value
        fCyclotronFrequency = newCyclotronFrequency;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KTrackAdiabaticStepParticle::SetCyclotronFrequency";
        msg << "KTrackAdiabaticStepParticle: setting fCyclotronFrequency" << ret;
        msg << "[" << fCyclotronFrequency << "]" << ret;
        msg << "KTrackAdiabaticStepParticle: fLongMomentum and fTransMomentum have been recalculated" << ret;
        msg << "[" << fLongMomentum << "]" << ret;
        msg << "[" << fTransMomentum << "]" << ret;
        msg << "KTrackAdiabaticStepParticle: fLorentzFactor has been secondarily recalculated" << ret;
        msg << "[" << fLorentzFactor << "]" << end;
#endif

        //lorentz factor and Cyclotron frequency are cached
        fGetCyclotronFrequencyAction = &KSBasicParticle::DoNothing;
        fGetLorentzFactorAction = &KSBasicParticle::DoNothing;

        //these quantities have to be recalculated:
        fGetVelocityAction = &KSBasicParticle::RecalculateVelocity;
        fGetSpeedAction = &KSBasicParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSBasicParticle::RecalculateKineticEnergy;

        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;

        return;
    }
    inline void KSAdiabaticParticle::RecalculateCyclotronFrequency() const
    {
        //The cyclotron frequency is computed from magnetic field and lorentz factor/

        fCyclotronFrequency = TMath::Abs( GetCharge() ) * GetMagneticField().Mag() / (GetMass() * GetLorentzFactor() * 2. * KSConst::Pi());

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KTrackAdiabaticStepParticle::RecalculateCyclotronFrequency";
        msg << "KTrackAdiabaticStepParticle: recalculating fCyclotronFrequency" << ret;
        msg << "[" << fCyclotronFrequency << "]" << end;
#endif

        fGetCyclotronFrequencyAction = &KSBasicParticle::DoNothing;

        return;
    }

    //****************************
    //orbital magnetic moment (mu)
    //****************************

    inline void KSAdiabaticParticle::SetOrbitalMagneticMoment( const Double_t& newMagneticMoment )
    {
        //Setting the magnetic moment changes the transverse momentum.

        fTransMomentum = TMath::Sqrt( 2. * newMagneticMoment * GetMass() * GetMagneticField().Mag() );

        //orbital magnetic moment is set to its new value
        fOrbitalMagneticMoment = newMagneticMoment;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KTrackAdiabaticStepParticle::SetOrbitalMagneticMoment";
        msg << "KTrackAdiabaticStepParticle: setting fOrbitalMagneticMoment" << ret;
        msg << "[" << fOrbitalMagneticMoment << "]" << ret;
        msg << "KTrackAdiabaticStepParticle: fTransMomentum has been recalculated" << ret;
        msg << "[" << fTransMomentum << "]" << end;
#endif

        //orbital magnetic moment is cached
        fGetOrbitalMagneticMomentAction = &KSBasicParticle::DoNothing;

        //these quantities have to be recalculated:
        fGetVelocityAction = &KSBasicParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSBasicParticle::RecalculateLorentzFactor;
        fGetSpeedAction = &KSBasicParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSBasicParticle::RecalculateKineticEnergy;

        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;

        return;
    }
    inline void KSAdiabaticParticle::RecalculateOrbitalMagneticMoment() const
    {
        //the magnetic moment is computed from the transverse momentum
        fOrbitalMagneticMoment = (fTransMomentum * fTransMomentum) / (2. * GetMass() * GetMagneticField().Mag());

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KTrackAdiabaticStepParticle::RecalculateOrbitalMagneticMoment";
        msg << "KTrackAdiabaticStepParticle: recalculating fOrbitalMagneticMoment" << ret;
        msg << "[" << fOrbitalMagneticMoment << "]" << end;
#endif

        fGetOrbitalMagneticMomentAction = &KSBasicParticle::DoNothing;

        return;
    }

    //*********************************
    //guiding center to particle vector
    //*********************************

    inline const TVector3& KSAdiabaticParticle::GetGCtoParticleVector() const
    {
        ((this)->*(fGetGCtoParticleVectorAction))();
        return fGCtoParticleVector;
    }
    inline void KSAdiabaticParticle::SetGCtoParticleVector( const TVector3& gctoParticleVector )
    {
        //fGCtoParticleVector is set to its new value
        fGCtoParticleVector = gctoParticleVector.Unit();

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KTrackAdiabaticStepParticle::GetGCtoParticleVector";
        msg << "KTrackAdiabaticStepParticle: setting fGCtoParticleVector" << ret;
        msg << "[" << fGCtoParticleVector.X() << ", " << fGCtoParticleVector.Y() << ", " << fGCtoParticleVector.Z() << "]" << end;
#endif

        //Momentum, velocity and gc-to-particle orth vector have to be recalcuated:
        fGetMomentumAction = &KSBasicParticle::RecalculateMomentum;
        fGetVelocityAction = &KSBasicParticle::RecalculateVelocity;
        fGetPolarAngleToZAction = &KSBasicParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSBasicParticle::RecalculateAzimuthalAngleToX;

        fGetGCtoParticleOrthVectorAction = &KSAdiabaticParticle::RecalculateGCtoParticleOrthVector;

        return;
    }
    inline void KSAdiabaticParticle::RecalculateGCtoParticleVector() const
    {
        //should not be called!
        return;
    }

    //********************************************
    //guiding center to particle orthogonal vector
    //********************************************

    inline const TVector3& KSAdiabaticParticle::GetGCtoParticleOrthVector() const
    {
        (this->*fGetGCtoParticleOrthVectorAction)();
        return fGCtoParticleOrthVector;
    }

    inline void KSAdiabaticParticle::SetGCtoParticleOrthVector( const TVector3& newGCtoParticleOrthVector )
    {
        //setting SetGCtoParticleOrthVector changes the vector pointing from the guiding center to the real particle position.

        fGCtoParticleVector = newGCtoParticleOrthVector.Unit().Cross( GetMagneticField().Unit() );

        //fGCtoParticleOrthVector is set to its new value
        fGCtoParticleOrthVector = newGCtoParticleOrthVector;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KTrackAdiabaticStepParticle::GetGCtoParticleOrthVector";
        msg << "KTrackAdiabaticStepParticle: setting fGCtoParticleOrthVector" << ret;
        msg << "[" << fGCtoParticleOrthVector.X() << ", " << fGCtoParticleOrthVector.Y() << ", " << fGCtoParticleOrthVector.Z() << "]" << ret;
        msg << "KTrackAdiabaticStepParticle: fPosition, fLongMomentum, fTransMomentum, and fGCtoParticleVector have been recalculated" << ret;
        msg << "[" << fGCtoParticleVector.X() << ", " << fGCtoParticleVector.Y() << ", " << fGCtoParticleVector.Z() << "]" << end;
#endif

        //gc to particle orth vector is cached
        fGetGCtoParticleOrthVectorAction = &KSAdiabaticParticle::DoNothing;

        //Momentum and velocity have to be recalcuated:
        fGetMomentumAction = &KSBasicParticle::RecalculateMomentum;
        fGetVelocityAction = &KSBasicParticle::RecalculateVelocity;
        fGetPolarAngleToZAction = &KSBasicParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSBasicParticle::RecalculateAzimuthalAngleToX;

        return;
    }
    inline void KSAdiabaticParticle::RecalculateGCtoParticleOrthVector() const
    {
        //GetGCtoParticleOrthVector is computed from the vector pointing from the guiding center to the particle and a unit vector pointing along the magnetic field.

        fGCtoParticleOrthVector = GetMagneticField().Unit().Cross( fGCtoParticleVector );

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KTrackAdiabaticStepParticle::RecalculateGCtoParticleOrthVector";
        msg << "KTrackAdiabaticStepParticle: recalculating fGCtoParticleVector" << ret;
        msg << "[" << fGCtoParticleVector.X() << ", " << fGCtoParticleVector.Y() << ", " << fGCtoParticleVector.Z() << "]" << end;
#endif

        fGetGCtoParticleOrthVectorAction = &KSAdiabaticParticle::DoNothing;

        return;
    }

} // end namespace Kassiopeia

#endif
