// $Id$

/*
 Class: KSTrack
 Author: N. Oblath

 For full class documentation: KSTrack.h

 Revision History
 Date         Name          Brief description
 -----------------------------------------------
 30/04/2010   N. Oblath     First version

 */

#include "KSTrack.h"

#include "KSParticle.h"
#include "KSQueue.h"

namespace Kassiopeia
{

    KSTrack::KSTrack() :
        fEventId( -1 ),
        fTrackId( -1 ),
        fParentTrackId( -1 ),
        fPrimaryTrackId( -1 ),
        fCreationName( "" ),
        fExitName( "" ),
        fTotalSteps( 0 ),
        fTotalSecondaries( 0 ),
        fTotalLength( 0. ),
        fTotalTime( 0. ),
        fTotalRadiationDeltaE( 0. ),
        fTotalScatteringDeltaE( 0. ),
        fTotalDecayDeltaE( 0. ),
        fInitialParticle( NULL ),
        fFinalParticle( NULL ),
        fSecondaryQueue( new KSQueue< KSTrack* >() )
    {
    }

    KSTrack::~KSTrack()
    {
        if( fInitialParticle != 0 )
        {
            delete fInitialParticle;
            fInitialParticle = 0;
        }

        if( fSecondaryQueue != NULL )
        {
            delete fSecondaryQueue;
            fSecondaryQueue = NULL;
        }
    }

} // end Kassiopeia namespace
