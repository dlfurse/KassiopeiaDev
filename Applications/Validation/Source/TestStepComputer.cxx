/*
 * TestStepComputer.cxx
 *
 * created on: Aug 29, 2011
 * author: dlfurse
 */

#include "KSMessage.h"
#include "KSMessageHandler.h"

#include "KSStep.h"
#include "KSParticle.h"
#include "KSParticleFactory.h"
#include "KSParticleFactoryTable.h"

#include "KSRootMagneticField.h"
#include "KSRootElectricField.h"
#include "KSRootProcess.h"

#include "KMathRK8.h"
#include "KTrackExactStepComputer.h"
#include "KTrackProcessPropagation.h"
#include "KTrackStepSizeCyclotron.h"

#include "TFile.h"
#include "TTree.h"
#include "TMath.h"

#include <iostream>
using std::cout;
using std::endl;

namespace Kassiopeia
{

    class KSMagneticFieldConstant :
        public KSMagneticField
    {
        public:
            KSMagneticFieldConstant();
            virtual ~KSMagneticFieldConstant();

        public:
            virtual Bool_t GetA( TVector3& aTarget, const TVector3& aSamplePoint, const Double_t& aSampleTime );
            virtual Bool_t GetField( TVector3& aTarget, const TVector3& aSamplePoint, const Double_t& aSampleTime );
            virtual Bool_t GetFieldGradient( TMatrixT< Double_t >& aTarget, const TVector3& aSamplePoint, const Double_t& aSampleTime );

        public:
            void SetField( const TVector3& aFieldVector );

        private:
            TVector3 fFieldVector;
    };

    inline KSMagneticFieldConstant::KSMagneticFieldConstant() :
        KSMagneticField(),
        fFieldVector( 0., 0., 0. )
    {
    }
    inline KSMagneticFieldConstant::~KSMagneticFieldConstant()
    {
    }

    inline Bool_t KSMagneticFieldConstant::GetA( TVector3& aTarget, const TVector3& aSamplePoint, const Double_t& )
    {
        aTarget = (1. / 2.) * fFieldVector.Cross( aSamplePoint );
        return kTRUE;
    }
    inline Bool_t KSMagneticFieldConstant::GetField( TVector3& aTarget, const TVector3&, const Double_t& )
    {
        aTarget = fFieldVector;
        return kTRUE;
    }
    inline Bool_t KSMagneticFieldConstant::GetFieldGradient( TMatrixT< Double_t >& aTarget, const TVector3&, const Double_t& )
    {
        aTarget.Zero();
        return kTRUE;
    }

    inline void KSMagneticFieldConstant::SetField( const TVector3& aFieldVector )
    {
        fFieldVector = aFieldVector;
        return;
    }

    class KSElectricFieldQuadrupole :
        public KSElectricField
    {
        public:
            KSElectricFieldQuadrupole();
            virtual ~KSElectricFieldQuadrupole();

        public:
            virtual Bool_t GetPhi( Double_t& aTarget, const TVector3& aSamplePoint, const Double_t& aSampleTime );
            virtual Bool_t GetField( TVector3& aTarget, const TVector3& aSamplePoint, const Double_t& aSampleTime );
            virtual Bool_t GetGradient( TMatrixT< Double_t >& aTarget, const TVector3& aSamplePoint, const Double_t& aSampleTime );

        public:
            void SetLocation( const TVector3& aLocation );
            void SetStrength( const Double_t& aStrength );
            void SetLength( const Double_t& aLength );
            void SetRadius( const Double_t& aRadius );

        private:
            TVector3 fLocation;
            Double_t fStrength;
            Double_t fLength;
            Double_t fRadius;
            Double_t fCharacteristic;
    };

    inline KSElectricFieldQuadrupole::KSElectricFieldQuadrupole() :
        fLocation( 0., 0., 0. ),
        fStrength( 0. ),
        fLength( 0. ),
        fRadius( 0. )
    {
    }
    inline KSElectricFieldQuadrupole::~KSElectricFieldQuadrupole()
    {
    }

    inline Bool_t KSElectricFieldQuadrupole::GetPhi( Double_t& aTarget, const TVector3& aSamplePoint, const Double_t& )
    {
        TVector3 FieldPoint = aSamplePoint - fLocation;
        aTarget = (fStrength / (2. * fCharacteristic * fCharacteristic)) * (FieldPoint.Z() * FieldPoint.Z() - (1. / 2.) * FieldPoint.X() * FieldPoint.X() - (1. / 2.) * FieldPoint.Y() * FieldPoint.Y());
        return kTRUE;
    }
    inline Bool_t KSElectricFieldQuadrupole::GetField( TVector3& aTarget, const TVector3& aSamplePoint, const Double_t& )
    {
        TVector3 FieldPoint = aSamplePoint - fLocation;
        TVector3 AxialPart = FieldPoint.Z() * TVector3( 0., 0., 1. );
        TVector3 RadialPart = FieldPoint - AxialPart;
        aTarget = (fStrength / (2. * fCharacteristic * fCharacteristic)) * RadialPart - (fStrength / (fCharacteristic * fCharacteristic)) * AxialPart;
        return kTRUE;
    }
    inline Bool_t KSElectricFieldQuadrupole::GetGradient( TMatrixT< Double_t >& aTarget, const TVector3&, const Double_t& )
    {
        aTarget.Zero();
        aTarget[0][0] = (fStrength / (2. * fCharacteristic * fCharacteristic));
        aTarget[1][1] = (fStrength / (2. * fCharacteristic * fCharacteristic));
        aTarget[2][2] = -(fStrength / (fCharacteristic * fCharacteristic));
        return kTRUE;
    }

