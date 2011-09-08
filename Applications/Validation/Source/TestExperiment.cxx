#include "Rtypes.h"

#include "KSList.h"

#include <ctime>

#include <iostream>
using std::cout;
using std::endl;

namespace Kassiopeia
{

    namespace Experiment
    {

// array base

        /*
         class KSConstantArray
         {
         public:
         KSConstantArray()
         {
         }
         virtual ~KSConstantArray()
         {
         }

         virtual Double_t CopyValueAt( const size_t& anIndex ) const = 0;
         };
         */

// array
        template< size_t XDimension >
        class KSArray
        {
            public:
                KSArray()
                {
                }
                virtual ~KSArray()
                {
                }

                Double_t operator[]( const size_t& anIndex ) const
                {
                    return fData[anIndex];
                }
                Double_t& operator[]( const size_t& anIndex )
                {
                    return fData[anIndex];
                }

                KSArray< XDimension >& operator=( const Double_t& anOperand )
                {
                    for( size_t Index = 0; Index < XDimension; Index++ )
                    {
                        fData[Index] = anOperand;
                    }
                    return *this;
                }
                template< class XType >
                KSArray< XDimension >& operator=( const XType& anOperand )
                {
                    for( size_t Index = 0; Index < XDimension; Index++ )
                    {
                        fData[Index] = anOperand[Index];
                    }
                    return *this;
                }

                template< class XType >
                KSArray< XDimension >& operator+=( const XType& anOperand )
                {
                    for( size_t Index = 0; Index < XDimension; Index++ )
                    {
                        fData[Index] += anOperand[Index];
                    }
                    return *this;
                }
                template< class XType >
                KSArray< XDimension >& operator-=( const XType& anOperand )
                {
                    for( size_t Index = 0; Index < XDimension; Index++ )
                    {
                        fData[Index] -= anOperand[Index];
                    }
                    return *this;
                }
                KSArray< XDimension >& operator*=( const Double_t& aFactor )
                {
                    for( size_t Index = 0; Index < XDimension; Index++ )
                    {
                        fData[Index] *= aFactor;
                    }
                    return *this;
                }
                KSArray< XDimension >& operator/=( const Double_t& aFactor )
                {
                    for( size_t Index = 0; Index < XDimension; Index++ )
                    {
                        fData[Index] /= aFactor;
                    }
                    return *this;
                }

            private:
                Double_t fData[XDimension];
        };

//expressions

        template< class XLeft, class XRight >
        class KSAddExpression
        {
            public:
                KSAddExpression( const XLeft& aLeftOperand, const XRight& aRightOperand ) :
                    fLeft( aLeftOperand ),
                    fRight( aRightOperand )
                {
                }
                virtual ~KSAddExpression()
                {
                }

                Double_t operator[]( const size_t& anIndex ) const
                {
                    return (fLeft[anIndex] + fRight[anIndex]);
                }

            private:
                const XLeft& fLeft;
                const XRight& fRight;
        };
        template< class XLeft, class XRight >
        KSAddExpression< XLeft, XRight > operator+( const XLeft& aLeftOperand, const XRight& aRightOperand )
        {
            return KSAddExpression< XLeft, XRight >( aLeftOperand, aRightOperand );
        }

        template< class XLeft, class XRight >
        class KSSubtractExpression
        {
            public:
                KSSubtractExpression( const XLeft& aLeftOperand, const XRight& aRightOperand ) :
                    fLeft( aLeftOperand ),
                    fRight( aRightOperand )
                {
                }
                virtual ~KSSubtractExpression()
                {
                }

                Double_t operator[]( const size_t& anIndex ) const
                {
                    return (fLeft[anIndex] - fRight[anIndex]);
                }

            private:
                const XLeft& fLeft;
                const XRight& fRight;
        };
        template< class XLeft, class XRight >
        KSSubtractExpression< XLeft, XRight > operator-( const XLeft& aLeftOperand, const XRight& aRightOperand )
        {
            return KSSubtractExpression< XLeft, XRight >( aLeftOperand, aRightOperand );
        }

        template< class XType >
        class KSMultiplyExpression
        {
            public:
                KSMultiplyExpression( const XType& anOperand, const Double_t& aFactor ) :
                    fOperand( anOperand ),
                    fFactor( aFactor )
                {
                }
                virtual ~KSMultiplyExpression()
                {
                }

