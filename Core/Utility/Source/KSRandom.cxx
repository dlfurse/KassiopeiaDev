#include "KSRandom.h"

/*
 Class: KSRandom
 Author: N. Oblath

 For full class documentation: KSRandom.h

 Revision History
 Date       Name          Brief description
 -----------------------------------------------
 08/12/09   N. Oblath     First version
 13/01/10   N. Oblath     Added assignment of gRandom
 25/03/10   N. Oblath     Implemented Kassiopeia namespaces
 01/07/10   N. Oblath     Renamed to KSRandom; typdefed to KRandom for backwards compatibility
 18/08/10   N. Oblath     Added gKSRandom pointer

 */

namespace Kassiopeia
{

    KSRandom* KSRandom::GetInstance( Int_t aSeed )
    {
        if( !fInstance )
        {
            fInstance = new KSRandom();
            fRandom = new TRandom3( aSeed );
            gRandom = fRandom;
        }
        return fInstance;
    }

    KSRandom::KSRandom()
    {
    }
    KSRandom::~KSRandom()
    {
    }

    KSRandom* KSRandom::fInstance = NULL;
    TRandom* KSRandom::fRandom = NULL;

} // end Kassiopeia namespace
