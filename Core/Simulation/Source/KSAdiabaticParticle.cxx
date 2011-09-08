#include "KSAdiabaticParticle.h"

#include "KSMessage.h"

namespace Kassiopeia
{

    KSAdiabaticParticle::KSAdiabaticParticle() :
        KSElectromagneticParticle(),

        fGCtoParticleVector( 0., 0., 0. ),
        fGCtoParticleOrthVector( 0., 0., 0. )
    {
        EnableAllVariables();
        DisableBasicVariables();
    }
    KSAdiabaticParticle::KSAdiabaticParticle( const KSAdiabaticParticle* aParticleToClone ) :
        KSElectromagneticParticle( aParticleToClone ),

        fGCtoParticleVector( aParticleToClone->fGCtoParticleVector ),
        fGCtoParticleOrthVector( aParticleToClone->fGCtoParticleOrthVector ),

        fGetGCtoParticleVectorAction( aParticleToClone->fGetGCtoParticleVectorAction ),
        fGetGCtoParticleOrthVectorAction( aParticleToClone->fGetGCtoParticleOrthVectorAction )
    {
    }
    KSAdiabaticParticle::~KSAdiabaticParticle()
    {
    }

    void KSAdiabaticParticle::EnableAllVariables() const
    {
        KSElectromagneticParticle::EnableAllVariables();

        fGetGCtoParticleVectorAction = &KSAdiabaticParticle::RecalculateGCtoParticleVector;
        fGetGCtoParticleOrthVectorAction = &KSAdiabaticParticle::RecalculateGCtoParticleOrthVector;

        return;
    }

    void KSAdiabaticParticle::DisableBasicVariables() const
    {
        fGetPositionAction = &KSBasicParticle::DoNothing;
        fGetLongMomentumAction = &KSBasicParticle::DoNothing;
        fGetTransMomentumAction = &KSBasicParticle::DoNothing;
        fGetGCtoParticleVectorAction = &KSBasicParticle::DoNothing;

        return;
    }

    void KSAdiabaticParticle::Print() const
    {
        msg = eMessage;
        msg < "KSAdiabaticParticle::Print";
        msg << "Particle State:" << ret;
        msg << "  id:         " << fStaticData->fPID << ret;
        msg << "  mass:       " << fStaticData->fMass << ret;
        msg << "  charge:     " << fStaticData->fCharge << ret;
        msg << "  total spin: " << fStaticData->fTotalSpin << ret;
        msg << "  lifetime:   " << fStaticData->fLifetime << ret;
        msg << ret;
        msg << "  gc x:       " << fPosition.X() << ret;
        msg << "  gc y:       " << fPosition.Y() << ret;
        msg << "  gc z:       " << fPosition.Z() << ret;
        msg << "  gc-to-p x:  " << fGCtoParticleVector.X() << ret;
        msg << "  gc-to-p y:  " << fGCtoParticleVector.Y() << ret;
        msg << "  gc-to-p z:  " << fGCtoParticleVector.Z() << ret;
        msg << "  p long:     " << fLongMomentum << ret;
        msg << "  p trans:     " << fTransMomentum << ret;
        return;
    }

} /* namespace Kassiopeia */
