#include "KScatteringElastic.h"
#include "KScatteringCalculatorElastic.h"
#include "KSParticle.h"
#include "KSConst.h"
#include "KSRandom.h"

namespace Kassiopeia
{

    KScatteringElastic::KScatteringElastic() :
        KScattering(),
        fElasticCalculator(new KScatteringCalculatorElastic())
    {
        fInteraction = string("Elastic");
    }

    KScatteringElastic::~KScatteringElastic()
    {
        delete fElasticCalculator;
    }

    Double_t KScatteringElastic::GetInitialCrossSection_Recalculate() const
    {
        fInitialCrossSection =  fElasticCalculator->sigmael(fInitialParticle->GetKineticEnergy());
        fGetInitialCrossSectionPtr = &KScatteringElastic::GetInitialCrossSection_Cached;
        return fInitialCrossSection;
    }
    Double_t KScatteringElastic::GetFinalCrossSection_Recalculate() const
    {
        fFinalCrossSection =  fElasticCalculator->sigmael(fFinalParticle->GetKineticEnergy());
        fGetFinalCrossSectionPtr = &KScatteringElastic::GetFinalCrossSection_Cached;
        return fFinalCrossSection;
    }

    Bool_t KScatteringElastic::Execute()
    {

//        E < "KTrackSingleSpeciesElastic::Execute";
//
//        #ifdef DEBUG_VERBOSE
//        E = KSException::eScatteringDebug;
//        CatchException(E);
//        #endif

        //Todo: determine position of final particle inside step container and update final particle

        Double_t KineticEnergy = fFinalParticle->GetKineticEnergy();

//        #ifdef DEBUG_VERBOSE
//        E = KSException::eScatteringDebug;
//        E << "Average kinetic energy of particle: " << AverageKineticEnergy;
//        CatchException(E);
//        #endif

        Double_t Eloss;
        Double_t Theta;
        Double_t Phi;

        //computes the energy loss and the new angle due to elastic scattering
        fElasticCalculator->randomel(KineticEnergy, Eloss, Theta);

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
//            E << "Warning: Energy after elastic scattering too low. Energy artificially increased. ";
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
        //for track output
//        fRootProcess->GetStep()->SetELossScattering(Eloss);

        return kTRUE;
    }


} /* namespace Kassiopeia */
