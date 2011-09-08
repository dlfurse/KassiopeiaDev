/*
 * KSBasicParticleInterface.h
 *
 * created on: Aug 8, 2011
 * author: dlfurse
 */

#ifndef KSBASICPARTICLEINTERFACE_H_
#define KSBASICPARTICLEINTERFACE_H_

namespace Kassiopeia
{

    class KSBasicParticleInterface
    {
        public:
            KSBasicParticleInterface();
            virtual ~KSBasicParticleInterface();

            //*****************
            //static properties
            //*****************

        public:
            virtual const Long_t& GetPID() const;
            virtual const Double_t& GetMass() const;
            virtual const Double_t& GetCharge() const;
            virtual const Double_t& GetTotalSpin() const;
            virtual const Double_t& GetLifetime() const;


            //******************
            //dynamic properties
            //******************

        public:

            //time (units are seconds)

            virtual const Double_t& GetT() const = 0;

            virtual void SetT( const Double_t t ) = 0;

            //position (units are meters)

            virtual const TVector3& GetPosition() const = 0;
            virtual Double_t GetX() const = 0;
            virtual Double_t GetY() const = 0;
            virtual Double_t GetZ() const = 0;

            virtual void SetPosition( const TVector3& position ) = 0;
            virtual void SetPosition( const Double_t& x, const Double_t& y, const Double_t& z ) = 0;
            virtual void SetX( const Double_t& x ) = 0;
            virtual void SetY( const Double_t& y ) = 0;
            virtual void SetZ( const Double_t& z ) = 0;

            //momentum (units are kg*m/s)

            virtual const TVector3& GetMomentum() const = 0;
            virtual Double_t GetPX() const = 0;
            virtual Double_t GetPY() const = 0;
            virtual Double_t GetPZ() const = 0;

            virtual void SetMomentum( const TVector3& momentum ) = 0;
            virtual void SetMomentum( const Double_t& px, const Double_t& py, const Double_t& pz ) = 0;
            virtual void SetPX( const Double_t& px ) = 0;
            virtual void SetPY( const Double_t& py ) = 0;
            virtual void SetPZ( const Double_t& pz ) = 0;

            //velocity (units are m/s)

            virtual const TVector3& GetVelocity() const = 0;

            virtual void SetVelocity( const TVector3& velocity ) = 0;

            //speed (units are m/s)

            virtual const Double_t& GetSpeed() const = 0;

            virtual void SetSpeed( const Double_t& speed ) = 0;

            // lorentz factor (unitless)

            virtual const Double_t& GetLorentzFactor() const = 0;

            virtual void SetLorentzFactor( const Double_t& lorentzfactor ) = 0;

            //kinetic energy (units are eV)

            virtual const Double_t& GetKineticEnergy() const = 0;

            virtual void SetKineticEnergy( const Double_t& energy ) = 0;

            //polar angle of momentum vector (units are degrees)

            virtual const Double_t& GetPolarAngleToZ() const = 0;

            virtual void SetPolarAngleToZ( const Double_t& NewPolarAngleToZ ) = 0;

            //azimuthal angle of momentum vector (units are degrees)

            virtual const Double_t& GetAzimuthalAngleToX() const  = 0;

            virtual void SetAzimuthalAngleToX( const Double_t& NewAzimuthalAngleToX ) = 0;
    };

} /* namespace Kassiopeia */
#endif /* KSBASICPARTICLEINTERFACE_H_ */
