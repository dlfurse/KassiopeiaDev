//XXX attention! this program is only temporary for debugging purposes in the disaster branch

//#include "KSMessage.h"

#include "KMathODE.h"

namespace Kassiopeia
{

    class KMathTestODE :
        public KMathODE
    {
        public:
            KMathTestODE();
            virtual ~KMathTestODE();

            virtual void CalculateDerivative();

        private:
            virtual void SetConditionAreaAction();
            virtual void SetDerivativeAreaAction();
    };

    inline KMathTestODE::KMathTestODE() :
        KMathODE( 3 )
    {
    }
    inline KMathTestODE::~KMathTestODE()
    {
    }

    inline void KMathTestODE::CalculateDerivative()
    {
        fDerivativeArea[0] = fConditionArea[1] - fConditionArea[2];
        fDerivativeArea[1] = fConditionArea[0] * fConditionArea[0] + fConditionArea[1];
        fDerivativeArea[2] = fConditionArea[0] * fConditionArea[0] + fConditionArea[2];
        return;
    }

    inline void KMathTestODE::SetConditionAreaAction()
    {
        return;
    }
    inline void KMathTestODE::SetDerivativeAreaAction()
    {
        return;
    }

}

#include "KMathRK8.h"
#include "KMathRK86.h"

#include "TMath.h"

#include <ctime>
#include <sstream>
#include <iostream>
using std::stringstream;
using std::cout;
using std::endl;
using namespace Kassiopeia;

void TestODE_Condition( Double_t* aCondition, Double_t aTime );

int main( int argc, char** argv )
{

    cout.precision( 20 );
    //KSMessageHandler::GetInstance()->SetTerminalVerbosity( eDebug );

    if( argc < 4 )
    {
        cout << "\n";
        cout << "TestODE (part of Kassiopeia validation)\n";
        cout << "\n";
        cout << "description:\n";
        cout << "  This C++ program integrates a stiff differential equation with an 8th order Runge-Kutta routine\n";
        cout << "  It is an adaptation of an original C-program by Dr. Ferenc Glück (KIT)\n";
        cout << "\n";
        cout << "usage:\n";
        cout << "  TestODE <solver index> <start time> <time step> <end time>" << endl;
        return -1;
    }

    stringstream Converter;

    //solver index
    UInt_t SolverIndex;
    Converter.clear();
    Converter.str( argv[1] );
    Converter >> SolverIndex;

    //the initial time
    Double_t InitialTime;
    Converter.clear();
    Converter.str( argv[2] );
    Converter >> InitialTime;

    //the time step
    Double_t TimeStep;
    Converter.clear();
    Converter.str( argv[3] );
    Converter >> TimeStep;

    //the final time
    Double_t FinalTime;
    Converter.clear();
    Converter.str( argv[4] );
    Converter >> FinalTime;

    //local variables
    Double_t CurrentTime;
    UInt_t StepCount;

    Double_t AnalyticSolution[3] =
        { 0., 0., 0. };
    Double_t NumericSolution[3] =
        { 0., 0., 0. };
    Double_t Error[3] =
        { 0., 0., 0. };

    //ode
    KMathODE* TestODE = new KMathTestODE();

    //solver
    KMathODESolver* TestODESolver;

    if( SolverIndex == 1 )
    {
        TestODESolver = new KMathRK8();
    }
    else if( SolverIndex == 2 )
    {
        TestODESolver = new KMathRK86();
    }
    else
    {
        cout << "unknown solver index" << endl;
        return -1;
    }
    TestODESolver->SetODE( TestODE );
    TestODESolver->SetTimeStep( TimeStep );
    TestODESolver->SetInitialConditionArea( NumericSolution );
    TestODESolver->SetFinalConditionArea( NumericSolution );
    TestODESolver->SetErrorConditionArea( Error );

    TestODE_Condition( NumericSolution, InitialTime );

    cout << "initial condition:\n";
    cout << "  " << NumericSolution[0] << ", " << NumericSolution[1] << ", " << NumericSolution[2] << "\n";

    CurrentTime = InitialTime;
    StepCount = 0;

    clock_t StartTime = clock();

    while( true )
    {
        TestODESolver->CalculateSolution();
        CurrentTime += TimeStep;
        StepCount += 1;

        if( CurrentTime >= FinalTime )
        {
            break;
        }
    }

    clock_t EndTime = clock();

    TestODE_Condition( AnalyticSolution, CurrentTime );

    cout.precision( 20 );
    cout << "step count:\n";
    cout << "  " << StepCount << "\n";
    cout << "clock ticks:\n";
    cout << "  " << EndTime - StartTime << "\n";
    cout << "analytic solution:\n";
    cout << "  " << AnalyticSolution[0] << ", " << AnalyticSolution[1] << ", " << AnalyticSolution[2] << "\n";
    cout << "numeric solution:\n";
    cout << "  " << NumericSolution[0] << ", " << NumericSolution[1] << ", " << NumericSolution[2] << "\n";
    cout << "analytic error:\n";
    cout << "  " << TMath::Abs( (NumericSolution[0] - AnalyticSolution[0]) / AnalyticSolution[0] ) << ", " << TMath::Abs( (NumericSolution[1] - AnalyticSolution[1]) / AnalyticSolution[1] ) << ", " << TMath::Abs( (NumericSolution[2] - AnalyticSolution[2]) / AnalyticSolution[2] ) << "\n";
    cout << "numeric error:\n";
    cout << "  " << TMath::Abs( Error[0] ) << ", " << TMath::Abs( Error[1] ) << ", " << TMath::Abs( Error[2] ) << "\n";
    cout << endl;

    delete TestODE;
    delete TestODESolver;

    return 0;
}

void TestODE_Condition( Double_t* aCondition, Double_t aTime )
{
    static const Double_t TestODE_Coefficients[3] =
        { 0.6, 1.6, 2.3 };

    aCondition[0] = TestODE_Coefficients[0] + TestODE_Coefficients[1] * TMath::Exp( aTime );
    aCondition[1] = -TestODE_Coefficients[0] * TestODE_Coefficients[0] + (2. * TestODE_Coefficients[0] * TestODE_Coefficients[1] * aTime + TestODE_Coefficients[2]) * TMath::Exp( aTime ) + TestODE_Coefficients[1] * TestODE_Coefficients[1] * TMath::Exp( 2. * aTime );
    aCondition[2] = aCondition[1] - aCondition[0] + TestODE_Coefficients[0];

    return;
}
