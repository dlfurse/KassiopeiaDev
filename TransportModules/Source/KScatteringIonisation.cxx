#include "KScatteringIonisation.h"
#include "KScatteringCalculatorInelastic.h"
#include "KSConst.h"
#include "KSRandom.h"
#include "KSParticle.h"
#include "KSParticleFactory.h"
#include "KSParticleFactoryTable.h"
#include "KSRootProcess.h"
#include "KSStep.h"
#include "KSTrack.h"

namespace Kassiopeia
{

    KScatteringIonisation::KScatteringIonisation() :
        KScattering(),
        fInelasticCalculator(new KScatteringCalculatorInelastic())
    {
        fInteraction = string("Ionisation");
    }

    KScatteringIonisation::~KScatteringIonisation()
    {
        delete fInelasticCalculator;
    }

    Double_t KScatteringIonisation::GetInitialCrossSection_Recalculate() const
    {
        fInitialCrossSection =  fInelasticCalculator->sigmaexc(fInitialParticle->GetKineticEnergy());
        fGetInitialCrossSectionPtr = &KScatteringIonisation::GetInitialCrossSection_Cached;
        return fInitialCrossSection;
    }
    Double_t KScatteringIonisation::GetFinalCrossSection_Recalculate() const
    {
        fFinalCrossSection =  fInelasticCalculator->sigmaexc(fFinalParticle->GetKineticEnergy());
        fGetFinalCrossSectionPtr = &KScatteringIonisation::GetFinalCrossSection_Cached;
        return fFinalCrossSection;
    }

    Bool_t KScatteringIonisation::Execute()
    {

//        E < "KTrackSingleSpeciesIonization::Execute";
//
//        #ifdef DEBUG_VERBOSE
//        E = KSException::eScatteringDebug;
//        CatchException(E);
//        #endif

        Double_t KineticEnergy = fFinalParticle->GetKineticEnergy();

//        #ifdef DEBUG_VERBOSE
//        E = KSException::eScatteringDebug;
//        E << "Average kinetic energy of particle: " << AverageKineticEnergy;
//        CatchException(E);
//        #endif

        Double_t Eloss;
        Double_t Theta;
        Double_t Phi;

        //computes the energy loss and the new angle due to scattering
        fInelasticCalculator->randomion(KineticEnergy, Eloss, Theta);

//        #ifdef DEBUG_VERBOSE
//        E = KSException::eScatteringDebug;
//        E << "Inelastic Calculator computed ELoss =  " << Eloss << " and Theta =  " << Theta;
//        CatchException(E);
//        #endif

        //subtract off the energy loss
        KineticEnergy = KineticEnergy - Eloss;

        //check if the new energy is too low
        if (KineticEnergy < KSConst::Q() * 0.1)
        {
            KineticEnergy = KSConst::Q() * 0.1;

//            #ifdef DEBUG_VERBOSE
//            E = KSException::eScatteringDebug;
//            E << "Warning: Energy after ionization too low. Energy artificially increased. ";
//            CatchException(E);
//            #endif
        }


        //dice an azimuthal angle
        Phi = 2.* KSConst::Pi() * KSRandom::GetInstance()->Rndm();

//        #ifdef DEBUG_VERBOSE
//        E = KSException::eScatteringDebug;
//        E << "Randomly chosen azimuthal angle Phi = : " << Phi;
//        CatchException(E);
//        #endif

        //update the final particle
        UpdateParticleMomentum( KineticEnergy, Theta, Phi );

        CreateSecondaryParticle( Eloss );

        //update the scattering data
//        fData->fScatteringEnergyLoss = Eloss;
//        fData->fNumSecondaries = fData->fNumSecondaries + 1;
//        fData->fImpulse = fFinalParticle->GetMomentum()-fInitialParticle->GetMomentum();
//        //for track output
//        fRootProcess->GetStep()->SetELossScattering(Eloss);

        return kTRUE;
    }

    void KScatteringIonisation::CreateSecondaryParticle(Double_t ELoss) const
    {

//        #ifdef DEBUG_VERBOSE
//
//        E = KSException::eScatteringDebug;
//        E < "KTrackSingleSpeciesIonization::CreateSecondaryParticle";
//        CatchException(E);
//        #endif
        KSParticle* NewParticle = KSParticleFactoryTable::GetInstance()->GetParticleFactory(11)->Build();

        NewParticle->SetPosition(fFinalParticle->GetPosition());
        NewParticle->SetT(fFinalParticle->GetT());

        //Int_t ParentLabel;
        //Int_t Label;
        NewParticle->SetKineticEnergy(ELoss - fInelasticCalculator->GetIonizationEnergy());

        Double_t InitialCosTheta = -1. + 2. * KSRandom::GetInstance()->Rndm();
        Double_t InitialPhi = (-1. + 2. * KSRandom::GetInstance()->Rndm()) * KSConst::Pi() ;
        NewParticle->SetPolarAngleToZ(TMath::ACos(InitialCosTheta) * 180.0 / KSConst::Pi());
        NewParticle->SetAzimuthalAngleToX(InitialPhi * 180.0 / KSConst::Pi());

//        #ifdef DEBUG_VERBOSE
//        E = KSException::eScatteringDebug;
//        E << "Kinetic energy: "<< ELoss - fInelasticCalculator->GetIonizationEnergy() << " Theta: "<< TMath::ACos(InitialCosTheta) << " Phi: "<< InitialPhi;
//        CatchException(E);
//        #endif

        KSTrack* NewTrack = new KSTrack();
        NewTrack->SetCreationName(fInteraction);
        NewTrack->SetInitialParticle(NewParticle);
        KSParticle* clone = new KSParticle(NewParticle);
        NewTrack->SetFinalParticle(clone);

        fParent->GetStep()->GetSecondaryQueue()->AddItem(NewTrack);

        return;
    }


} /* namespace Kassiopeia */