                Double_t operator[]( const size_t& anIndex ) const
                {
                    return fOperand[anIndex] * fFactor;
                }

            private:
                const XType& fOperand;
                const Double_t& fFactor;
        };
        template< class XType >
        KSMultiplyExpression< XType > operator*( const XType& anOperand, const Double_t& aFactor )
        {
            return KSMultiplyExpression< XType >( anOperand, aFactor );
        }
        template< class XType >
        KSMultiplyExpression< XType > operator*( const Double_t& aFactor, const XType& anOperand )
        {
            return KSMultiplyExpression< XType >( anOperand, aFactor );
        }

        template< class XType >
        class KSDivideExpression
        {
            public:
                KSDivideExpression( const XType& anOperand, const Double_t& aFactor ) :
                    fOperand( anOperand ),
                    fFactor( aFactor )
                {
                }
                virtual ~KSDivideExpression()
                {
                }

                Double_t operator[]( const size_t& anIndex ) const
                {
                    return fOperand.CopyValueAt( anIndex ) / fFactor;
                }

            private:
                const XType& fOperand;
                const Double_t& fFactor;

        };
        template< class XType >
        KSDivideExpression< XType > operator/( const XType& anOperand, const Double_t& aFactor )
        {
            return KSDivideExpression< XType >( anOperand, aFactor );
        }

// ode system

        template< class XConditionType, class XDerivativeType, class XErrorType >
        class KMathODESystem
        {
            public:
                typedef XConditionType ConditionType;
                typedef XDerivativeType DerivativeType;
                typedef XErrorType ErrorType;
        };

// ode

        template< class XSystemType >
        class KMathODE
        {
            public:
                typedef XSystemType SystemType;
                typedef typename SystemType::ConditionType ConditionType;
                typedef typename SystemType::DerivativeType DerivativeType;
                typedef typename SystemType::ErrorType ErrorType;

            public:
                KMathODE() :
                    fConditionArea( NULL ),
                    fDerivativeArea( NULL )
                {
                }
                virtual ~KMathODE()
                {
                }

                virtual void CalculateDerivative() = 0;

                virtual void SetConditionArea( ConditionType* aConditionArea )
                {
                    fConditionArea = aConditionArea;
                    return;
                }
                virtual void SetDerivativeArea( DerivativeType* aDerivativeArea )
                {
                    fDerivativeArea = aDerivativeArea;
                    return;
                }

            protected:
                ConditionType* fConditionArea;
                DerivativeType* fDerivativeArea;
        };

// ode composite

