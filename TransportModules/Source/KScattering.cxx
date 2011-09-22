#include "KScattering.h"

#include "KSRootProcess.h"
#include "KSStep.h"
#include "KSParticle.h"
#include "KSConst.h"

#include "DensityCalculator.h"

namespace Kassiopeia
{

    KScattering::KScattering() :
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
        fGetInitialCrossSectionPtr(&KScattering::GetInitialCrossSection_Recalculate),
        fFinalCrossSection(0.),
        fGetFinalCrossSectionPtr(&KScattering::GetFinalCrossSection_Recalculate)
    {
    }

    KScattering::~KScattering()
    {
    }

    Bool_t KScattering::AddParent( KSProcess* aParentProcess )
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

    Bool_t KScattering::EnableAction()
    {
        fInitialParticle = fParent->GetStep()->GetInitialParticle();
        fFinalParticle = fParent->GetStep()->GetFinalParticle();
        fGetInitialCrossSectionPtr = &KScattering::GetInitialCrossSection_Recalculate;
        fGetFinalCrossSectionPtr = &KScattering::GetFinalCrossSection_Recalculate;

        if( fSubStepSizes.ForEachUntilFalse( &KSStepSize::Enable ) == kFALSE )
        {
            return kFALSE;
        }

        return kTRUE;
    }
    Bool_t KScattering::DisableAction()
    {
        fInitialParticle = NULL;
        fFinalParticle = NULL;
        return kTRUE;
    }

    Double_t KScattering::ComputeTimeStep()
    {
        return fSubStepSizes.SmallestOfAll( &KSStepSize::ComputeTimeStep );
    }

    Double_t& KScattering::ComputeProbability()
    {
        fScatteringProbability = GetScatteringProbability();
        return fScatteringProbability;
    }

    Double_t KScattering::GetScatteringProbability() const
    {
        Double_t pathlength = fParent->GetStep()->GetPathLength();
        Double_t averageDensity = ( fDensityCalculator->GetDensity(fInitialParticle->GetPosition())
                + fDensityCalculator->GetDensity(fFinalParticle->GetPosition()) )/2.0;
        Double_t averageCrossSection = (GetInitialCrossSection() + GetFinalCrossSection())/2.0;
        Double_t totalProb = pathlength * averageDensity * averageCrossSection;

        return totalProb;
    }

    Double_t KScattering::GetDiffScatteringProbability() const
    {
        Double_t density = fDensityCalculator->GetDensity(fInitialParticle->GetPosition());
        Double_t crossSection = GetInitialCrossSection();
        Double_t speed = fInitialParticle->GetSpeed();
        Double_t diffProb = density * crossSection * speed;
        return diffProb;
    }

    Double_t KScattering::GetInitialCrossSection() const
    {
        return (this->*fGetInitialCrossSectionPtr)();
    }

    Double_t KScattering::GetInitialCrossSection_Cached() const
    {
        return fInitialCrossSection;
    }

    Double_t KScattering::GetFinalCrossSection() const
    {
        return (this->*fGetFinalCrossSectionPtr)();
    }

    Double_t KScattering::GetFinalCrossSection_Cached() const
    {
        return fFinalCrossSection;
    }

    void KScattering::UpdateParticleMomentum(const Double_t& ke_eV, const Double_t& theta, const Double_t& phi)
    {
        Double_t Energy = ke_eV * KSConst::Q();
        Double_t Mass = fFinalParticle->GetMass();
        Double_t C = KSConst::C();


//        E < "KTrackScatteringModule::UpdateParticleMomentum";
//
//        #ifdef DEBUG_VERBOSE
//        E = KSException::eScatteringDebug;
//        CatchException(E);
//        #endif

        // if velocity is too small the momentum will not change
        if ( fFinalParticle->GetSpeed() < 1.e-8)
        {
//            #ifdef DEBUG_VERBOSE
//            E << "absolute velocity of particle is too small to change the primary electron momentum";
//            CatchException(E);
//            #endif

            return;
        }


        // Unit vector ub perpendicular to ua:
        // if ua is in z direction -->  ub=(1,0,0);
        // else: ub in x-y plane, perp. to ua
        // Unit vector uc = ua cross ub
        TVector3 UnitA, UnitB, UnitC;
        UnitA = fFinalParticle->GetMomentum().Unit();
        Double_t UnitAInXY = UnitA.Perp();

        if( UnitAInXY < 1.e-10 )
        {
            UnitB.SetXYZ (1., 0., 0. );
        }
        else
        {
            UnitB.SetXYZ( UnitA.Y()/UnitAInXY, -UnitA.X()/UnitAInXY , 0. );

        }
        UnitC = UnitA.Cross(UnitB);


        // Unit vector in new momentum direction (after scattering):
        Double_t CosPhi = TMath::Cos(phi/180. * KSConst::Pi());
        Double_t SinPhi = TMath::Sin(phi/180. * KSConst::Pi());
        Double_t CosTheta= TMath::Cos(theta/180.* KSConst::Pi());
        Double_t SinTheta= TMath::Sin(theta/180.* KSConst::Pi());

        TVector3 MomUnitNew = CosTheta * UnitA + SinTheta * ( CosPhi * UnitB  + SinPhi* UnitC);

        // Momentum vector after scattering:
        Double_t GammaNew = 1. + Energy/(Mass * C * C);
        Double_t MomMagNew = TMath::Sqrt(Energy * (GammaNew + 1.) * Mass);
        fFinalParticle->SetMomentum(MomMagNew * MomUnitNew);

//        #ifdef DEBUG_VERBOSE
//        E << "New particle absolute momentum" << MomMagNew;
//        CatchException(E);
//        #endif

        return;
    }

} /* namespace Kassiopeia */

