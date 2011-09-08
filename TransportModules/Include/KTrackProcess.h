#ifndef KTRACKPROCESS_H_
#define KTRACKPROCESS_H_

#include "KSProcess.h"

namespace Kassiopeia
{

    class KTrackProcess :
        public KSProcess
    {
        public:
            KTrackProcess();
            virtual ~KTrackProcess();

            //******
            //action
            //******

        public:
            virtual Bool_t ComputeStep();
            virtual Double_t ComputeTimeStep();

            //***********
            //composition
            //***********

        public:
            virtual Bool_t AddProcess( KSProcess* aSubProcess );
            virtual Bool_t RemoveProcess( KSProcess* aSubProcess );

            virtual Bool_t AddStepSize( KSStepSize* aSubStepSize );
            virtual Bool_t RemoveStepSize( KSStepSize* aSubStepSize );
    };

    inline Bool_t KTrackProcess::ComputeStep()
    {
        return kFALSE;
    }
    inline Double_t KTrackProcess::ComputeTimeStep()
    {
        return 1.e300;
    }

    inline Bool_t KTrackProcess::AddProcess( KSProcess* /*aSubProcess*/ )
    {
        return kFALSE;
    }
    inline Bool_t KTrackProcess::RemoveProcess( KSProcess* /*aSubProcess*/ )
    {
        return kFALSE;
    }

    inline Bool_t KTrackProcess::AddStepSize( KSStepSize* /*aSubStepSize*/ )
    {
        return kFALSE;
    }
    inline Bool_t KTrackProcess::RemoveStepSize( KSStepSize* /*aSubStepSize*/ )
    {
        return kFALSE;
    }


}

#endif
