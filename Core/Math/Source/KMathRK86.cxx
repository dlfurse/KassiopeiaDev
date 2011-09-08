#include "KMathRK86.h"

#include "KMathODE.h"

//#define DEBUG_VERBOSE

#ifdef DEBUG_VERBOSE
#include "KSMessage.h"
#endif

namespace Kassiopeia
{

    KMathRK86::KMathRK86() :
        KMathODESolver( eSubsteps ),
        fSum6( 0. ),
        fSum8( 0. )
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

    KMathRK86::~KMathRK86()
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

    void KMathRK86::CalculateSolution()
    {
        UInt_t iRow, iColumn, iComponent;

#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KMathRK86::SolveAction";
#endif

#ifdef DEBUG_VERBOSE
        msg << "step 0:" << ret;
        msg << "[";
        for( size_t index = 0; index < fODESystem->GetDimension(); index++ )
        {
            msg << fConditionAreas[0][index] << ", ";
        }
        msg << "]" << end;
#endif

        //iteratively find the intermediate points and calculate the derivatives there
        for( iRow = 0; iRow < eSubsteps - 1; iRow++ )
        {
            fODESystem->SetConditionArea( fConditionAreas[iRow] );
            fODESystem->SetDerivativeArea( fDerivativeAreas[iRow]);
            fODESystem->CalculateDerivative();

#ifdef DEBUG_VERBOSE
            msg << "derivative " << iRow << ":" << ret;
            msg << "[";
            for( size_t index = 0; index < fODESystem->GetDimension(); index++ )
            {
                msg << fDerivativeAreas[iRow][index] << ", ";
            }
            msg << "]" << end;
#endif

            for( iComponent = 0; iComponent < fODESystem->GetDimension(); iComponent++ )
            {
                fSum8 = 0.0;
                for( iColumn = 0; iColumn <= iRow; iColumn++ )
                {
                    fSum8 += fA[iRow][iColumn] * fDerivativeAreas[iColumn][iComponent];
                }
                fConditionAreas[iRow + 1][iComponent] = fConditionAreas[0][iComponent] + fTimeStep * fSum8;
            }

#ifdef DEBUG_VERBOSE
            msg << "step " << iRow + 1 << ":" << ret;
            msg << "[";
            for( size_t index = 0; index < fODESystem->GetDimension(); index++ )
            {
                msg << fConditionAreas[iRow + 1][index] << ", ";
            }
            msg << "]" << end;
#endif

        }

        fODESystem->SetConditionArea( fConditionAreas[eSubsteps - 1] );
        fODESystem->SetDerivativeArea( fDerivativeAreas[eSubsteps - 1] );
        fODESystem->CalculateDerivative();

        //form the solution and truncation error from the intermediate derivatives
        for( iComponent = 0; iComponent < fODESystem->GetDimension(); iComponent++ )
        {
            fSum8 = 0.0;
            fSum6 = 0.0;
            for( iColumn = 0; iColumn < eSubsteps; iColumn++ )
            {
                fSum8 += fAFinal8[iColumn] * fDerivativeAreas[iColumn][iComponent];
                fSum6 += fAFinal6[iColumn] * fDerivativeAreas[iColumn][iComponent];
            }
            fConditionAreas[eSubsteps][iComponent] = fConditionAreas[0][iComponent] + fTimeStep * fSum8;
            fErrorConditionArea[iComponent] = (fConditionAreas[eSubsteps][iComponent] - (fConditionAreas[0][iComponent] + fTimeStep * fSum6)) * fTimeStep;
            fFinalConditionArea[iComponent] = fConditionAreas[eSubsteps][iComponent];
        }

#ifdef DEBUG_VERBOSE
        msg << "solution:" << ret;
        msg << "[";
        for( size_t index = 0; index < fODESystem->GetDimension(); index++ )
        {
            msg << fFinalConditionArea[index] << ", ";
        }
        msg << "]" << end;
#endif

#ifdef DEBUG_VERBOSE
        msg << "error:" << ret;
        msg << "[";
        for( size_t index = 0; index < fODESystem->GetDimension(); index++ )
        {
            msg << fErrorConditionArea[index] << ", ";
        }
        msg << "]" << end;
#endif

        return;
    }

    void KMathRK86::SetODESystemAction()
    {
#ifdef DEBUG_VERBOSE
        msg = eDebug;
        msg < "KMathRK86::SetODEAction";
#endif

#ifdef DEBUG_VERBOSE
        msg << "got a new ODE of dimension " << fODESystem->GetDimension() << end;
#endif

//release previously allocated dervative array if necessary
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
            msg << "deleting old condition condition array at " << fConditionAreas[1] << end;
#endif
            delete[] fConditionAreas[1];
            fConditionAreas[1] = 0;
        }

