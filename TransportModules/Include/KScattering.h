#ifndef KSCATTERING_H_
#define KSCATTERING_H_

#include "KSDiscreteProcess.h"
#include "KSStepSize.h"
#include "KSList.h"



namespace Kassiopeia
{
    class KSRootProcess;
    class KSParticle;
    class DensityCalculator;

    class KScattering:
        public KSDiscreteProcess
    {
        public:
            KScattering();
            virtual ~KScattering();

            //**************
            //identification
            //**************
        public:
            const string GetSpecies() const;
            const string GetInteraction() const;

        protected:
            string fInteraction;
            string fSpecies;

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
            virtual Bool_t AddParent( KSProcess* aParentProcess );

            virtual Bool_t AddStepSize( KSStepSize* aSubStepSize );
            virtual Bool_t RemoveStepSize( KSStepSize* aSubStepSize );

            void SetSpecies( const string& species );
            void SetDensityCalculator( DensityCalculator* const denscal );

        protected:
            KSRootProcess* fParent;
            KSParticle* fInitialParticle;
            KSParticle* fFinalParticle;
            KSList< KSStepSize > fSubStepSizes;
            DensityCalculator* fDensityCalculator;

            //******
            //action
            //******

        public:
            virtual Double_t ComputeTimeStep();
            virtual Bool_t Execute() = 0;
            virtual Double_t& ComputeProbability();
            void UpdateParticleMomentum(const Double_t& ke_SI, const Double_t& theta, const Double_t& phi); // updates final particle momentum according to parameters given.  ke_SI is the new energy in SI UNITS, theta is the angle to the previous momentum in DEGREES, phi is the angle from the vector normal to the plane formed by the previous momentum and the z-axis in DEGREES

            Double_t GetScatteringProbability() const;
            Double_t GetDiffScatteringProbability() const;
            Double_t GetInitialCrossSection() const;
            Double_t GetFinalCrossSection() const;

        protected:
            Double_t fScatteringProbability;

            mutable Double_t fInitialCrossSection;
            mutable Double_t (KScattering::*fGetInitialCrossSectionPtr)() const;
            virtual Double_t GetInitialCrossSection_Recalculate() const = 0;
            Double_t GetInitialCrossSection_Cached() const;

            mutable Double_t fFinalCrossSection;
            mutable Double_t (KScattering::*fGetFinalCrossSectionPtr)() const;
            virtual Double_t GetFinalCrossSection_Recalculate() const = 0;
            Double_t GetFinalCrossSection_Cached() const;
    };

    inline const string KScattering::GetInteraction() const
    {
        return fInteraction;
    }
    inline void KScattering::SetSpecies( const string& species )
    {
        fSpecies = species;
        return;
    }
    inline const string KScattering::GetSpecies() const
    {
        return fSpecies;
    }
    inline void KScattering::SetDensityCalculator( DensityCalculator* const denscal )
    {
        fDensityCalculator = denscal;
    }
    Bool_t KScattering::AddStepSize( KSStepSize* aSubStepSize )
    {
        if( (aSubStepSize->AddParent( this ) == kTRUE) && (fSubStepSizes.AddElement( aSubStepSize ) != -1) )
        {
            if( IsEnabled() )
            {
                aSubStepSize->Enable();
            }
            return kTRUE;
        }
        return kFALSE;
    }
    Bool_t KScattering::RemoveStepSize( KSStepSize* aSubStepSize )
    {
        if( fSubStepSizes.RemoveElement( aSubStepSize ) != -1 )
        {
            if( IsEnabled() )
            {
                aSubStepSize->Disable();
            }
        }
        return kTRUE;
    }


}

#endif /* KSCATTERING_H_ */