        template< class XSystemType >
        class KMathCompositeODE :
            public KMathODE< XSystemType >
        {
            public:
                typedef XSystemType SystemType;
                typedef KMathODE< SystemType > ParentType;
                typedef KMathODE< SystemType > TermType;
                typedef typename SystemType::ConditionType ConditionType;
                typedef typename SystemType::DerivativeType DerivativeType;
                typedef typename SystemType::ErrorType ErrorType;

            public:
                KMathCompositeODE() :
                    fCurrentTerm( 0 ),
                    fEndTerm( 0 )
                {
                    for( fCurrentTerm = 0; fCurrentTerm < eMaxTerms; fCurrentTerm++ )
                    {
                        fTerms[fCurrentTerm] = NULL;
                        fDerivatives[fCurrentTerm] = NULL;
                    }
                }
                virtual ~KMathCompositeODE()
                {
                    for( fCurrentTerm = 0; fCurrentTerm < eMaxTerms; fCurrentTerm++ )
                    {
                        if( fDerivatives[fCurrentTerm] != NULL )
                        {
                            delete fDerivatives[fCurrentTerm];
                            fDerivatives[fCurrentTerm] = NULL;
                        }
                    }
                }

                virtual Bool_t AddTerm( TermType* aTerm )
                {
                    if( fEndTerm == eMaxTerms )
                    {
                        return kFALSE;
                    }
                    fDerivatives[fEndTerm] = new DerivativeType();
                    fTerms[fEndTerm] = aTerm;
                    fTerms[fEndTerm]->SetDerivativeArea( fDerivatives[fEndTerm] );
                    fEndTerm++;
                    return kTRUE;
                }
                virtual Bool_t RemoveTerm( TermType* aTerm )
                {
                    Bool_t TermFound = kFALSE;
                    for( fCurrentTerm = 0; fCurrentTerm < fEndTerm; fCurrentTerm++ )
                    {
                        if( TermFound == kFALSE )
                        {
                            if( fTerms[fCurrentTerm] == aTerm )
                            {
                                delete fDerivatives[fCurrentTerm];
                                fDerivatives[fCurrentTerm] = NULL;
                                fTerms[fCurrentTerm] = NULL;
                                TermFound = kTRUE;
                            }
                            continue;
                        }
                        fTerms[fCurrentTerm - 1] = fTerms[fCurrentTerm];
                    }
                    if( TermFound == kTRUE )
                    {
                        fEndTerm--;
                        fTerms[fEndTerm] = NULL;
                        return kTRUE;
                    }
                    return kFALSE;
                }

                virtual void CalculateDerivative()
                {
                    (*ParentType::fDerivativeArea) = 0.;
                    for( fCurrentTerm = 0; fCurrentTerm < fEndTerm; fCurrentTerm++ )
                    {
                        fTerms[fCurrentTerm]->CalculateDerivative();
                        (*ParentType::fDerivativeArea) += (*fDerivatives[fCurrentTerm]);
                    }
                    return;
                }

                virtual void SetConditionArea( ConditionType* aConditionArea )
                {
                    ParentType::fConditionArea = aConditionArea;
                    for( fCurrentTerm = 0; fCurrentTerm < fEndTerm; fCurrentTerm++ )
                    {
                        fTerms[fCurrentTerm]->SetConditionArea( ParentType::fConditionArea );
                    }
                    return;
                }
                virtual void SetDerivativeArea( DerivativeType* aDerivativeArea )
                {
                    ParentType::fDerivativeArea = aDerivativeArea;
                    return;
                }

            protected:
                enum
                {
                    eMaxTerms = 64
                };
                size_t fCurrentTerm;
                size_t fEndTerm;
                TermType* fTerms[eMaxTerms];
                DerivativeType* fDerivatives[eMaxTerms];
        };

// ode solver

        template< class XSystemType >
        class KMathODESolver
        {
            public:
                typedef XSystemType SystemType;
                typedef KMathODE< SystemType > ODEType;
                typedef typename SystemType::ConditionType ConditionType;
                typedef typename SystemType::DerivativeType DerivativeType;
                typedef typename SystemType::ErrorType ErrorType;

            public:
                KMathODESolver() :
                    fCalculator( NULL )
                {
                }
                virtual ~KMathODESolver()
                {
                }

                virtual void CalculateSolution() = 0;

                virtual void SetCalculator( ODEType* aCalculator )
                {
                    fCalculator = aCalculator;
                    return;
                }
                virtual void SetStepSize( const Double_t& aStepSize )
                {
                    fStepSize = aStepSize;
                    return;
                }

                virtual void SetInitialConditionArea( ConditionType* anInitialConditionArea )
                {
                    fInitialConditionArea = anInitialConditionArea;
                    return;
                }
                virtual void SetFinalConditionArea( ConditionType* aFinalConditionArea )
                {
                    fFinalConditionArea = aFinalConditionArea;
                    return;
                }
                virtual void SetErrorArea( ErrorType* anErrorArea )
                {
                    fErrorArea = anErrorArea;
                    return;
                }

            protected:
                ODEType* fCalculator;
                Double_t fStepSize;

                ConditionType* fInitialConditionArea;
                ConditionType* fFinalConditionArea;
                ErrorType* fErrorArea;
        };

// rk8