        //allocate new memory for the derivative array
        size_t DerivativeAreaAllocSize = eSubsteps * fODESystem->GetDimension();
#ifdef DEBUG_VERBOSE
        msg << " allocating new derivative array of dimension " << DerivativeAreaAllocSize << end;
#endif
        fDerivativeAreas[0] = new Double_t[DerivativeAreaAllocSize]();
        for( UInt_t i = 1; i < eSubsteps; i++ )
        {
            fDerivativeAreas[i] = fDerivativeAreas[i - 1] + fODESystem->GetDimension();
        }

        //allocate new memory for the intermediate condition array
        size_t ConditionAreaAllocSize = (eConditions - 1) * fODESystem->GetDimension();
#ifdef DEBUG_VERBOSE
        msg << "allocating new condition array of dimension " << ConditionAreaAllocSize << end;
#endif
        fConditionAreas[1] = new Double_t[ConditionAreaAllocSize]();
        for( UInt_t i = 2; i < eConditions; i++ )
        {
            fConditionAreas[i] = fConditionAreas[i - 1] + fODESystem->GetDimension();
        }

        return;
    }

    void KMathRK86::SetTimeStepAction()
    {
        return;
    }

    void KMathRK86::SetInitialConditionAreaAction()
    {
        fConditionAreas[0] = fInitialConditionArea;
        return;
    }

    void KMathRK86::SetFinalConditionAreaAction()
    {
        return;
    }

    void KMathRK86::SetErrorConditionAreaAction()
    {
        return;
    }

    //11 by 11 matrix of coefficients for the linear combination of the derivatives
    const Double_t KMathRK86::fA[eSubsteps - 1][eSubsteps - 1] =
    {
        {   9.0/142.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, //1st row
        {   178422123.0/9178574137.0, 685501333.0/8224473205.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, //2nd row
        {   12257.0/317988.0, 0.0, 12257.0/105996.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, //3rd row
        {   2584949729.0/6554704252.0, 0.0, -9163901916.0/6184003973.0, 26222057794.0/17776421907.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, //4th row
        {   4418011.0/96055225.0, 0.0, 0.0, 2947922107.0/12687381736.0, 3229973413.0/17234960414.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, //5th row
        {   2875139539.0/47877267651.0, 0.0, 0.0, 2702377211.0/24084535832.0, -135707089.0/4042230341.0, 299874140.0/17933325691.0, 0.0, 0.0, 0.0, 0.0, 0.0}, //6th row
        {   -7872176137.0/5003514694.0, 0.0, 0.0, -35136108789.0/26684798878.0, -114433184681.0/9760995895.0, 299204996517.0/32851421233.0, 254.0/39.0, 0.0, 0.0, 0.0, 0.0}, //7th row
        {   -3559950777.0/7399971898.0, 0.0, 0.0, -29299291531.0/4405504148.0, -42434013379.0/9366905709.0, 20642871700.0/5300635453.0, 12951197050.0/1499985011.0, 59527523.0/6331620793.0, 0.0, 0.0, 0.0}, //8th row
        {   -8196723582.0/10570795981.0, 0.0, 0.0, -46181454005.0/5775132776.0, -196277106011.0/29179424052.0, 63575135343.0/11491868333.0, 9348448139.0/857846776.0, 195434294.0/9727139945.0, -617468037.0/15757346105.0, 0.0, 0.0}, //9th row
        {   -6373809055.0/5357779452.0, 0.0, 0.0, -150772749657.0/21151088080.0, -58076657383.0/6089469394.0, 9252721190.0/1221566797.0, 132381309631.0/11748965576.0, 704633904.0/13813696331.0, 656417033.0/8185349658.0, -1669806516.0/10555289849.0, 0.0}, //10th row
        {   -2726346953.0/6954959789.0, 0.0, 0.0, 24906446731.0/6359105161.0, -65277767625.0/23298960463.0, 39128152317.0/16028215273.0, -40638357893.0/16804059016.0, -7437361171.0/21911114743.0, 1040125706.0/5334949109.0, -1129865134.0/5812907645.0, 6253441118.0/10543852725.0} //11th row
    };

    //coefficients for the final 6th order combination of the derivatives
const    Double_t KMathRK86::fAFinal6[eSubsteps] =
        { 289283091.0 / 6008696510.0, 0.0, 0.0, 0.0, 0.0, 3034152487.0 / 7913336319.0, 7170564158.0 / 30263027435.0, 7206303747.0 / 16758195910.0, -1059739258.0 / 8472387467.0, 16534129531.0 / 11550853505.0, -3.0 / 2.0, 5118195927.0 / 53798651926.0 };

    //coefficients for the final 8th order combination of the derivatives
    const Double_t KMathRK86::fAFinal8[eSubsteps] =
        { 438853193.0 / 9881496838.0, 0.0, 0.0, 0.0, 0.0, 11093525429.0 / 31342013414.0, 481311443.0 / 1936695762.0, -3375294558.0 / 10145424253.0, 9830993862.0 / 5116981057.0, -138630849943.0 / 50747474617.0, 7152278206.0 / 5104393345.0, 5118195927.0 / 53798651926.0 };

} // end namespace Kassiopeia
