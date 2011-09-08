#include "KTrackLorentzODE.h"

namespace Kassiopeia
{

    KTrackLorentzODE::KTrackLorentzODE() :
        KTrackODE( 7 )
    {
    }

    KTrackLorentzODE::~KTrackLorentzODE()
    {
    }

    inline void KTrackLorentzODE::CalculateDerivative()
    {
        TVector3 Velocity = fParticle->GetVelocity();
        TVector3 Force = fParticle->GetCharge() * (fParticle->GetElectricField() + Velocity.Cross( fParticle->GetMagneticField() ));

        fDerivativeArea[0] = 1.;
        fDerivativeArea[1] = Velocity.X();
        fDerivativeArea[2] = Velocity.Y();
        fDerivativeArea[3] = Velocity.Z();
        fDerivativeArea[4] = Force.X();
        fDerivativeArea[5] = Force.Y();
        fDerivativeArea[6] = Force.Z();

        return;
    }

}
