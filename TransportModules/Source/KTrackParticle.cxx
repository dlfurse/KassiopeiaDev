#include "KTrackParticle.h"

namespace Kassiopeia
{

    KTrackParticle::KTrackParticle() :
        fData( NULL ),
        fParticle( NULL ),
        fMagneticFieldCalculator( NULL ),
        fElectricFieldCalculator( NULL ),

        fPosition( 0., 0., 0. ),
        fMomentum( 0., 0., 0. ),
        fVelocity( 0., 0., 0. ),
        fLorentzFactor( 0. ),
        fKineticEnergy( 0. ),

        fMagneticField( 0., 0., 0. ),
        fElectricField( 0., 0., 0. ),
        fElectricPotential( 0. ),
        fGradientB( 0. ),
        fGradientE( 0. ),

        fLongMomentum( 0. ),
        fTransMomentum( 0. ),
        fLongVelocity( 0. ),
        fTransVelocity( 0. ),
        fCyclotronFrequency( 0. ),
        fOrbitalMagneticMoment( 0. )
    {
    }
    KTrackParticle::~KTrackParticle()
    {
    }

    Double_t KTrackParticle::fMass = 0.;
    Double_t KTrackParticle::fCharge = 0.;

} /* namespace Kassiopeia */
