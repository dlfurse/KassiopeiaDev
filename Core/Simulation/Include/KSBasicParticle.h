#ifndef KSBASICPARTICLE_H_
#define KSBASICPARTICLE_H_

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

    class KSBasicParticle
    {
        public:
            friend class KSParticleFactory;

            void DoNothing() const;
            void ClearCache() const;

            //*********************
            //particle construction
            //*********************

        public:
            KSBasicParticle( const KSBasicParticle* aParticleToClone );
            virtual ~KSBasicParticle();

        protected:
            KSBasicParticle();

            virtual void EnableAllVariables() const;
            virtual void DisableBasicVariables() const;

            //***************
            //printing system
            //***************

        public:
            virtual void Print() const;

            //************************
            //static properties system
            //************************

        public:
            virtual const Long_t& GetPID() const;
            virtual const Double_t& GetMass() const;
            virtual const Double_t& GetCharge() const;
            virtual const Double_t& GetTotalSpin() const;
            virtual const Double_t& GetLifetime() const;

        protected:
            Long_t fPID;
            Double_t fMass;
            Double_t fCharge;
            Double_t fTotalSpin;
            Double_t fLifetime;

            //***********************
            //basic properties system
            //***********************

        public:

            //time (units are seconds)

            const Double_t& GetT() const;

            void SetT( const Double_t t );

            //position (units are meters)

            const TVector3& GetPosition() const;
            Double_t GetX() const;
            Double_t GetY() const;
            Double_t GetZ() const;

            virtual void SetPosition( const TVector3& position );
            virtual void SetPosition( const Double_t& x, const Double_t& y, const Double_t& z );
            virtual void SetX( const Double_t& x );
            virtual void SetY( const Double_t& y );
            virtual void SetZ( const Double_t& z );

            virtual void RecalculatePosition() const;

            //momentum (units are kg*m/s)

            const TVector3& GetMomentum() const;
            Double_t GetPX() const;
            Double_t GetPY() const;
            Double_t GetPZ() const;

            virtual void SetMomentum( const TVector3& momentum );
            virtual void SetMomentum( const Double_t& px, const Double_t& py, const Double_t& pz );
            virtual void SetPX( const Double_t& px );
            virtual void SetPY( const Double_t& py );
            virtual void SetPZ( const Double_t& pz );

            virtual void RecalculateMomentum() const;

            //velocity (units are m/s)

            const TVector3& GetVelocity() const;

            virtual void SetVelocity( const TVector3& velocity );

            virtual void RecalculateVelocity() const;

            //speed (units are m/s)

            const Double_t& GetSpeed() const;

            virtual void SetSpeed( const Double_t& speed );

            virtual void RecalculateSpeed() const;

            // lorentz factor (unitless)

            const Double_t& GetLorentzFactor() const;

            virtual void SetLorentzFactor( const Double_t& lorentzfactor );

            virtual void RecalculateLorentzFactor() const;

            //kinetic energy (units are eV)

            const Double_t& GetKineticEnergy() const;

            virtual void SetKineticEnergy( const Double_t& energy );

            virtual void RecalculateKineticEnergy() const;

            //polar angle of momentum vector (units are degrees)

            const Double_t& GetPolarAngleToZ() const;

            virtual void SetPolarAngleToZ( const Double_t& NewPolarAngleToZ );

            virtual void RecalculatePolarAngleToZ() const;

            //azimuthal angle of momentum vector (units are degrees)

            const Double_t& GetAzimuthalAngleToX() const;

            virtual void SetAzimuthalAngleToX( const Double_t& NewAzimuthalAngleToX );

            virtual void RecalculateAzimuthalAngleToX() const;

            //*******************
            //actual data members
            //*******************

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

            //*******************************
            //recalculation function pointers
            //*******************************

        protected:
            mutable void (KSBasicParticle::*fGetPositionAction)() const;
            mutable void (KSBasicParticle::*fGetMomentumAction)() const;
            mutable void (KSBasicParticle::*fGetVelocityAction)() const;
            mutable void (KSBasicParticle::*fGetLorentzFactorAction)() const;
            mutable void (KSBasicParticle::*fGetSpeedAction)() const;
            mutable void (KSBasicParticle::*fGetKineticEnergyAction)() const;
            mutable void (KSBasicParticle::*fGetPolarAngleToZAction)() const;
            mutable void (KSBasicParticle::*fGetAzimuthalAngleToXAction)() const;
    };

    inline void KSBasicParticle::DoNothing() const
    {
        return;
    }

    inline void KSBasicParticle::ClearCache() const
    {
        EnableAllVariables();
        DisableBasicVariables();

        return;
    }

    //*******************
    //static data getters
    //*******************

    inline const Long_t& KSBasicParticle::GetPID() const
    {
        return fPID;
    }
    inline const Double_t& KSBasicParticle::GetMass() const
    {
        return fMass;
    }
    inline const Double_t& KSBasicParticle::GetCharge() const
    {
        return fCharge;
    }
    inline const Double_t& KSBasicParticle::GetTotalSpin() const
    {
        return fTotalSpin;
    }
    inline const Double_t& KSBasicParticle::GetLifetime() const
    {
        return fLifetime;
    }

    //****
    //time
    //****

    inline void KSBasicParticle::SetT( const Double_t t )
    {
        fTime = t;
        return;
    }
    inline const Double_t& KSBasicParticle::GetT() const
    {
        return fTime;
    }

    //********
    //position
    //********

    inline const TVector3& KSBasicParticle::GetPosition() const
    {
        return fPosition;
    }
    inline Double_t KSBasicParticle::GetX() const
    {
        return fPosition.X();
    }
    inline Double_t KSBasicParticle::GetY() const
    {
        return fPosition.Y();
    }
    inline Double_t KSBasicParticle::GetZ() const
    {
        return fPosition.Z();
    }

    inline void KSBasicParticle::SetPosition( const TVector3& position )
    {
        fPosition = position;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSBasicParticle::SetPosition";
        msg << "KSBasicParticle: [" << this << "] setting fPosition" << ret;
        msg << "[" << fPosition.X() << ", " << fPosition.Y() << ", " << fPosition.Z() << "]" << end;
#endif

        return;
    }
    inline void KSBasicParticle::SetPosition( const Double_t& x, const Double_t& y, const Double_t& z )
    {
        fPosition.SetXYZ( x, y, z );

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSBasicParticle::SetPosition";
        msg << "KSBasicParticle: [" << this << "] setting fPosition" << ret;
        msg << "[" << fPosition.X() << ", " << fPosition.Y() << ", " << fPosition.Z() << "]" << end;
#endif

        return;
    }
    inline void KSBasicParticle::SetX( const Double_t& x )
    {
        fPosition.SetX( x );

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSBasicParticle::SetX";
        msg << "KSBasicParticle: [" << this << "] setting fPosition.X" << ret;
        msg << "[" << fPosition.X() << "]" << end;
#endif

        return;
    }
    inline void KSBasicParticle::SetY( const Double_t& y )
    {
        fPosition.SetY( y );

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSBasicParticle::SetY";
        msg << "KSBasicParticle: [" << this << "] setting fPosition.Y" << ret;
        msg << "[" << fPosition.Y() << "]" << end;
#endif

        return;
    }
    inline void KSBasicParticle::SetZ( const Double_t& z )
    {
        fPosition.SetZ( z );

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSBasicParticle::SetZ";
        msg << "KSBasicParticle: [" << this << "] setting fPosition.Z" << ret;
        msg << "[" << fPosition.Z() << "]" << end;
#endif

        return;
    }

    inline void KSBasicParticle::RecalculatePosition() const
    {
        //this function should not be called since position is a basic variable
        return;
    }

    //********
    //momentum
    //********

    inline const TVector3& KSBasicParticle::GetMomentum() const
    {
        return fMomentum;
    }
    inline Double_t KSBasicParticle::GetPX() const
    {
        return fMomentum.X();
    }
    inline Double_t KSBasicParticle::GetPY() const
    {
        return fMomentum.Y();
    }
    inline Double_t KSBasicParticle::GetPZ() const
    {
        return fMomentum.Z();
    }

    inline void KSBasicParticle::SetMomentum( const TVector3& momentum )
    {
        fMomentum = momentum;
#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSBasicParticle::SetMomentum";
        msg << "KSBasicParticle: [" << this << "] setting fMomentum" << ret;
        msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << end;
#endif

        //fMomentum is a native variable of this particle
        fGetVelocityAction = &KSBasicParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSBasicParticle::RecalculateLorentzFactor;
        fGetSpeedAction = &KSBasicParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSBasicParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSBasicParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSBasicParticle::RecalculateAzimuthalAngleToX;

        return;
    }

    inline void KSBasicParticle::SetMomentum( const Double_t& px, const Double_t& py, const Double_t& pz )
    {
        fMomentum.SetXYZ( px, py, pz );

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSBasicParticle::SetMomentum";
        msg << "KSBasicParticle: [" << this << "] setting fMomentum" << ret;
        msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << end;
#endif

        //fMomentum is a native variable of this particle
        fGetVelocityAction = &KSBasicParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSBasicParticle::RecalculateLorentzFactor;
        fGetSpeedAction = &KSBasicParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSBasicParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSBasicParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSBasicParticle::RecalculateAzimuthalAngleToX;

        return;
    }
    inline void KSBasicParticle::SetPX( const Double_t& px )
    {
        fMomentum.SetX( px );

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSBasicParticle::SetPX";
        msg << "KSBasicParticle: [" << this << "] setting fMomentum.X" << ret;
        msg << "[" << fMomentum.X();
#endif

        fGetVelocityAction = &KSBasicParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSBasicParticle::RecalculateLorentzFactor;
        fGetSpeedAction = &KSBasicParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSBasicParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSBasicParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSBasicParticle::RecalculateAzimuthalAngleToX;

        return;
    }
    inline void KSBasicParticle::SetPY( const Double_t& py )
    {
        fMomentum.SetY( py );

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSBasicParticle::SetPY";
        msg << "KSBasicParticle: [" << this << "] setting fMomentum.Y" << ret;
        msg << "[" << fMomentum.Y();
#endif

        fGetVelocityAction = &KSBasicParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSBasicParticle::RecalculateLorentzFactor;
        fGetSpeedAction = &KSBasicParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSBasicParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSBasicParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSBasicParticle::RecalculateAzimuthalAngleToX;

        return;
    }
    inline void KSBasicParticle::SetPZ( const Double_t& pz )
    {
        fMomentum.SetZ( pz );

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSBasicParticle::SetPZ";
        msg << "KSBasicParticle: [" << this << "] setting fMomentum.Z" << ret;
        msg << "[" << fMomentum.Z();
#endif

        fGetVelocityAction = &KSBasicParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSBasicParticle::RecalculateLorentzFactor;
        fGetSpeedAction = &KSBasicParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSBasicParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSBasicParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSBasicParticle::RecalculateAzimuthalAngleToX;

        return;
    }

    inline void KSBasicParticle::RecalculateMomentum() const
    {
        //this function should not be called since momentum is a basic variable
        return;
    }

    //********
    //velocity
    //********

    inline const TVector3& KSBasicParticle::GetVelocity() const
    {
        (this->*fGetVelocityAction)();
        return fVelocity;
    }

    inline void KSBasicParticle::SetVelocity( const TVector3& NewVelocity )
    {
        register Double_t NewSpeed = NewVelocity.Mag();
        register Double_t NewLorentzFactor = 1.0 / TMath::Sqrt( 1.0 - (NewSpeed * NewSpeed / (KSConst::C() * KSConst::C())) );

        fMomentum = GetMass() * NewLorentzFactor * NewVelocity;
        fVelocity = NewVelocity;
        fLorentzFactor = NewLorentzFactor;
        fSpeed = NewSpeed;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSBasicParticle::SetVelocity";
        msg << "KSBasicParticle: [" << this << "] setting fVelocity" << ret;
        msg << "[" << fVelocity.X() << ", " << fVelocity.Y() << ", " << fVelocity.Z() << "]" << ret;
        msg << "KSBasicParticle: [" << this << "] fMomentum has been recalculated" << ret;
        msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << ret;
        msg << "KSBasicParticle: [" << this << "] fLorentzFactor and fSpeed have been secondarily recalculated" << ret;
        msg << "[" << fLorentzFactor << "]" << ret;
        msg << "[" << fSpeed << "]" << end;
#endif

        fGetVelocityAction = &KSBasicParticle::DoNothing;
        fGetLorentzFactorAction = &KSBasicParticle::DoNothing;
        fGetSpeedAction = &KSBasicParticle::DoNothing;
        fGetKineticEnergyAction = &KSBasicParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSBasicParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSBasicParticle::RecalculateAzimuthalAngleToX;

        return;
    }

    inline void KSBasicParticle::RecalculateVelocity() const
    {
        fVelocity = (1. / (GetMass() * GetLorentzFactor())) * fMomentum;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSBasicParticle::RecalculateVelocity";
        msg << "KSBasicParticle: [" << this << "] recalculating fVelocity" << ret;
        msg << "[" << fVelocity.X() << ", " << fVelocity.Y() << ", " << fVelocity.Z() << "]" << end;
#endif

        fGetVelocityAction = &KSBasicParticle::DoNothing;

        return;
    }

    //*****
    //speed
    //*****

    inline const Double_t& KSBasicParticle::GetSpeed() const
    {
        (this->*fGetSpeedAction)();
        return fSpeed;
    }

    inline void KSBasicParticle::SetSpeed( const Double_t& NewSpeed )
    {
        register Double_t LorentzFactor = 1.0 / TMath::Sqrt( 1.0 - NewSpeed * NewSpeed / (KSConst::C() * KSConst::C()) );
        register Double_t MomentumMagnitude = GetMass() * KSConst::C() * TMath::Sqrt( LorentzFactor * LorentzFactor - 1.0 );

        fMomentum.SetMag( MomentumMagnitude );
        fLorentzFactor = LorentzFactor;
        fSpeed = NewSpeed;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSBasicParticle::SetSpeed";
        msg << "KSBasicParticle: [" << this << "] setting fSpeed" << ret;
        msg << "[" << fSpeed << "]" << ret;
        msg << "KSBasicParticle: [" << this << "] fMomentum has been recalculated" << ret;
        msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << ret;
        msg << "KSBasicParticle: [" << this << "] fLorentzFactor has been secondarily recalculated" << ret;
        msg << "[" << fLorentzFactor << "]" << end;
#endif

        fGetVelocityAction = &KSBasicParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSBasicParticle::DoNothing;
        fGetSpeedAction = &KSBasicParticle::DoNothing;
        fGetKineticEnergyAction = &KSBasicParticle::RecalculateKineticEnergy;

        return;
    }

    inline void KSBasicParticle::RecalculateSpeed() const
    {
        fSpeed = GetVelocity().Mag();

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSBasicParticle::RecalculateSpeed";
        msg << "KSBasicParticle: [" << this << "] recalculating fSpeed" << ret;
        msg << "[" << fSpeed << "]" << end;
#endif

        fGetSpeedAction = &KSBasicParticle::DoNothing;

        return;
    }

    //**************
    //lorentz factor
    //**************

    inline const Double_t& KSBasicParticle::GetLorentzFactor() const
    {
        (this->*fGetLorentzFactorAction)();
        return fLorentzFactor;
    }

    inline void KSBasicParticle::SetLorentzFactor( const Double_t& NewLorentzFactor )
    {
        register Double_t MomentumMagnitude = GetMass() * KSConst::C() * TMath::Sqrt( NewLorentzFactor * NewLorentzFactor - 1.0 );

        fMomentum.SetMag( MomentumMagnitude );
        fLorentzFactor = NewLorentzFactor;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSBasicParticle::SetLorentzFactor";
        msg << "KSBasicParticle: [" << this << "] setting fLorentzFactor" << ret;
        msg << "[" << fLorentzFactor << "]" << ret;
        msg << "KSBasicParticle: [" << this << "] fMomentum has been recalculated" << ret;
        msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << end;
#endif

        fGetVelocityAction = &KSBasicParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSBasicParticle::DoNothing;
        fGetSpeedAction = &KSBasicParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSBasicParticle::RecalculateKineticEnergy;

        return;
    }

    inline void KSBasicParticle::RecalculateLorentzFactor() const
    {
        fLorentzFactor = TMath::Sqrt( 1.0 + fMomentum.Mag2() / (GetMass() * GetMass() * KSConst::C() * KSConst::C()) );

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSBasicParticle::RecalculateLorentzFactor";
        msg << "KSBasicParticle: [" << this << "] recalculating fLorentzFactor" << ret;
        msg << "[" << fLorentzFactor << "]" << end;
#endif

        fGetLorentzFactorAction = &KSBasicParticle::DoNothing;

        return;
    }

    //**************
    //kinetic energy
    //**************

    inline const Double_t& KSBasicParticle::GetKineticEnergy() const
    {
        (this->*fGetKineticEnergyAction)();
        return fKineticEnergy;
    }

    inline void KSBasicParticle::SetKineticEnergy( const Double_t& energy )
    {
        register Double_t NewKineticEnergy_SI = energy * KSConst::Q();
        register Double_t MomentumMagnitude = (NewKineticEnergy_SI / KSConst::C()) * TMath::Sqrt( 1.0 + (2.0 * GetMass() * KSConst::C() * KSConst::C()) / NewKineticEnergy_SI );

        fMomentum.SetMag( MomentumMagnitude );
        fKineticEnergy = energy;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSBasicParticle::SetKineticEnergy";
        msg << "KSBasicParticle: [" << this << "] setting fKineticEnergy" << ret;
        msg << "[" << fKineticEnergy << "]" << ret;
        msg << "KSBasicParticle: [" << this << "] fMomentum has been recalculated" << ret;
        msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << end;
#endif

        fGetVelocityAction = &KSBasicParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSBasicParticle::RecalculateLorentzFactor;
        fGetSpeedAction = &KSBasicParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSBasicParticle::DoNothing;

        return;
    }

    inline void KSBasicParticle::RecalculateKineticEnergy() const
    {
        fKineticEnergy = fMomentum.Mag2() / ((1.0 + GetLorentzFactor()) * GetMass() * KSConst::Q());

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSBasicParticle::RecalculateKineticEnergy";
        msg << "KSBasicParticle: [" << this << "] recalculating fKineticEnergy" << ret;
        msg << "[" << fKineticEnergy << "]" << end;
#endif

        fGetKineticEnergyAction = &KSBasicParticle::DoNothing;

        return;
    }

    //***********
    //polar angle
    //***********

    inline const Double_t& KSBasicParticle::GetPolarAngleToZ() const
    {
        (this->*fGetPolarAngleToZAction)();
        return fPolarAngleToZ;
    }

    inline void KSBasicParticle::SetPolarAngleToZ( const Double_t& NewPolarAngleToZ )
    {
        register Double_t NewPolarAngleToZ_SI = (KSConst::Pi() / 180.) * NewPolarAngleToZ;
        register Double_t AzimuthalAngleToX_SI = (KSConst::Pi() / 180.) * GetAzimuthalAngleToX();
        register Double_t MomentumMagnitude = fMomentum.Mag();

        fMomentum.SetXYZ( MomentumMagnitude * TMath::Sin( NewPolarAngleToZ_SI ) * TMath::Cos( AzimuthalAngleToX_SI ), MomentumMagnitude * TMath::Sin( NewPolarAngleToZ_SI ) * TMath::Sin( AzimuthalAngleToX_SI ), MomentumMagnitude * TMath::Cos( NewPolarAngleToZ_SI ) );
        fPolarAngleToZ = NewPolarAngleToZ;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSBasicParticle::SetPolarAngleToZ";
        msg << "KSBasicParticle: [" << this << "] setting fPolarAngleToZ" << ret;
        msg << "[" << fKineticEnergy << "]" << ret;
        msg << "KSBasicParticle: [" << this << "] fMomentum has been recalculated" << ret;
        msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << end;
#endif

        fGetVelocityAction = &KSBasicParticle::RecalculateVelocity;

        return;
    }

    inline void KSBasicParticle::RecalculatePolarAngleToZ() const
    {
        fPolarAngleToZ = (180. / KSConst::Pi()) * TMath::ACos( fMomentum.Z() / fMomentum.Mag() );

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSBasicParticle::RecalculatePolarAngleToZ";
        msg << "KSBasicParticle: [" << this << "] recalculating fPolarAngleToZ";
        msg << "[" << fPolarAngleToZ << "]" << ret;
#endif

        fGetPolarAngleToZAction = &KSBasicParticle::DoNothing;

        return;
    }

    //***************
    //azimuthal angle
    //***************

    inline const Double_t& KSBasicParticle::GetAzimuthalAngleToX() const
    {
        (this->*fGetAzimuthalAngleToXAction)();
        return fAzimuthalAngleToX;
    }

    inline void KSBasicParticle::SetAzimuthalAngleToX( const Double_t& NewAzimuthalAngleToX )
    {
        register Double_t NewAzimuthalAngleToX_SI = (KSConst::Pi() / 180.) * NewAzimuthalAngleToX;
        register Double_t PolarAngleToZ_SI = (KSConst::Pi() / 180.) * GetPolarAngleToZ();
        register Double_t MomentumMagnitude = fMomentum.Mag();

        fMomentum.SetXYZ( MomentumMagnitude * TMath::Sin( PolarAngleToZ_SI ) * TMath::Cos( NewAzimuthalAngleToX_SI ), MomentumMagnitude * TMath::Sin( PolarAngleToZ_SI ) * TMath::Sin( NewAzimuthalAngleToX_SI ), MomentumMagnitude * TMath::Cos( PolarAngleToZ_SI ) );
        fAzimuthalAngleToX = NewAzimuthalAngleToX;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSBasicParticle::SetAzimuthalAngleToX";
        msg << "KSBasicParticle: [" << this << "] setting fAzimuthalAngleToX" << ret;
        msg << "[" << fKineticEnergy << "]" << ret;
        msg << "KSBasicParticle: [" << this << "] fMomentum has been recalculated" << ret;
        msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << end;
#endif

        fGetVelocityAction = &KSBasicParticle::RecalculateVelocity;

        return;
    }

    inline void KSBasicParticle::RecalculateAzimuthalAngleToX() const
    {
        register Double_t RadialComponent = TMath::Sqrt( GetMomentum().X() * GetMomentum().X() + GetMomentum().Y() * GetMomentum().Y() );
        register Double_t NewCosPhi = GetMomentum().X() / RadialComponent;

        if( GetMomentum().Y() >= 0. )
        {
            fAzimuthalAngleToX = (180. / KSConst::Pi()) * TMath::ACos( NewCosPhi );
        }
        else
        {
            fAzimuthalAngleToX = (180. / KSConst::Pi()) * (2. - TMath::ACos( NewCosPhi ));
        }

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KSBasicParticle::RecalculateAzimuthalAngleToX";
        msg << "KSBasicParticle: [" << this << "] recalculating fAzimuthalAngleToX" << ret;
        msg << "[" << fAzimuthalAngleToX << "]" << end;
#endif

        fGetAzimuthalAngleToXAction = &KSBasicParticle::DoNothing;

        return;
    }

}

#endif