        template< class XSystemType >
        class KMathRK8 :
            public KMathODESolver< XSystemType >
        {
            public:
                typedef XSystemType SystemType;
                typedef KMathODESolver< SystemType > ParentType;
                typedef KMathODE< SystemType > CalculatorType;
                typedef typename SystemType::ConditionType ConditionType;
                typedef typename SystemType::DerivativeType DerivativeType;
                typedef typename SystemType::ErrorType ErrorType;

            public:
                KMathRK8()
                {
                }
                virtual ~KMathRK8()
                {
                }

                virtual void CalculateSolution()
                {

                    ParentType::fCalculator->SetConditionArea( ParentType::fInitialConditionArea );
                    ParentType::fCalculator->SetDerivativeArea( &fDerivativeAreas[0] );
                    ParentType::fCalculator->CalculateDerivative();

                    fConditionAreas[0] = (*ParentType::fInitialConditionArea) + ParentType::fStepSize * (fA[0][0] * fDerivativeAreas[0]);

                    ParentType::fCalculator->SetConditionArea( &fConditionAreas[0] );
                    ParentType::fCalculator->SetDerivativeArea( &fDerivativeAreas[1] );
                    ParentType::fCalculator->CalculateDerivative();

                    fConditionAreas[1] = (*ParentType::fInitialConditionArea) + ParentType::fStepSize * (fA[1][0] * fDerivativeAreas[0] + fA[1][1] * fDerivativeAreas[1]);

                    ParentType::fCalculator->SetConditionArea( &fConditionAreas[1] );
                    ParentType::fCalculator->SetDerivativeArea( &fDerivativeAreas[2] );
                    ParentType::fCalculator->CalculateDerivative();

                    fConditionAreas[2] = (*ParentType::fInitialConditionArea) + ParentType::fStepSize * (fA[2][0] * fDerivativeAreas[0] + fA[2][1] * fDerivativeAreas[1] + fA[2][2] * fDerivativeAreas[2]);

                    ParentType::fCalculator->SetConditionArea( &fConditionAreas[2] );
                    ParentType::fCalculator->SetDerivativeArea( &fDerivativeAreas[3] );
                    ParentType::fCalculator->CalculateDerivative();

                    fConditionAreas[3] = (*ParentType::fInitialConditionArea) + ParentType::fStepSize * (fA[3][0] * fDerivativeAreas[0] + fA[3][1] * fDerivativeAreas[1] + fA[3][2] * fDerivativeAreas[2] + fA[3][3] * fDerivativeAreas[3]);

                    ParentType::fCalculator->SetConditionArea( &fConditionAreas[3] );
                    ParentType::fCalculator->SetDerivativeArea( &fDerivativeAreas[4] );
                    ParentType::fCalculator->CalculateDerivative();

                    fConditionAreas[4] = (*ParentType::fInitialConditionArea) + ParentType::fStepSize * (fA[4][0] * fDerivativeAreas[0] + fA[4][1] * fDerivativeAreas[1] + fA[4][2] * fDerivativeAreas[2] + fA[4][3] * fDerivativeAreas[3] + fA[4][4] * fDerivativeAreas[4]);

                    ParentType::fCalculator->SetConditionArea( &fConditionAreas[4] );
                    ParentType::fCalculator->SetDerivativeArea( &fDerivativeAreas[5] );
                    ParentType::fCalculator->CalculateDerivative();

                    fConditionAreas[5] = (*ParentType::fInitialConditionArea) + ParentType::fStepSize * (fA[5][0] * fDerivativeAreas[0] + fA[5][1] * fDerivativeAreas[1] + fA[5][2] * fDerivativeAreas[2] + fA[5][3] * fDerivativeAreas[3] + fA[5][4] * fDerivativeAreas[4] + fA[5][5] * fDerivativeAreas[5]);

                    ParentType::fCalculator->SetConditionArea( &fConditionAreas[5] );
                    ParentType::fCalculator->SetDerivativeArea( &fDerivativeAreas[6] );
                    ParentType::fCalculator->CalculateDerivative();

                    fConditionAreas[6] = (*ParentType::fInitialConditionArea) + ParentType::fStepSize * (fA[6][0] * fDerivativeAreas[0] + fA[6][1] * fDerivativeAreas[1] + fA[6][2] * fDerivativeAreas[2] + fA[6][3] * fDerivativeAreas[3] + fA[6][4] * fDerivativeAreas[4] + fA[6][5] * fDerivativeAreas[5] + fA[6][6] * fDerivativeAreas[6]);

                    ParentType::fCalculator->SetConditionArea( &fConditionAreas[6] );
                    ParentType::fCalculator->SetDerivativeArea( &fDerivativeAreas[7] );
                    ParentType::fCalculator->CalculateDerivative();

                    fConditionAreas[7] = (*ParentType::fInitialConditionArea) + ParentType::fStepSize * (fA[7][0] * fDerivativeAreas[0] + fA[7][1] * fDerivativeAreas[1] + fA[7][2] * fDerivativeAreas[2] + fA[7][3] * fDerivativeAreas[3] + fA[7][4] * fDerivativeAreas[4] + fA[7][5] * fDerivativeAreas[5] + fA[7][6] * fDerivativeAreas[6] + fA[7][7] * fDerivativeAreas[7]);

                    ParentType::fCalculator->SetConditionArea( &fConditionAreas[7] );
                    ParentType::fCalculator->SetDerivativeArea( &fDerivativeAreas[8] );
                    ParentType::fCalculator->CalculateDerivative();

                    fConditionAreas[8] = (*ParentType::fInitialConditionArea) + ParentType::fStepSize * (fA[8][0] * fDerivativeAreas[0] + fA[8][1] * fDerivativeAreas[1] + fA[8][2] * fDerivativeAreas[2] + fA[8][3] * fDerivativeAreas[3] + fA[8][4] * fDerivativeAreas[4] + fA[8][5] * fDerivativeAreas[5] + fA[8][6] * fDerivativeAreas[6] + fA[8][7] * fDerivativeAreas[7] + fA[8][8] * fDerivativeAreas[8]);

                    ParentType::fCalculator->SetConditionArea( &fConditionAreas[8] );
                    ParentType::fCalculator->SetDerivativeArea( &fDerivativeAreas[9] );
                    ParentType::fCalculator->CalculateDerivative();

                    fConditionAreas[9] = (*ParentType::fInitialConditionArea) + ParentType::fStepSize * (fA[9][0] * fDerivativeAreas[0] + fA[9][1] * fDerivativeAreas[1] + fA[9][2] * fDerivativeAreas[2] + fA[9][3] * fDerivativeAreas[3] + fA[9][4] * fDerivativeAreas[4] + fA[9][5] * fDerivativeAreas[5] + fA[9][6] * fDerivativeAreas[6] + fA[9][7] * fDerivativeAreas[7] + fA[9][8] * fDerivativeAreas[8] + fA[9][9] * fDerivativeAreas[9]);

                    ParentType::fCalculator->SetConditionArea( &fConditionAreas[9] );
                    ParentType::fCalculator->SetDerivativeArea( &fDerivativeAreas[10] );
                    ParentType::fCalculator->CalculateDerivative();

                    fConditionAreas[10] = (*ParentType::fInitialConditionArea) + ParentType::fStepSize * (fA[10][0] * fDerivativeAreas[0] + fA[10][1] * fDerivativeAreas[1] + fA[10][2] * fDerivativeAreas[2] + fA[10][3] * fDerivativeAreas[3] + fA[10][4] * fDerivativeAreas[4] + fA[10][5] * fDerivativeAreas[5] + fA[10][6] * fDerivativeAreas[6] + fA[10][7] * fDerivativeAreas[7] + fA[10][8] * fDerivativeAreas[8] + fA[10][9] * fDerivativeAreas[9] + fA[10][10] * fDerivativeAreas[10]);

                    ParentType::fCalculator->SetConditionArea( &fConditionAreas[10] );
                    ParentType::fCalculator->SetDerivativeArea( &fDerivativeAreas[11] );
                    ParentType::fCalculator->CalculateDerivative();

                    fConditionAreas[11] = (*ParentType::fInitialConditionArea) + ParentType::fStepSize * (fA[11][0] * fDerivativeAreas[0] + fA[11][1] * fDerivativeAreas[1] + fA[11][2] * fDerivativeAreas[2] + fA[11][3] * fDerivativeAreas[3] + fA[11][4] * fDerivativeAreas[4] + fA[11][5] * fDerivativeAreas[5] + fA[11][6] * fDerivativeAreas[6] + fA[11][7] * fDerivativeAreas[7] + fA[11][8] * fDerivativeAreas[8] + fA[11][9] * fDerivativeAreas[9] + fA[11][10] * fDerivativeAreas[10] + fA[11][11] * fDerivativeAreas[11]);

                    ParentType::fCalculator->SetConditionArea( &fConditionAreas[11] );
                    ParentType::fCalculator->SetDerivativeArea( &fDerivativeAreas[12] );
                    ParentType::fCalculator->CalculateDerivative();

                    *ParentType::fFinalConditionArea = (*ParentType::fInitialConditionArea) + ParentType::fStepSize * (fA[12][0] * fDerivativeAreas[0] + fA[12][1] * fDerivativeAreas[1] + fA[12][2] * fDerivativeAreas[2] + fA[12][3] * fDerivativeAreas[3] + fA[12][4] * fDerivativeAreas[4] + fA[12][5] * fDerivativeAreas[5] + fA[12][6] * fDerivativeAreas[6] + fA[12][7] * fDerivativeAreas[7] + fA[12][8] * fDerivativeAreas[8] + fA[12][9] * fDerivativeAreas[9] + fA[12][10] * fDerivativeAreas[10] + fA[12][11] * fDerivativeAreas[11] + fA[12][12] * fDerivativeAreas[12]);

                    return;
                }

            private:
                ConditionType fConditionAreas[12];
                DerivativeType fDerivativeAreas[13];
                static const Double_t fA[13][13];
        }
        ;

