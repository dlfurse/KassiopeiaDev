#ifndef KSSTEPSIZE_H_
#define KSSTEPSIZE_H_

#include "Rtypes.h"

#include <string>
using std::string;

namespace Kassiopeia
{

    class KSProcess;

    class KSStepSize
    {
        public:
            KSStepSize();
            virtual ~KSStepSize();

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
            virtual Double_t ComputeTimeStep() = 0;
            virtual Bool_t ComputeCheck() = 0;

            //***********
            //composition
            //***********

        public:
            virtual Bool_t AddParent( KSProcess* aParentProcess ) = 0;

    };

    inline void KSStepSize::SetName( const string& aName )
    {
        fName = aName;
        return;
    }
    inline const string& KSStepSize::GetName() const
    {
        return fName;
    }

    inline Bool_t KSStepSize::Enable()
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
    inline Bool_t KSStepSize::Disable()
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
    inline Bool_t KSStepSize::IsEnabled()
    {
        if( fState == eEnabled )
        {
            return kTRUE;
        }
        return kFALSE;
    }
    inline Bool_t KSStepSize::IsDisabled()
    {
        if( fState == eDisabled )
        {
            return kTRUE;
        }
        return kFALSE;
    }

}

#endif
