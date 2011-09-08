#include "KSParticleFactory.h"

namespace Kassiopeia
{
    // A "ghost" particle
    static const KSParticleFactory sGhostFactory( 0, -1., 0., 0., 0. );

    //electron
    static const KSParticleFactory sElectronFactory( 11, 9.1093826e-31, -1.60217653e-19, 0.5, -1.0 );

    //positron
    static const KSParticleFactory sPositronFactory( -11, 9.1093826e-31, 1.60217653e-19, 0.5, -1.0 );

    //muon
    static const KSParticleFactory sMuMinusFactory( 12, 1.88353131e-28, -1.60217653e-19, 0.5, 2.19703e-6 );

    //anti-muon
    static const KSParticleFactory sMuPlusFactory( -12, 1.88353131e-28, 1.60217653e-19, 0.5, 2.19703e-6 );

    //proton
    static const KSParticleFactory sProtonFactory( 2212, 1.67262158e-27, 1.60217653e-19, 0.5, -1.0 );

    //anti-proton
    static const KSParticleFactory sAntiProtonFactory( -2212, 1.67262158e-27, -1.60217653e-19, 0.5, -1.0 );

}
