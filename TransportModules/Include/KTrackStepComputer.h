#ifndef KTRACKSTEPCOMPUTER_H_
#define KTRACKSTEPCOMPUTER_H_

#include "KSTransportProcess.h"

#include "KSList.h"
#include "KSProcess.h"
#include "KSStepSize.h"

namespace Kassiopeia
{

    class KSRootProcess;

    class KMathCompositeODE;
    class KMathODESolver;

    class KTrackParticle;
    class KTrackError;

    class KTrackStepComputer :
        public KSTransportProcess
    {
        public:
            KTrackStepComputer( KMathODESolver* anODESolver, KMathCompositeODE* aCompositeODE, KTrackParticle* anInitialParticle, Double_t* anInitialParticleData, KTrackParticle* anActiveParticle, Double_t* anActiveParticleData, KTrackParticle* aFinalParticle, Double_t* aFinalParticleData, KTrackError* anError, Double_t* anErrorData );
            virtual ~KTrackStepComputer();

            //*****
            //state
            //*****

        protected:
            virtual Bool_t EnableAction();
            virtual Bool_t DisableAction();

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
            virtual Bool_t AddParent( KSProcess* aParentProcess );

            virtual Bool_t AddProcess( KSProcess* aSubProcess );
            virtual Bool_t RemoveProcess( KSProcess* aSubProcess );

            virtual Bool_t AddStepSize( KSStepSize* aSubStepSize );
            virtual Bool_t RemoveStepSize( KSStepSize* aSubStepSize );

        protected:
            enum
            {
                eMaxSubObjects = 64
            };
            KSRootProcess* fParent;
            KSList< KSProcess > fSubProcesses;
            KSList< KSStepSize > fSubStepSizes;

            //*************
            //configuration
            //*************

        public:
            KMathCompositeODE* GetCompositeODE();

            KTrackParticle* GetInitialParticle();
            KTrackParticle* GetActiveParticle();
            KTrackParticle* GetFinalParticle();

            KTrackError* GetError();

        protected:
            KMathODESolver* fODESolver;
            KMathCompositeODE* fODE;

            KTrackParticle* fInitialParticle;
            Double_t* fInitialParticleData;
            KTrackParticle* fActiveParticle;
            Double_t* fActiveParticleData;
            KTrackParticle* fFinalParticle;
            Double_t* fFinalParticleData;

            KTrackError* fError;
            Double_t* fErrorData;
    };

    inline KMathCompositeODE* KTrackStepComputer::GetCompositeODE()
    {
        return fODE;
    }

    inline KTrackParticle* KTrackStepComputer::GetInitialParticle()
    {
        return fInitialParticle;
    }
    inline KTrackParticle* KTrackStepComputer::GetActiveParticle()
    {
        return fActiveParticle;
    }
    inline KTrackParticle* KTrackStepComputer::GetFinalParticle()
    {
        return fFinalParticle;
    }
    inline KTrackError* KTrackStepComputer::GetError()
    {
        return fError;
    }

}

#endif
