#include "KTrackProcessPropagation.h"

#include "KTrackExactStepComputer.h"

#include "KMathCompositeODE.h"

#include "KTrackODE.h"
#include "KTrackLorentzODE.h"

namespace Kassiopeia
{

    KTrackProcessPropagation::KTrackProcessPropagation() :
        KTrackProcess(),
        fParent( NULL ),
        fActiveTerm( NULL ),
        fExactTerm( new KTrackLorentzODE() )
    {
    }

    KTrackProcessPropagation::~KTrackProcessPropagation()
    {
        delete fExactTerm;
    }

    Bool_t KTrackProcessPropagation::EnableAction()
    {
        if( fParent->GetCompositeODE()->AddTerm( fActiveTerm ) == kTRUE )
        {
            fActiveTerm->SetParticle( fParent->GetActiveParticle() );
            return kTRUE;
        }
        return kFALSE;
    }
    Bool_t KTrackProcessPropagation::DisableAction()
    {
        if( fParent->GetCompositeODE()->RemoveTerm( fActiveTerm ) == kTRUE )
        {
            fActiveTerm->SetParticle( NULL );
            return kTRUE;
        }
        return kFALSE;
    }

    Bool_t KTrackProcessPropagation::AddParent( KSProcess* aParent )
    {
        KTrackExactStepComputer* ExactStepComputer = NULL;
        ExactStepComputer = dynamic_cast< KTrackExactStepComputer* >( aParent );
        if( ExactStepComputer != NULL )
        {
            fParent = ExactStepComputer;
            fActiveTerm = fExactTerm;
            return kTRUE;
        }

        return kFALSE;
    }

} /* namespace Kassiopeia */
