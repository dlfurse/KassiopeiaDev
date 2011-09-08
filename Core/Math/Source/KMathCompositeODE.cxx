#include "KMathCompositeODE.h"

namespace Kassiopeia
{

    KMathCompositeODE::KMathCompositeODE( const size_t& aDimension ) :
        KMathODE( aDimension ),
        fCurrentTerm( 0 ),
        fEndTerm( 0 )
    {
        for( fCurrentTerm = 0; fCurrentTerm < eMaxTerms; fCurrentTerm++ )
        {
            fTerms[fCurrentTerm] = NULL;
            fTermDerivatives[fCurrentTerm] = NULL;
        }
    }

    KMathCompositeODE::~KMathCompositeODE()
    {
        for( fCurrentTerm = 0; fCurrentTerm < eMaxTerms; fCurrentTerm++ )
        {
            if( fTermDerivatives[fCurrentTerm] != NULL )
            {
                delete[] fTermDerivatives[fCurrentTerm];
                fTermDerivatives[fCurrentTerm] = NULL;
            }
        }
    }

    Bool_t KMathCompositeODE::AddTerm( KMathODE* aTerm )
    {
        if( fEndTerm == eMaxTerms )
        {
            return kFALSE;
        }
        fTerms[fEndTerm] = aTerm;
        fTermDerivatives[fEndTerm] = new Double_t[GetDimension()];
        fTerms[fEndTerm]->SetDerivativeArea( fTermDerivatives[fEndTerm] );
        fEndTerm++;
        return kTRUE;
    }

    Bool_t KMathCompositeODE::RemoveTerm( KMathODE* aTerm )
    {
        Bool_t TermFound = kFALSE;
        for( fCurrentTerm = 0; fCurrentTerm < fEndTerm; fCurrentTerm++ )
        {
            if( TermFound == kFALSE )
            {
                if( fTerms[fCurrentTerm] == aTerm )
                {
                    delete[] fTermDerivatives[fCurrentTerm];
                    fTermDerivatives[fCurrentTerm] = NULL;
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

    void KMathCompositeODE::CalculateDerivative()
    {
        for( size_t Index = 0; Index < GetDimension(); Index++ )
        {
            fDerivativeArea[Index] = 0;
        }

        for( fCurrentTerm = 0; fCurrentTerm < fEndTerm; fCurrentTerm++ )
        {
            fTerms[fCurrentTerm]->CalculateDerivative();
            for( size_t Index = 0; Index < GetDimension(); Index++ )
            {
                fDerivativeArea[Index] += fTermDerivatives[fCurrentTerm][Index];
            }
        }

        return;
    }

    void KMathCompositeODE::SetConditionAreaAction()
    {
        for( fCurrentTerm = 0; fCurrentTerm < fEndTerm; fCurrentTerm++ )
        {
            fTerms[fCurrentTerm]->SetConditionArea( fConditionArea );
        }
        return;
    }

    void KMathCompositeODE::SetDerivativeAreaAction()
    {
        return;
    }

}
