#ifndef KSPROCESS_H_
#define KSPROCESS_H_

#include "Rtypes.h"

#include <string>
using std::string;

namespace Kassiopeia
{

    class KSStepSize;

    class KSProcess
    {
        public:
            KSProcess();
            virtual ~KSProcess();

            //**************
            //identification
            //**************

        public:
            void SetName( const string& aName );
            const string& GetName() const;

        private:
            string fName;

            //*****
            //state
            //*****

        public:
            Bool_t Enable();
            Bool_t Disable();

            Bool_t IsEnabled();
            Bool_t IsDisabled();

        protected:
            virtual Bool_t EnableAction() = 0;
            virtual Bool_t DisableAction() = 0;

            typedef enum
            {
                eEnabled, eDisabled
            } State;
            State fState;

            //******
            //action
            //******

        public:
            virtual Bool_t ComputeStep() = 0;
            virtual Double_t ComputeTimeStep() = 0;

            //***********
            //composition
            //***********

        public:
            virtual Bool_t AddParent( KSProcess* aParentProcess ) = 0;

            virtual Bool_t AddProcess( KSProcess* aSubProcess ) = 0;
            virtual Bool_t RemoveProcess( KSProcess* aSubProcess ) = 0;

            virtual Bool_t AddStepSize( KSStepSize* aSubStepSize ) = 0;
            virtual Bool_t RemoveStepSize( KSStepSize* aSubStepSize ) = 0;
    };

    inline void KSProcess::SetName( const string& aName )
    {
        fName = aName;
        return;
    }
    inline const string& KSProcess::GetName() const
    {
        return fName;
    }

    inline Bool_t KSProcess::Enable()
    {
        if( fState == eDisabled )
        {
            if( EnableAction() == kTRUE )
            {
                fState = eEnabled;
                return kTRUE;
            }
        }
        return kFALSE;
    }
    inline Bool_t KSProcess::Disable()
    {
        if( fState == eEnabled )
        {
            if( DisableAction() == kTRUE )
            {
                fState = eDisabled;
                return kTRUE;
            }
        }
        return kFALSE;
    }
    inline Bool_t KSProcess::IsEnabled()
    {
        if( fState == eEnabled )
        {
            return kTRUE;
        }
        return kFALSE;
    }
    inline Bool_t KSProcess::IsDisabled()
    {
        if( fState == eDisabled )
        {
            return kTRUE;
        }
        return kFALSE;
    }
}

#endif
