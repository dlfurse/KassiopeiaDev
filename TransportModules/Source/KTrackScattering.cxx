#include "KTrackScattering.h"

#include "KSRootProcess.h"
#include "KSStep.h"
#include "KSParticle.h"

#include "DensityCalculator.h"

namespace Kassiopeia
{

    KTrackScattering::KTrackScattering() :
        KSDiscreteProcess(),
        fInteraction("NONE"),
        fSpecies("NONE"),
        fParent( NULL ),
        fInitialParticle( NULL ),
        fFinalParticle( NULL ),
        fSubStepSizes(),
        fDensityCalculator( NULL ),
        fScatteringProbability(0.),
        fInitialCrossSection(0.),
        fGetInitialCrossSectionPtr(&KTrackScattering::GetInitialCrossSection_Recalculate),
        fFinalCrossSection(0.),
        fGetFinalCrossSectionPtr(&KTrackScattering::GetFinalCrossSection_Recalculate)
    {
    }

    KTrackScattering::~KTrackScattering()
    {
    }

    Bool_t KTrackScattering::AddParent( KSProcess* aParentProcess )
    {
        KSRootProcess* RootProcess = NULL;
        RootProcess = dynamic_cast< KSRootProcess* >( aParentProcess );
        if( RootProcess != NULL )
        {
            fParent = RootProcess;
            return kTRUE;
        }
        return kFALSE;
    }

    Bool_t KTrackScattering::EnableAction()
    {
        fInitialParticle = fParent->GetStep()->GetInitialParticle();
        fFinalParticle = fParent->GetStep()->GetFinalParticle();
        fGetInitialCrossSectionPtr = &KTrackScattering::GetInitialCrossSection_Recalculate;
        fGetFinalCrossSectionPtr = &KTrackScattering::GetFinalCrossSection_Recalculate;
        return kTRUE;
    }
    Bool_t KTrackScattering::DisableAction()
    {
        fInitialParticle = NULL;
        fFinalParticle = NULL;
        return kTRUE;
    }

    Double_t KTrackScattering::ComputeTimeStep()
    {
        return fSubStepSizes.SmallestOfAll( &KSStepSize::ComputeTimeStep );
    }

    Double_t& KTrackScattering::ComputeProbability()
    {
        fScatteringProbability = GetScatteringProbability();
        return fScatteringProbability;
    }

    Double_t KTrackScattering::GetScatteringProbability() const
    {
        Double_t pathlength = fParent->GetStep()->GetPathLength();
        Double_t averageDensity = ( fDensityCalculator->GetDensity(fInitialParticle->GetPosition())
                + fDensityCalculator->GetDensity(fFinalParticle->GetPosition()) )/2.0;
        Double_t averageCrossSection = (GetInitialCrossSection() + GetFinalCrossSection())/2.0;
        Double_t totalProb = pathlength * averageDensity * averageCrossSection;

        return totalProb;
    }

    Double_t KTrackScattering::GetDiffScatteringProbability() const
    {
        Double_t density = fDensityCalculator->GetDensity(fInitialParticle->GetPosition());
        Double_t crossSection = GetInitialCrossSection();
        Double_t diffProb = density * crossSection;
        return diffProb;
    }

    Double_t KTrackScattering::GetInitialCrossSection() const
    {
        return (this->*fGetInitialCrossSectionPtr)();
    }

    Double_t KTrackScattering::GetInitialCrossSection_Cached() const
    {
        return fInitialCrossSection;
    }

    Double_t KTrackScattering::GetFinalCrossSection() const
    {
        return (this->*fGetFinalCrossSectionPtr)();
    }

    Double_t KTrackScattering::GetFinalCrossSection_Cached() const
    {
        return fFinalCrossSection;
    }

} /* namespace Kassiopeia */

