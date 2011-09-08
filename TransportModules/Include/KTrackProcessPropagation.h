#ifndef KTRACKPROPAGATIONPROCESS_H_
#define KTRACKPROPAGATIONPROCESS_H_

#include "KTrackProcess.h"

namespace Kassiopeia
{

    class KTrackStepComputer;
    class KTrackODE;
    class KTrackLorentzODE;

    class KTrackProcessPropagation :
        public KTrackProcess
    {
        public:
            KTrackProcessPropagation();
            virtual ~KTrackProcessPropagation();

            //*****
            //state
            //*****

        protected:
            virtual Bool_t EnableAction();
            virtual Bool_t DisableAction();

            //***********
            //composition
            //***********

        public:
            virtual Bool_t AddParent( KSProcess* aParent );

        private:
            KTrackStepComputer* fParent;
            KTrackODE* fActiveTerm;

            KTrackLorentzODE* fExactTerm;
    };

}

#endif
