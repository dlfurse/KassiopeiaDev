#include "KSElectromagneticParticle.h"

#include "KSMessage.h"

namespace Kassiopeia
{

    KSElectromagneticParticle::KSElectromagneticParticle( const KSElectromagneticParticle* aParticleToClone ) :
        KSBasicParticle( aParticleToClone ),

        fMagneticFieldCalculator( aParticleToClone->fMagneticFieldCalculator ),
        fElectricFieldCalculator( aParticleToClone->fElectricFieldCalculator ),

        fMagneticField( aParticleToClone->fMagneticField ),
        fElectricField( aParticleToClone->fElectricField ),
        fElectricPotential( aParticleToClone->fElectricPotential ),
        fGradientB( aParticleToClone->fGradientB ),
        fGradientE( aParticleToClone->fGradientE ),

        fLongMomentum( aParticleToClone->fLongMomentum ),
        fTransMomentum( aParticleToClone->fTransMomentum ),
        fLongVelocity( aParticleToClone->fLongVelocity ),
        fTransVelocity( aParticleToClone->fTransVelocity ),
        fPolarAngleToB( aParticleToClone->fPolarAngleToB ),
        fCyclotronFrequency( aParticleToClone->fCyclotronFrequency ),
        fOrbitalMagneticMoment( aParticleToClone->fOrbitalMagneticMoment ),

        fGetMagneticFieldAction( aParticleToClone->fGetMagneticFieldAction ),
        fGetElectricFieldAction( aParticleToClone->fGetElectricFieldAction ),
        fGetElectricPotentialAction( aParticleToClone->fGetElectricPotentialAction ),
        fGetGradientBAction( aParticleToClone->fGetGradientBAction ),
        fGetGradientEAction( aParticleToClone->fGetGradientEAction ),

        fGetLongMomentumAction( aParticleToClone->fGetLongMomentumAction ),
        fGetTransMomentumAction( aParticleToClone->fGetTransMomentumAction ),
        fGetLongVelocityAction( aParticleToClone->fGetLongVelocityAction ),
        fGetTransVelocityAction( aParticleToClone->fGetTransVelocityAction ),
        fGetPolarAngleToBAction( aParticleToClone->fGetPolarAngleToBAction ),
        fGetCyclotronFrequencyAction( aParticleToClone->fGetCyclotronFrequencyAction ),
        fGetOrbitalMagneticMomentAction( aParticleToClone->fGetOrbitalMagneticMomentAction ),
        fGetGCPositionAction( aParticleToClone->fGetGCPositionAction )
    {
    }
    KSElectromagneticParticle::~KSElectromagneticParticle()
    {
    }

    KSElectromagneticParticle::KSElectromagneticParticle() :
        KSBasicParticle(),

        fMagneticFieldCalculator( NULL ),
        fElectricFieldCalculator( NULL ),

        fMagneticField( 0., 0., 0. ),
        fElectricField( 0., 0., 0. ),
        fElectricPotential( 0. ),
        fGradientB( 0. ),
        fGradientE( 0. ),

        fLongMomentum( 0. ),
        fTransMomentum( 0. ),
        fLongVelocity( 0. ),
        fTransVelocity( 0. ),
        fPolarAngleToB( 0. ),
        fCyclotronFrequency( 0. ),
        fOrbitalMagneticMoment( 0. ),
        fGuidingCenterPosition( 0., 0., 0. )
    {
        EnableAllVariables();
        DisableBasicVariables();
    }
    void KSElectromagneticParticle::EnableAllVariables() const
    {
        KSBasicParticle::EnableAllVariables();

        fGetMagneticFieldAction = &KSElectromagneticParticle::RecalculateMagneticField;
        fGetElectricFieldAction = &KSElectromagneticParticle::RecalculateElectricField;
        fGetElectricPotentialAction = &KSElectromagneticParticle::RecalculateElectricPotential;
        fGetGradientBAction = &KSElectromagneticParticle::RecalculateGradientB;
        fGetGradientEAction = &KSElectromagneticParticle::RecalculateGradientE;
        fGetLongMomentumAction = &KSElectromagneticParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSElectromagneticParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSElectromagneticParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSElectromagneticParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSElectromagneticParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSElectromagneticParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSElectromagneticParticle::RecalculateOrbitalMagneticMoment;

        return;
    }
    void KSElectromagneticParticle::DisableBasicVariables() const
    {
        fGetPositionAction = &KSBasicParticle::DoNothing;
        fGetMomentumAction = &KSBasicParticle::DoNothing;

        return;
    }

    void KSElectromagneticParticle::Print() const
    {
        msg = eMessage;
        msg < "KSElectromagneticParticle::Print";
        msg << "Particle State:" << ret;
        msg << "  id:         " << fStaticData->fPID << ret;
        msg << "  mass:       " << fStaticData->fMass << ret;
        msg << "  charge:     " << fStaticData->fCharge << ret;
        msg << "  total spin: " << fStaticData->fTotalSpin << ret;
        msg << "  lifetime:   " << fStaticData->fLifetime << ret;
        msg << ret;
        msg << "  x:          " << fPosition.X() << ret;
        msg << "  y:          " << fPosition.Y() << ret;
        msg << "  z:          " << fPosition.Z() << ret;
        msg << "  px:         " << fMomentum.X() << ret;
        msg << "  py:         " << fMomentum.Y() << ret;
        msg << "  pz:         " << fMomentum.Z() << eom;
        return;
    }
}
