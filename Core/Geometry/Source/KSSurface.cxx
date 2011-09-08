/*
 * KSSurface.cxx
 *
 * created on: Feb 17, 2011
 * author: dlfurse
 */

#include "KSSurface.h"

//*******
//surface
//*******

namespace Kassiopeia
{

    KSSurface::KSSurface() :
        KSShape(),
        fVisualizationProperties( NULL ),
        fSurfaceCommandProperties( NULL ),
        fSurfaceElectricalProperties( NULL ),
        fParent( NULL ),
        fArea( 0. )
    {
    }

    KSSurface::~KSSurface()
    {
    }

    //*********************
    //initialization system
    //*********************

    void KSSurface::InitializeGeometrySubclass()
    {
        InitializeSurfaceSubclass();
        InitializeArea();
        return;
    }

    //****************
    //structure system
    //****************

    void KSSurface::AssignParent( const KSVolume* parent )
    {
        fParent = parent;
        return;
    }
    void KSSurface::GetParent( const KSVolume** parent ) const
    {
        *parent = fParent;
        return;
    }

    //******************
    //positioning system
    //******************

    void KSSurface::TransformGeometrySubclass( const KSTransformation* transform )
    {
        TransformSurfaceSubclass( transform );
        return;
    }

    //*****************
    //properties system
    //*****************

    void KSSurface::SetVisualizationProperties( const VisualizationProperties* properties )
    {
        fVisualizationProperties = properties;
        return;
    }
    const VisualizationProperties* KSSurface::GetVisualizationProperties() const
    {
        return fVisualizationProperties;
    }

    void KSSurface::SetCommandProperties( const SurfaceCommandProperties* properties )
    {
        fSurfaceCommandProperties = properties;
        return;
    }
    const SurfaceCommandProperties* KSSurface::GetCommandProperties() const
    {
        return fSurfaceCommandProperties;
    }

    void KSSurface::SetElectricalProperties( const SurfaceElectricalProperties* properties )
    {
        fSurfaceElectricalProperties = properties;
        return;
    }
    const SurfaceElectricalProperties* KSSurface::GetElectricalProperties() const
    {
        return fSurfaceElectricalProperties;
    }

    /* old functions
     void KSSurface::AssignTag( const string& tag )
     {
     TDCIt tIter = fTags.find(tag);
     if (tIter == fTags.end()) {
     fTags.insert( tag );
     std::cout << "assigned tag <" << tag << "> to surface <" << fName << ">" << std::endl;
     }
     return;
     }

     void KSSurface::AssignTags( const TagSet* tags )
     {
     if (tags == NULL) return;
     for (TDCIt tIter = tags->begin(); tIter != tags->end(); tIter++)
     {
     AssignTag( *tIter );
     }
     return;
     }
     */

    //****************
    //geometric system
    //****************
    const Double_t& KSSurface::GetArea() const
    {
        return fArea;
    }

}

//****************
//abstract surface
//****************

namespace Kassiopeia
{

    KSAbstractSurface::KSAbstractSurface() :
        KSAbstractShape()
    {
    }

    KSAbstractSurface::~KSAbstractSurface()
    {
    }

    void KSAbstractSurface::MakeSurface( KSSurface** aNewSurface ) const
    {
        MakeSurfaceSubclass( aNewSurface );
        (*aNewSurface)->AddTagSet( GetTagSet() );
        return;
    }

}
