#ifndef KSROOTPROCESS_H_
#define KSROOTPROCESS_H_

#include "KSProcess.h"

namespace Kassiopeia
{

    class KSStep;
    class KSTransportProcess;
    class KSDiscreteProcess;

    class KSRootProcess :
        public KSProcess
    {
            //*********
            //singleton
            //*********

        public:
            static KSRootProcess* GetInstance();
            virtual ~KSRootProcess();

        private:
            KSRootProcess();
            static KSRootProcess* fInstance;

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

        private:
            enum
            {
                eMaxSubprocesses = 32
            };
            KSTransportProcess* fTransportProcess;

            KSDiscreteProcess* fDiscreteProcesses[eMaxSubprocesses];
            size_t fEndDiscreteProcess;
            size_t fCurrentDiscreteProcess;

            //*************
            //configuration
            //*************

        public:
            void SetStep( KSStep* aStep );
            void SetTimeStep( const Double_t& aTimeStep );
            void SetTimeCompression( const Double_t& aTimeCompression );

            KSStep* GetStep() const;
            const Double_t& GetTimeStep() const;
            const Double_t& GetTimeCompression() const;

        private:
            KSStep* fCurrentStep;
            Double_t fCurrentTimeStep;
            Double_t fCurrentTimeCompression;
    };

    inline void KSRootProcess::SetStep( KSStep* aStep )
    {
        fCurrentStep = aStep;
        return;
    }
    inline void KSRootProcess::SetTimeStep( const Double_t& aTimeStep )
    {
        fCurrentTimeStep = aTimeStep;
        return;
    }
    inline void KSRootProcess::SetTimeCompression( const Double_t& aTimeCompression )
    {
        fCurrentTimeCompression = aTimeCompression;
        return;
    }

    inline KSStep* KSRootProcess::GetStep() const
    {
        return fCurrentStep;
    }
    inline const Double_t& KSRootProcess::GetTimeStep() const
    {
        return fCurrentTimeStep;
    }
    inline const Double_t& KSRootProcess::GetTimeCompression() const
    {
        return fCurrentTimeCompression;
    }

}

#endif
