#include "KTrackScatteringElastic.h"
#include "KScatterBasicElasticCalculatorFerenc.h"
#include "KSParticle.h"

namespace Kassiopeia
{

    KTrackScatteringElastic::KTrackScatteringElastic() :
        KTrackScattering(),
        fElasticCalculator(new KScatterBasicElasticCalculatorFerenc())
    {
        fInteraction = string("Elastic");
    }

    KTrackScatteringElastic::~KTrackScatteringElastic()
    {
    }

    Double_t KTrackScatteringElastic::GetInitialCrossSection_Recalculate() const
    {
        fInitialCrossSection =  fElasticCalculator->sigmael(fInitialParticle->GetKineticEnergy());
        fGetInitialCrossSectionPtr = &KTrackScatteringElastic::GetInitialCrossSection_Cached;
        return fInitialCrossSection;
    }
    Double_t KTrackScatteringElastic::GetFinalCrossSection_Recalculate() const
    {
        fFinalCrossSection =  fElasticCalculator->sigmael(fFinalParticle->GetKineticEnergy());
        fGetFinalCrossSectionPtr = &KTrackScatteringElastic::GetFinalCrossSection_Cached;
        return fFinalCrossSection;
    }

    Bool_t KTrackScatteringElastic::Execute()
    {
        //do all the stuff here
        return kTRUE;
    }


} /* namespace Kassiopeia */
