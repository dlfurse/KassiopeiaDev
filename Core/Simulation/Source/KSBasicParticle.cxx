#include "KSBasicParticle.h"

#include "KSParticleFactoryTable.h"

#include "KSMessage.h"

namespace Kassiopeia
{

    KSBasicParticle::KSBasicParticle( const KSBasicParticle* aParticleToClone ) :
        fStaticData( aParticleToClone->fStaticData ),

        fTime( aParticleToClone->fTime ),

        fPosition( aParticleToClone->fPosition ),
        fMomentum( aParticleToClone->fMomentum ),
        fVelocity( aParticleToClone->fVelocity ),
        fLorentzFactor( aParticleToClone->fLorentzFactor ),
        fSpeed( aParticleToClone->fSpeed ),
        fKineticEnergy( aParticleToClone->fKineticEnergy ),
        fPolarAngleToZ( aParticleToClone->fPolarAngleToZ ),
        fAzimuthalAngleToX( aParticleToClone->fAzimuthalAngleToX ),

        fGetPositionAction( aParticleToClone->fGetPositionAction ),
        fGetMomentumAction( aParticleToClone->fGetMomentumAction ),
        fGetVelocityAction( aParticleToClone->fGetVelocityAction ),
        fGetLorentzFactorAction( aParticleToClone->fGetLorentzFactorAction ),
        fGetSpeedAction( aParticleToClone->fGetSpeedAction ),
        fGetKineticEnergyAction( aParticleToClone->fGetKineticEnergyAction ),
        fGetPolarAngleToZAction( aParticleToClone->fGetPolarAngleToZAction ),
        fGetAzimuthalAngleToXAction( aParticleToClone->fGetAzimuthalAngleToXAction )
    {
    }
    KSBasicParticle::~KSBasicParticle()
    {
    }

    KSBasicParticle::KSBasicParticle() :
        fStaticData( NULL ),

        fTime( 0. ),

        fPosition( 0., 0., 0. ),
        fMomentum( 0., 0., 0. ),
        fVelocity( 0., 0., 0. ),
        fLorentzFactor( 0. ),
        fSpeed( 0. ),
        fKineticEnergy( 0. ),
        fPolarAngleToZ( 0. ),
        fAzimuthalAngleToX( 0. )
    {
        EnableAllVariables();
        DisableBasicVariables();
    }
    void KSBasicParticle::EnableAllVariables() const
    {
        fGetPositionAction = &KSBasicParticle::RecalculatePosition;
        fGetMomentumAction = &KSBasicParticle::RecalculateMomentum;
        fGetVelocityAction = &KSBasicParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSBasicParticle::RecalculateLorentzFactor;
        fGetSpeedAction = &KSBasicParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSBasicParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSBasicParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSBasicParticle::RecalculateAzimuthalAngleToX;

        return;
    }
    void KSBasicParticle::DisableBasicVariables() const
    {
        fGetPositionAction = &KSBasicParticle::DoNothing;
        fGetMomentumAction = &KSBasicParticle::DoNothing;

        return;
    }

    void KSBasicParticle::Print() const
    {
        msg = eMessage;
        msg < "KSBasicParticle::Print";
        msg << "Basic Particle State:" << ret;
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
        msg << "  pz:         " << fMomentum.Z() << end;
        return;
    }

}
