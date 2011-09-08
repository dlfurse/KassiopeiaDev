#include "KMathRK8.h"

#include "KMathODE.h"

//#define DEBUG_VERBOSE

#ifdef DEBUG_VERBOSE
#include "KSMessage.h"
#endif

namespace Kassiopeia
{

    KMathRK8::KMathRK8() :
        KMathODESolver( eSubsteps ),
        fSum( 0. )
    {
        for( UInt_t i = 0; i < eSubsteps; i++ )
        {
            fDerivativeAreas[i] = NULL;
        }

        for( UInt_t i = 0; i < eConditions; i++ )
        {
            fConditionAreas[i] = NULL;
        }
    }

    KMathRK8::~KMathRK8()
    {
        if( fDerivativeAreas[0] != NULL )
        {
            delete[] fDerivativeAreas[0];
            fDerivativeAreas[0] = NULL;
        }
        if( fConditionAreas[1] != NULL )
        {
            delete[] fConditionAreas[1];
            fConditionAreas[1] = NULL;
        }
    }

    void KMathRK8::CalculateSolution()
    {
        UInt_t iRow, iColumn, iComponent;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KMathRK8::SolveAction";
#endif

#ifdef DEBUG_VERBOSE
        msg << "initial:" << ret;
        msg << "[";
        for( UInt_t index = 0; index < fODESystem->GetDimension(); index++ )
        {
            msg << fConditionAreas[0][index] << ", ";
        }
        msg << "]" << end;
#endif

        for( iRow = 0; iRow < eSubsteps; iRow++ )
        {

            fODESystem->SetConditionArea( fConditionAreas[iRow] );
            fODESystem->SetDerivativeArea( fDerivativeAreas[iRow] );
            fODESystem->CalculateDerivative();

#ifdef DEBUG_VERBOSE
            msg << "derivative " << iRow << ":" << ret;
            msg << "[";
            for( UInt_t index = 0; index < fODESystem->GetDimension(); index++ )
            {
                msg << fDerivativeAreas[iRow][index] << ", ";
            }
            msg << "]" << end;
#endif

            for( iComponent = 0; iComponent < fODESystem->GetDimension(); iComponent++ )
            {
                fSum = 0.0;
                for( iColumn = 0; iColumn <= iRow; iColumn++ )
                {
                    fSum += fA[iRow][iColumn] * fDerivativeAreas[iColumn][iComponent];
                }
                fConditionAreas[iRow + 1][iComponent] = fConditionAreas[0][iComponent] + fTimeStep * fSum;
            }

#ifdef DEBUG_VERBOSE
            msg << "step " << iRow + 1 << ":" << ret;
            msg << "[";
            for( UInt_t index = 0; index < fODESystem->GetDimension(); index++ )
            {
                msg << fConditionAreas[iRow + 1][index] << ", ";
            }
            msg << "]" << end;
#endif
        }

#ifdef DEBUG_VERBOSE
        msg << "solution:" << ret;
        msg << "[";
        for( UInt_t index = 0; index < fODESystem->GetDimension(); index++ )
        {
            msg << fConditionAreas[eConditions - 1][index] << ", ";
        }
        msg << "]" << end;
#endif

        return;
    }

