#ifndef KSELECTROMAGNETICPARTICLEINTERFACE_H_
#define KSELECTROMAGNETICPARTICLEINTERFACE_H_

#include "KSBasicParticleInterface.h"

namespace Kassiopeia
{

    class KSElectromagneticParticleInterface :
        public KSBasicParticleInterface
    {
        public:
            KSElectromagneticParticleInterface();
            virtual ~KSElectromagneticParticleInterface();

            //magnetic field (units are tesla)

            virtual const TVector3& GetMagneticField() const = 0;

            virtual void SetMagneticField( const TVector3& ) = 0;

            //electric field (units are volt/meter)

            virtual const TVector3& GetElectricField() const = 0;

            virtual void SetElectricField( const TVector3& ) = 0;

            //electric potential (units are volt)

            virtual const Double_t& GetElectricPotential() const = 0;

            virtual void SetElectricPotential( const Double_t& ) = 0;

            //gradient of magnetic field (units are tesla/meter)

            virtual const Double_t& GetGradientB( const TVector3& ) const = 0;

            virtual void SetGradientB( const Double_t& ) = 0;

            //gradient of electric field (units are volt/meter^2)

            virtual const Double_t& GetGradientE( const TVector3& ) const = 0;

            virtual void SetGradientE( const Double_t& ) = 0;

            //longitudinal momentum (units are kg*m/s)

            virtual const Double_t& GetLongMomentum() const = 0;

            virtual void SetLongMomentum( const Double_t& ) = 0;

            //transverse momentum (units are kg*m/s)

            virtual const Double_t& GetTransMomentum() const = 0;

            virtual void SetTransMomentum( const Double_t& ) = 0;

            //longitudinal velocity (units are m/s)

            virtual const Double_t& GetLongVelocity() const = 0;

            virtual void SetLongVelocity( const Double_t& ) = 0;

            //transverse velocity (units are m/s)

            virtual const Double_t& GetTransVelocity() const = 0;

            virtual void SetTransVelocity( const Double_t& ) = 0;

            //polar angle to b (units are degrees)

            virtual const Double_t& GetPolarAngleToB() const = 0;

            virtual void SetPolarAngleToB( const Double_t& ) = 0;

            //cyclotron frequency (units are 1/s)

            virtual const Double_t& GetCyclotronFrequency() const = 0;

            virtual void SetCyclotronFrequency( const Double_t& ) = 0;

            //orbital magnetic moment (units are A*m^2)

            virtual const Double_t& GetOrbitalMagneticMoment() const = 0;

            virtual void SetOrbitalMagneticMoment( const Double_t& ) = 0;
    };

} /* namespace Kassiopeia */

#endif /* KSELECTROMAGNETICPARTICLEINTERFACE_H_ */