        template< class XSystemType >
        const Double_t KMathRK8< XSystemType >::fA[13][13] =
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

    }

}

using namespace Kassiopeia::Experiment;

class SimpleODESystem :
    public KMathODESystem< KSArray< 3 >, KSArray< 3 >, KSArray< 3 > >
{
};

class SimpleODE :
    public KMathODE< SimpleODESystem >
{
    public:
        SimpleODE() :
            KMathODE< SimpleODESystem >()
        {
        }
        virtual ~SimpleODE()
        {
        }

        virtual void CalculateDerivative()
        {
            ConditionType& Condition = *fConditionArea;
            DerivativeType& Derivative = *fDerivativeArea;

            Derivative[0] = Condition[1] - Condition[2];
            Derivative[1] = Condition[0] * Condition[0] + Condition[1];
            Derivative[2] = Condition[0] * Condition[0] + Condition[2];
            return;
        }
};

class SimpleODETerm :
    public KMathODE< SimpleODESystem >
{
    public:
        SimpleODETerm() :
            KMathODE< SimpleODESystem >()
        {
        }
        virtual ~SimpleODETerm()
        {
        }

        virtual void CalculateDerivative()
        {
            ConditionType& Condition = *fConditionArea;
            DerivativeType& Derivative = *fDerivativeArea;

            Derivative[0] = (Condition[1] - Condition[2]) / 2.;
            Derivative[1] = (Condition[0] * Condition[0] + Condition[1]) / 2.;
            Derivative[2] = (Condition[0] * Condition[0] + Condition[2]) / 2.;
            return;
        }
};

