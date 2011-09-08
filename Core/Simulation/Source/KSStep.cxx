#include "KSStep.h"

namespace Kassiopeia
{

    KSStep::KSStep() :
        fTrackId( -1 ),
        fStepId( -1 ),
        fElapsedLength( 0. ),
        fElapsedTime( 0. ),
        fRadiationOccurred( kFALSE ),
        fRadiationDeltaE( 0. ),
        fScatteringOccurred( kFALSE ),
        fScatteringDeltaE( 0. ),
        fDecayOccurred( kFALSE ),
        fDecayDeltaE( 0. ),
        fInitialParticle( NULL ),
        fFinalParticle( NULL )
    {
    }

    KSStep::~KSStep()
    {
    }

}
