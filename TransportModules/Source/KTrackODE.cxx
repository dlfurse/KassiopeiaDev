#include "KTrackODE.h"

namespace Kassiopeia
{

    KTrackODE::KTrackODE( const size_t& aDimension ) :
        KMathODE(aDimension),
        fParticle( NULL )
    {
    }

    KTrackODE::~KTrackODE()
    {
    }

}
