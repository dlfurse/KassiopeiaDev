#include "KSParticleFactory.h"

#include "KSParticleFactoryTable.h"

namespace Kassiopeia
{

    KSParticleFactory::KSParticleFactory( const Long_t pid, const Double_t mass, const Double_t charge, const Double_t totalspin, const Double_t lifetime ) :
        fPID( pid ),
        fMass( mass ),
        fCharge( charge ),
        fTotalSpin( totalspin ),
        fLifetime( lifetime )
    {
        KSParticleFactoryTable::GetInstance()->Register( this );
    }
    KSParticleFactory::~KSParticleFactory()
    {
    }

    Long_t KSParticleFactory::GetPID() const
    {
        return fPID;
    }

    KSParticle* KSParticleFactory::Build() const
    {
        KSParticle* NewParticle = new KSParticle();

        NewParticle->fPID = &fPID;
        NewParticle->fMass = &fMass;
        NewParticle->fCharge = &fCharge;
        NewParticle->fTotalSpin = &fTotalSpin;
        NewParticle->fLifetime = &fLifetime;

        return NewParticle;
    }

}