int main()
{

    cout.precision( 20 );

    KMathCompositeODE< SimpleODESystem > ODEComposite;
    SimpleODETerm ODETermOne;
    SimpleODETerm ODETermTwo;

    ODEComposite.AddTerm( &ODETermOne );
    ODEComposite.AddTerm( &ODETermTwo );

    KMathRK8< SimpleODESystem > ODESolver;

    SimpleODESystem::ConditionType Condition;
    Condition[0] = 0.60053674020464398176;
    Condition[1] = -0.36438085383035950793;
    Condition[2] = -0.36491759403500345638;

    ODESolver.SetCalculator( &ODEComposite );
    ODESolver.SetInitialConditionArea( &Condition );
    ODESolver.SetFinalConditionArea( &Condition );
    ODESolver.SetStepSize( .00001 );

    cout << "initial:\n";
    cout << "  [ " << Condition[0] << ", " << Condition[1] << ", " << Condition[2] << " ]" << endl;

    UInt_t StepCount = 0;

    clock_t StartTime = clock();

    while( StepCount < 1000000 )
    {
        ODESolver.CalculateSolution();
        StepCount++;
    }

    clock_t EndTime = clock();

    cout << "step counts:\n";
    cout << "  " << StepCount << "\n";
    cout << "clock ticks:\n";
    cout << "  " << EndTime - StartTime << "\n";
    cout << "final:\n";
    cout << "  [ " << Condition[0] << ", " << Condition[1] << ", " << Condition[2] << " ]" << endl;

//

    return 0;
}

