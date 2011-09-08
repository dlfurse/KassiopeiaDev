#include "KSVolume.h"
#include "KSSurface.h"

//******
//volume
//******

namespace Kassiopeia
{

    KSVolume::KSVolume( const UInt_t& sidecount ) :
        KSShape(),
        fVisualizationProperties( NULL ),
        fVolumeCommandProperties( NULL ),
        fVolumeElectricalProperties( NULL ),
        fSideSurfaces( NULL ),
        fSideSurfaceCount( 0 ),
        fParent( NULL ),
        fChildSurfaces( NULL ),
        fChildSurfaceCount( 0 ),
        fChildVolumes( NULL ),
        fChildVolumeCount( 0 ),
        fCapacity( 0. ),
        fArea( 0. )
    {
        if( sidecount != 0 )
        {
            fSideSurfaceCount = sidecount;
            fSideSurfaces = new KSSurface*[fSideSurfaceCount];
            for( UInt_t Index = 0; Index < fSideSurfaceCount; Index++ )
            {
                fSideSurfaces[Index] = NULL;
            }
        }
    }
    KSVolume::KSVolume()
    {
    }
    KSVolume::~KSVolume()
    {
        UInt_t Index;

        if( fSideSurfaces != 0 )
        {
            for( Index = 0; Index < fSideSurfaceCount; Index++ )
            {
                if( fSideSurfaces[Index] != 0 )
                {
                    delete fSideSurfaces[Index];
                    fSideSurfaces[Index] = 0;
                }
            }
            delete[] fSideSurfaces;
            fSideSurfaceCount = 0;
        }

        if( fChildVolumes != 0 )
        {
            for( Index = 0; Index < fChildVolumeCount; Index++ )
            {
                if( fChildVolumes[Index] != 0 )
                {
                    delete fChildVolumes[Index];
                    fChildVolumes[Index] = 0;
                }
            }
            delete[] fChildVolumes;
            fChildVolumes = 0;
        }

        if( fChildSurfaces != 0 )
        {
            for( Index = 0; Index < fChildSurfaceCount; Index++ )
            {
                if( fChildSurfaces[Index] != 0 )
                {
                    delete fChildSurfaces[Index];
                    fChildSurfaces[Index] = 0;
                }
            }
            delete[] fChildSurfaces;
            fChildSurfaces = 0;
        }
    }

    //*********************
    //initialization system
    //*********************

    void KSVolume::InitializeGeometrySubclass()
    {
        InitializeVolumeSubclass();
        InitializeCapacityAndArea();
        return;
    }

    //*****************
    //properties system
    //*****************

    void KSVolume::AssignVisualizationProperties( const VisualizationProperties* properties )
    {
        fVisualizationProperties = properties;
        return;
    }
    const VisualizationProperties* KSVolume::GetVisualizationProperties() const
    {
        return fVisualizationProperties;
    }

    void KSVolume::AssignVolumeCommandProperties( const VolumeCommandProperties* properties )
    {
        fVolumeCommandProperties = properties;
        return;
    }
    const VolumeCommandProperties* KSVolume::GetVolumeCommandProperties() const
    {
        return fVolumeCommandProperties;
    }

    void KSVolume::AssignVolumeElectricalProperties( const VolumeElectricalProperties* properties )
    {
        fVolumeElectricalProperties = properties;
        return;
    }
    const VolumeElectricalProperties* KSVolume::GetVolumeElectricalProperties() const
    {
        return fVolumeElectricalProperties;
    }

    /* old functions
     void KSVolume::AssignTag( const string& tag )
     {
     TDCIt tIter = fTags.find(tag);
     if (tIter == fTags.end()) {
     fTags.insert( tag );
     std::cout << "assigned tag <" << tag << "> to volume <" << fName << ">" << std::endl;
     for( UInt_t iSide = 0; iSide < fSideSurfaceCount; iSide++ )
     {
     fSideSurfaces[iSide]->AssignTag( tag );
     }
     }
     return;
     }

     void KSVolume::AssignTags( const TagSet* tags )
     {
     if (tags == NULL) return;
     for (TDCIt tIter = tags->begin(); tIter != tags->end(); tIter++)
     {
     AssignTag( *tIter );
     }
     return;
     }

     void KSVolume::SetVisualizationProperties( const VisualizationProperties* properties )
     {
     fVisualizationProperties = properties;
     for( UInt_t Index = 0; Index < fSideSurfaceCount; Index++ )
     {
     fSideSurfaces[Index]->SetVisualizationProperties(properties);
     }
     return;
     }

     void KSVolume::SetVisualizationProperties( const VisualizationProperties* properties, const Char_t* sidename)
     {
     KSSurface* Side;
     GetSideSurface(&Side, sidename);
     if (Side) Side->SetVisualizationProperties(properties);
     return;
     }

     const VisualizationProperties* KSVolume::GetVisualizationProperties( const Char_t* sidename) const
     {
     KSSurface* Side;
     GetSideSurface(&Side, sidename);
     if (Side) return Side->GetVisualizationProperties();
     return NULL;
     }

     const VisualizationProperties* KSVolume::GetVisualizationProperties() const
     {
     return fVisualizationProperties;
     }

     void KSVolume::AssignVolumeCommandProperties( const VolumeCommandProperties* properties )
     {
     fVolumeCommandProperties = properties;
     return;
     }
     const VolumeCommandProperties* KSVolume::GetVolumeCommandProperties() const
     {
     return fVolumeCommandProperties;
     }
     */

