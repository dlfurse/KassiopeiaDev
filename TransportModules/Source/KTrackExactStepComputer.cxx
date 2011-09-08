#include "KTrackExactStepComputer.h"

#include "KMathCompositeODE.h"
#include "KTrackExactParticle.h"
#include "KTrackExactError.h"

namespace Kassiopeia
{

    KTrackExactStepComputer::KTrackExactStepComputer( KMathODESolver* aSolver ) :
        KTrackStepComputer( aSolver, new KMathCompositeODE( 7 ), new KTrackExactParticle(), new Double_t[7](), new KTrackExactParticle(), new Double_t[7](), new KTrackExactParticle(), new Double_t[7](), new KTrackExactError(), new Double_t[7]() )
    {
    }

    KTrackExactStepComputer::~KTrackExactStepComputer()
    {
    }

}