    inline void KSElectricFieldQuadrupole::SetLocation( const TVector3& aLocation )
    {
        fLocation = aLocation;
        return;
    }
    inline void KSElectricFieldQuadrupole::SetStrength( const Double_t& aStrength )
    {
        fStrength = aStrength;
        return;
    }
    inline void KSElectricFieldQuadrupole::SetLength( const Double_t& aLength )
    {
        fLength = aLength;
        fCharacteristic = TMath::Sqrt( (1. / 2.) * (fLength * fLength + (1. / 2.) * fRadius * fRadius) );
        return;
    }
    inline void KSElectricFieldQuadrupole::SetRadius( const Double_t& aRadius )
    {
        fRadius = aRadius;
        fCharacteristic = TMath::Sqrt( (1. / 2.) * (fLength * fLength + (1. / 2.) * fRadius * fRadius) );
        return;
    }

}

using namespace Kassiopeia;

int main()
{

    //initialize toolbox

    KSMagneticFieldConstant* ConstantMagneticField = new KSMagneticFieldConstant();
    ConstantMagneticField->SetField( TVector3( 0., 0., 5.05 ) );
    KSRootMagneticField::GetInstance()->AddMagneticField( ConstantMagneticField );

    KSElectricFieldQuadrupole* QuadrupoleElectricField = new KSElectricFieldQuadrupole();
    QuadrupoleElectricField->SetLocation( TVector3( 0., 0., 0. ) );
    QuadrupoleElectricField->SetStrength( 53.1 );
    QuadrupoleElectricField->SetLength( 1.120e-3 );
    QuadrupoleElectricField->SetRadius( 1.584e-3 );
    KSRootElectricField::GetInstance()->AddElectricField( QuadrupoleElectricField );

    KSParticle* InitialParticle = KSParticleFactoryTable::GetInstance()->GetParticleFactory( 2212 )->Build();
    InitialParticle->SetElectricFieldCalculator( KSRootElectricField::GetInstance() );
    KSParticle* FinalParticle = KSParticleFactoryTable::GetInstance()->GetParticleFactory( 2212 )->Build();
    FinalParticle->SetElectricFieldCalculator( KSRootElectricField::GetInstance() );
    KSStep* Step = new KSStep();
    Step->SetInitialParticle( InitialParticle );
    Step->SetFinalParticle( FinalParticle );

    KMathODESolver* Solver = new KMathRK8();

    KTrackExactStepComputer* StepComputer = new KTrackExactStepComputer( Solver );

    KTrackProcessPropagation* ProcessPropagation = new KTrackProcessPropagation();

    KTrackStepSizeCyclotron* StepSizeCyclotron = new KTrackStepSizeCyclotron();
    StepSizeCyclotron->SetFraction( 1. / 16. );

    //initialize root garbage

    TFile* OutputFile = new TFile( "./TestStepComputerOutput.root", "RECREATE" );

    TTree* OutputTree = new TTree( "StepComputerOutput", "StepComputerOutput" );
    OutputTree->SetDirectory( OutputFile );

    Double_t Time;
    OutputTree->Branch( "Time", &Time );

    TVector3 Position;
    OutputTree->Branch( "Position", &Position );

    TVector3 Momentum;
    OutputTree->Branch( "Momentum", &Momentum );

    //dynamic filling of stuff

    cout << "initializing root stuff..." << endl;

    KSRootProcess* RootProcess = KSRootProcess::GetInstance();
    RootProcess->Disable();

    RootProcess->AddProcess( StepComputer );
    RootProcess->AddProcess( ProcessPropagation );
    RootProcess->AddStepSize( StepSizeCyclotron );

    RootProcess->SetStep( Step );
    RootProcess->Enable();

    //main loop

    KSMessageHandler::GetInstance()->SetTerminalVerbosity( eDebug );

    InitialParticle->SetPosition( 1.5e-3, 0., -1.5e-3 );
    InitialParticle->SetMomentum( 0., 1., 0. );
    InitialParticle->SetKineticEnergy( 5.0 );

    for( UInt_t StepIndex = 0; StepIndex < 100000; StepIndex++ )
    {

        RootProcess->ComputeStep();

        if( StepIndex % 10000 == 0 )
        {
            cout << StepIndex << endl;
        }

        if( StepIndex % 1 == 0 )
        {
            Time = Step->GetFinalParticle()->GetT();
            Position = Step->GetFinalParticle()->GetPosition();
            Momentum = Step->GetFinalParticle()->GetMomentum();
            OutputTree->Fill();
        }

        InitialParticle->PullFrom( FinalParticle );
    }

    //dynamic removal of stuff

    RootProcess->Disable();

    RootProcess->RemoveProcess( ProcessPropagation );
    RootProcess->RemoveProcess( StepComputer );

    //finalize root garbage

    cout << "finalizing root stuff..." << endl;

    OutputTree->Write();
    OutputFile->Close();
    delete OutputFile;

    //finalize toolbox

    delete ProcessPropagation;
    delete StepComputer;

    delete InitialParticle;
    delete FinalParticle;
    delete Step;

    delete ConstantMagneticField;
    delete QuadrupoleElectricField;

    return 0;
}
