/*
 *  KSPlacement.cxx
 *  Kassiopeia
 *
 *  Created by Noah Oblath on 6/22/11.
 *
 */

#include "KSPlacement.h"

#include "KSTransformation.h"

//***********
//KSPlacement
//***********

namespace Kassiopeia
{

    KSPlacement::KSPlacement() :
        fTransformation( NULL )
    {
    }
    KSPlacement::~KSPlacement()
    {
        if( fTransformation != NULL )
        {
            delete fTransformation;
            fTransformation = NULL;
        }
    }

    void KSPlacement::SetTransformation( const KSTransformation* aTransformation )
    {
        fTransformation = aTransformation;
        return;
    }
    const KSTransformation* KSPlacement::GetTransformation() const
    {
        return fTransformation;
    }

}
