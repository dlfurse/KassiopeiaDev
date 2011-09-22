#include "KScatteringExcitation.h"
#include "KScatteringCalculatorInelastic.h"
#include "KSParticle.h"
#include "KSConst.h"
#include "KSRandom.h"

namespace Kassiopeia
{

    KScatteringExcitation::KScatteringExcitation() :
        KScattering(),
        fInelasticCalculator(new KScatteringCalculatorInelastic())
    {
        fInteraction = string("Excitation");
    }

    KScatteringExcitation::~KScatteringExcitation()
    {
        delete fInelasticCalculator;
    }

    Double_t KScatteringExcitation::GetInitialCrossSection_Recalculate() const
    {
        fInitialCrossSection =  fInelasticCalculator->sigmaexc(fInitialParticle->GetKineticEnergy());
        fGetInitialCrossSectionPtr = &KScatteringExcitation::GetInitialCrossSection_Cached;
        return fInitialCrossSection;
    }
    Double_t KScatteringExcitation::GetFinalCrossSection_Recalculate() const
    {
        fFinalCrossSection =  fInelasticCalculator->sigmaexc(fFinalParticle->GetKineticEnergy());
        fGetFinalCrossSectionPtr = &KScatteringExcitation::GetFinalCrossSection_Cached;
        return fFinalCrossSection;
    }

    Bool_t KScatteringExcitation::Execute()
    {
//        #ifdef DEBUG_VERBOSE
//
//        E = KSException::eScatteringDebug;
//        E < "KTrackSingleSpeciesExcitation::Execute";
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

        //computes the energy loss and the new angle due to inelastic scattering
        fInelasticCalculator->randomexc(KineticEnergy, Eloss, Theta);

//        #ifdef DEBUG_VERBOSE
//        E = KSException::eScatteringDebug;
//        E << "Elastic Calculator computed ELoss =  " << Eloss << " and Theta =  " << Theta;
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
//            E << "Warning: Energy after inelastic scattering too low. Energy artificially increased. ";
//            CatchException(E);
//            #endif
        }

        //dice an azimuthal angle
        Phi = 2.* KSConst::Pi() * KSRandom::GetInstance()->Rndm();
//        #ifdef DEBUG_VERBOSE
//        E = KSException::eScatteringDebug;
//        E << "Randomly chosen azimuthal angle: " << Phi;
//        CatchException(E);
//        #endif

        //update the final particle
        UpdateParticleMomentum( KineticEnergy, Theta, Phi );

        //update the scattering data
//        fData->fScatteringEnergyLoss = Eloss;
//        fData->fNumSecondaries = 0;
//        fData->fImpulse = fFinalParticle->GetMomentum()-fInitialParticle->GetMomentum();
//        //for track output
//        fRootProcess->GetStep()->SetELossScattering(Eloss);



        return kTRUE;
    }


} /* namespace Kassiopeia */