    //*****************
    //structural system
    //*****************
    void KSVolume::GetSideSurfaces( KSSurface*** sides, UInt_t* count ) const
    {
        *sides = fSideSurfaces;
        *count = fSideSurfaceCount;
        return;
    }
    void KSVolume::AssignParent( KSVolume* parent )
    {
        fParent = parent;
        return;
    }
    void KSVolume::GetParent( KSVolume** parent ) const
    {
        *parent = fParent;
        return;
    }
    void KSVolume::AssignChildVolumes( KSVolume** children, UInt_t& count )
    {
        fChildVolumes = children;
        fChildVolumeCount = count;

        /* old implementation
         if (fChildVolumeCount == 0)
         {
         fChildVolumes = children;
         fChildVolumeCount = count;
         }
         else
         {
         // temporarily point to the old array
         KSVolume** tOldChildVolumes = fChildVolumes;
         UInt_t tOldChildVolumeCount = fChildVolumeCount;

         // make the new array
         fChildVolumeCount += count;
         fChildVolumes = new KSVolume*[fChildVolumeCount];
         // transfer the pointers from the old array
         for (UInt_t iChild=0; iChild < tOldChildVolumeCount; iChild++)
         {
         fChildVolumes[iChild] = tOldChildVolumes[iChild];
         }
         // transfer the pointers from the incoming array
         for (UInt_t iChild=tOldChildVolumeCount; iChild < fChildVolumeCount; iChild++)
         {
         fChildVolumes[iChild] = children[iChild - tOldChildVolumeCount];
         }

         // delete the old array and the incoming array (but not the children pointed to!)
         delete [] tOldChildVolumes;
         delete [] children;
         }
         */

        return;
    }
    void KSVolume::GetChildVolumes( KSVolume*** children, UInt_t* count ) const
    {
        *children = fChildVolumes;
        *count = fChildVolumeCount;
        return;
    }

    void KSVolume::AssignChildSurfaces( KSSurface** children, UInt_t& count )
    {
        fChildSurfaces = children;
        fChildSurfaceCount = count;

        /* old implementation
         if (fChildSurfaceCount == 0)
         {
         fChildSurfaces = children;
         fChildSurfaceCount = count;
         }
         else
         {
         KSSurface** tOldChildSurfaces = fChildSurfaces;
         UInt_t tOldChildSurfaceCount = fChildSurfaceCount;

         // make the new array
         fChildSurfaceCount += count;
         fChildSurfaces = new KSSurface*[fChildSurfaceCount];
         // transfer the pointers from the old array
         for (UInt_t iChild=0; iChild < tOldChildSurfaceCount; iChild++)
         {
         fChildSurfaces[iChild] = tOldChildSurfaces[iChild];
         }
         // transfer the pointers from the incoming array
         for (UInt_t iChild=tOldChildSurfaceCount; iChild < fChildSurfaceCount; iChild++)
         {
         fChildSurfaces[iChild] = children[iChild - tOldChildSurfaceCount];
         }

         // delete the old array and the incoming array (but not the children pointed to!)
         delete [] tOldChildSurfaces;
         delete [] children;
         }
         */

        return;
    }
    void KSVolume::GetChildSurfaces( KSSurface*** children, UInt_t* count ) const
    {
        *children = fChildSurfaces;
        *count = fChildSurfaceCount;
        return;
    }

    //******************
    //positioning system
    //******************

    void KSVolume::TransformGeometrySubclass( const KSTransformation* transform )
    {
        UInt_t Index;

        if( fSideSurfaces != 0 )
        {
            for( Index = 0; Index < fSideSurfaceCount; Index++ )
            {
                fSideSurfaces[Index]->Transform( transform );
            }
        }
        if( fChildVolumes != 0 )
        {
            for( Index = 0; Index < fChildVolumeCount; Index++ )
            {
                fChildVolumes[Index]->Transform( transform );
            }
        }
        if( fChildSurfaces != 0 )
        {
            for( Index = 0; Index < fChildSurfaceCount; Index++ )
            {
                fChildSurfaces[Index]->Transform( transform );
            }

        }

        TransformVolumeSubclass( transform );

        return;
    }

    //****************
    //geometric system
    //****************

    const Double_t& KSVolume::GetCapacity() const
    {
        return fCapacity;
    }
    const Double_t& KSVolume::GetArea() const
    {
        return fArea;
    }

}

//***************
//abstract volume
//***************

namespace Kassiopeia
{

    KSAbstractVolume::KSAbstractVolume() :
        KSAbstractShape()
    {
    }

    KSAbstractVolume::~KSAbstractVolume()
    {
    }

    void KSAbstractVolume::MakeVolume( KSVolume** aNewVolume ) const
    {
        MakeVolumeSubclass( aNewVolume );
        (*aNewVolume)->AddTagSet( GetTagSet() );
        return;
    }

}

