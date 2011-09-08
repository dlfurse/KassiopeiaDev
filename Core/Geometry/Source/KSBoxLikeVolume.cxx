/*
 * KSBoxLikeVolume.cxx
 *
 * created on: Mar 28, 2011
 * author: dlfurse
 */

#include "KSBoxLikeVolume.h"

#include "KSSurface.h"

namespace Kassiopeia
{

    KSBoxLikeVolume::KSBoxLikeVolume() :
        KSVolume( 6 )
    {
        fSideSurfaces[eSideNumberTop]->SetName( "top" );
        fSideSurfaces[eSideNumberBottom]->SetName( "bottom" );
        fSideSurfaces[eSideNumberFront]->SetName( "front" );
        fSideSurfaces[eSideNumberBack]->SetName( "back" );
        fSideSurfaces[eSideNumberRight]->SetName( "right" );
        fSideSurfaces[eSideNumberLeft]->SetName( "left" );
    }
    KSBoxLikeVolume::~KSBoxLikeVolume()
    {
    }

    //*********************
    //initialization system
    //*********************

    void KSBoxLikeVolume::InitializeVolumeSubclass()
    {
        InitializeTop();
        InitializeBottom();
        InitializeFront();
        InitializeBack();
        InitializeRight();
        InitializeLeft();
        InitializeBoxLikeVolumeSubclass();
        return;
    }

    //*****************
    //structural system
    //*****************

    void KSBoxLikeVolume::GetSideSurface( const Char_t* name, KSSurface** side ) const
    {
        if( strcmp( name, "top" ) == 0 )
        {
            *side = fSideSurfaces[eSideNumberTop];
            return;
        }
        if( strcmp( name, "bottom" ) == 0 )
        {
            *side = fSideSurfaces[eSideNumberBottom];
            return;
        }
        if( strcmp( name, "front" ) == 0 )
        {
            *side = fSideSurfaces[eSideNumberFront];
            return;
        }
        if( strcmp( name, "back" ) == 0 )
        {
            *side = fSideSurfaces[eSideNumberBack];
            return;
        }
        if( strcmp( name, "right" ) == 0 )
        {
            *side = fSideSurfaces[eSideNumberRight];
            return;
        }
        if( strcmp( name, "left" ) == 0 )
        {
            *side = fSideSurfaces[eSideNumberLeft];
            return;
        }
        *side = NULL;
        return;
    }

    void KSBoxLikeVolume::GetTop( KSSurface** side ) const
    {
        *side = fSideSurfaces[eSideNumberTop];
        return;
    }

    void KSBoxLikeVolume::GetBottom( KSSurface** side ) const
    {
        *side = fSideSurfaces[eSideNumberBottom];
        return;
    }

    void KSBoxLikeVolume::GetFront( KSSurface** side ) const
    {
        *side = fSideSurfaces[eSideNumberFront];
        return;
    }

    void KSBoxLikeVolume::GetBack( KSSurface** side ) const
    {
        *side = fSideSurfaces[eSideNumberBack];
        return;
    }

    void KSBoxLikeVolume::GetRight( KSSurface** side ) const
    {
        *side = fSideSurfaces[eSideNumberRight];
        return;
    }

    void KSBoxLikeVolume::GetLeft( KSSurface** side ) const
    {
        *side = fSideSurfaces[eSideNumberLeft];
        return;
    }

}