    void KMathRK8::SetODESystemAction()
    {

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KMathRK8::SetODEAction";
#endif

#ifdef DEBUG_VERBOSE
        msg << "got a new ODE of dimension " << fODESystem->GetDimension() << end;
#endif

        //release previously allocated derivative array if necessary
        if( fDerivativeAreas[0] != NULL )
        {
#ifdef DEBUG_VERBOSE
            msg << "deleting old derivative array at " << fDerivativeAreas[0] << end;
#endif
            delete[] fDerivativeAreas[0];
            fDerivativeAreas[0] = NULL;
        }

        //release previously allocated intermediate condition array if necessary
        if( fConditionAreas[1] != NULL )
        {
#ifdef DEBUG_VERBOSE
            msg << "deleting old intermediate condition array at " << fConditionAreas[0] << end;
#endif
            delete[] fConditionAreas[0];
            fConditionAreas[1] = NULL;
        }

        //allocate new memory for the derivative array
        size_t DerivativeAreaAllocSize = eSubsteps * fODESystem->GetDimension();
#ifdef DEBUG_VERBOSE
        msg << "allocating new derivative array of dimension " << DerivativeAreaAllocSize << end;
#endif
        fDerivativeAreas[0] = new Double_t[DerivativeAreaAllocSize]();
        for( UInt_t i = 1; i < eSubsteps; i++ )
        {
            fDerivativeAreas[i] = fDerivativeAreas[i - 1] + fODESystem->GetDimension();
        }

        //allocate new memory for the intermediate condition array
        size_t ConditionAreaAllocSize = (eConditions - 2) * fODESystem->GetDimension();
#ifdef DEBUG_VERBOSE
        msg << "allocating new intermediate condition array of dimension " << ConditionAreaAllocSize << end;
#endif
        fConditionAreas[1] = new Double_t[ConditionAreaAllocSize]();
        for( UInt_t i = 2; i < eConditions - 1; i++ )
        {
            fConditionAreas[i] = fConditionAreas[i - 1] + fODESystem->GetDimension();
        }

        return;
    }

    void KMathRK8::SetTimeStepAction()
    {
        return;
    }

    void KMathRK8::SetInitialConditionAreaAction()
    {
        fConditionAreas[0] = fInitialConditionArea;
        return;
    }

    void KMathRK8::SetFinalConditionAreaAction()
    {
        fConditionAreas[eConditions-1] = fFinalConditionArea;
        return;
    }

    void KMathRK8::SetErrorConditionAreaAction()
    {
        return;
    }

    //*************************
    // runge-kutta coefficients
    //*************************

    const Double_t KMathRK8::fA[eSubsteps][eSubsteps] =
        {
            { 1. / 4., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0. }, //1st row
                { 5. / 72., 1. / 72., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0. }, //2nd row
                { 1. / 32., 0., 3. / 32., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0. }, //3rd row
                { 106. / 125., 0., -408. / 125., 352. / 125., 0., 0., 0., 0., 0., 0., 0., 0., 0. }, //4th row
                { 1. / 48., 0., 0., 8. / 33., 125. / 528., 0., 0., 0., 0., 0., 0., 0., 0. }, //5th row
                { -1263. / 2401., 0., 0., 39936. / 26411., -64125. / 26411., 5520. / 2401., 0., 0., 0., 0., 0., 0., 0. }, //6th row
                { 37. / 392., 0., 0., 0., 1625. / 9408., -2. / 15., 61. / 6720., 0., 0., 0., 0., 0., 0. }, //7th row
                { 17176. / 25515., 0., 0., -47104. / 25515., 1325. / 504., -41792. / 25515., 20237. / 145800., 4312. / 6075., 0., 0., 0., 0., 0. }, //8th row
                { -23834. / 180075., 0., 0., -77824. / 1980825., -636635. / 633864., 254048. / 300125., -183. / 7000., 8. / 11., -324. / 3773., 0., 0., 0., 0. }, //9th row
                { 12733. / 7600., 0., 0., -20032. / 5225., 456485. / 80256., -42599. / 7125., 339227. / 912000., -1029. / 4180., 1701. / 1408., 5145. / 2432., 0., 0., 0. }, //10th row
                { -27061. / 204120., 0., 0., 40448. / 280665., -1353775. / 1197504., 17662. / 25515., -71687. / 1166400., 98. / 225., 1. / 16., 3773. / 11664., 0., 0., 0. }, //11th row
                { 11203. / 8680., 0., 0., -38144. / 11935., 2354425. / 458304., -84046. / 16275., 673309. / 1636800., 4704. / 8525., 9477. / 10912., -1029. / 992., 0., 729. / 341., 0. }, //12th row
                { 31. / 720., 0., 0., 0., 0., 16. / 75., 16807. / 79200., 16807. / 79200., 243. / 1760., 0., 0., 243. / 1760., 31. / 720. } }; //13th row

} // end namespace Kassiopeia
