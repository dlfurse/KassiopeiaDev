#include "KSGeometryToolbox.h"

#include "KSShape.h"
#include "KSSurface.h"
#include "KSVolume.h"
#include "KSAssembly.h"

namespace Kassiopeia
{

    const string KSGeometryToolbox::fTypeName = string( "KSGeometryToolbox" );

    KSGeometryToolbox::KSGeometryToolbox() :
        fASMap(),
        fAVMap(),
        fAMap(),
        fTagGroupMap(),
        fWorldVolume( NULL )
    {
    }
    KSGeometryToolbox::~KSGeometryToolbox()
    {
        ASIt anASIt;
        for( anASIt = fASMap.begin(); anASIt != fASMap.end(); anASIt++ )
        {
            if( anASIt->second != NULL )
            {
                delete anASIt->second;
                anASIt->second = NULL;
            }
        }

        AVIt anAVIt;
        for( anAVIt = fAVMap.begin(); anAVIt != fAVMap.end(); anAVIt++ )
        {
            if( anAVIt->second != NULL )
            {
                delete anAVIt->second;
                anAVIt->second = NULL;
            }
        }

        AIt anAIt;
        for( anAIt = fAMap.begin(); anAIt != fAMap.end(); anAIt++ )
        {
            if( anAIt->second != NULL )
            {
                delete anAIt->second;
                anAIt->second = NULL;
            }
        }

        TagGroupMapIt aTagGroupMapIt;
        for( aTagGroupMapIt = fTagGroupMap.begin(); aTagGroupMapIt != fTagGroupMap.end(); aTagGroupMapIt++ )
        {
            if( aTagGroupMapIt->second != NULL )
            {
                delete aTagGroupMapIt->second;
                aTagGroupMapIt->second = NULL;
            }
        }

        if( fWorldVolume != NULL )
        {
            delete fWorldVolume;
            fWorldVolume = NULL;
        }
    }

    void KSGeometryToolbox::SetupManager()
    {
        return;
    }
    void KSGeometryToolbox::PrepareManager()
    {
        return;
    }
    void KSGeometryToolbox::ShutdownManager()
    {
        return;
    }

    const string& KSGeometryToolbox::GetTypeName() const
    {
        return fTypeName;
    }
    const string& KSGeometryToolbox::GetStaticTypeName()
    {
        return fTypeName;
    }

    void KSGeometryToolbox::AddAbstractSurface( const KSAbstractSurface* aSurface )
    {
        ASIt anASIt = fASMap.find( aSurface->GetName() );
        if( anASIt != fASMap.end() )
        {
            fASMap.insert( ASEntry( aSurface->GetName(), aSurface ) );
        }
        return;
    }
    const KSAbstractSurface* KSGeometryToolbox::GetAbstractSurface( const string& aName ) const
    {
        ASCIt anASCIt = fASMap.find( aName );
        if( anASCIt != fASMap.end() )
        {
            return anASCIt->second;
        }
        return NULL;
    }

    void KSGeometryToolbox::AddAbstractVolume( const KSAbstractVolume* aVolume )
    {
        AVIt anAVIt = fAVMap.find( aVolume->GetName() );
        if( anAVIt != fAVMap.end() )
        {
            fAVMap.insert( AVEntry( aVolume->GetName(), aVolume ) );
        }
        return;
    }
    const KSAbstractVolume* KSGeometryToolbox::GetAbstractVolume( const string& aName ) const
    {
        AVCIt anAVCIt = fAVMap.find( aName );
        if( anAVCIt != fAVMap.end() )
        {
            return anAVCIt->second;
        }
        return NULL;
    }

    void KSGeometryToolbox::AddAssembly( const KSAssembly* aAssembly )
    {
        AIt anAIt = fAMap.find( aAssembly->GetName() );
        if( anAIt != fAMap.end() )
        {
            fAMap.insert( AEntry( aAssembly->GetName(), aAssembly ) );
        }
        return;
    }
    const KSAssembly* KSGeometryToolbox::GetAssembly( const string& aName ) const
    {
        ACIt anACIt = fAMap.find( aName );
        if( anACIt != fAMap.end() )
        {
            return anACIt->second;
        }
        return NULL;
    }

    const vector< KSShape* >* KSGeometryToolbox::GetTag( const string& aTag ) const
    {
        TagGroupMapCIt aTagGroupMapCIt = fTagGroupMap.find( aTag );
        if( aTagGroupMapCIt != fTagGroupMap.end() )
        {
            return aTagGroupMapCIt->second;
        }
        return NULL;
    }

    void KSGeometryToolbox::SetWorldVolume( KSVolume* aWorldVolume )
    {
        fWorldVolume = aWorldVolume;
        AddVolume( aWorldVolume );
        return;
    }
    KSSurface* KSGeometryToolbox::GetSurface( const string& aFullName ) const
    {
        return FindSurface( fWorldVolume, aFullName );
    }
    KSVolume* KSGeometryToolbox::GetVolume( const string& aFullName ) const
    {
        return FindVolume( fWorldVolume, aFullName );
    }
    KSVolume* KSGeometryToolbox::GetWorldVolume() const
    {
        return fWorldVolume;
    }

    void KSGeometryToolbox::AddShape( KSShape* aShape )
    {
        const KSGeometry::TagSet* aTagSet = aShape->GetTagSet();
        KSGeometry::TagSetCIt aTagSetCIt;
        TagGroup* aTagGroup;
        TagGroupMapIt aTagGroupMapIt;
        for( aTagSetCIt = aTagSet->begin(); aTagSetCIt != aTagSet->end(); aTagSet++ )
        {
            aTagGroupMapIt = fTagGroupMap.find( *aTagSetCIt );
            if( aTagGroupMapIt != fTagGroupMap.end() )
            {
                aTagGroup = aTagGroupMapIt->second;
            }
            else
            {
                aTagGroup = new TagGroup();
                fTagGroupMap.insert( TagGroupMapEntry( *aTagSetCIt, aTagGroup ) );
            }
            aTagGroup->push_back( aShape );
        }
        aShape->ClearTags();
        return;
    }
    void KSGeometryToolbox::AddSurface( KSSurface* aSurface )
    {
        AddShape( aSurface );
        return;
    }
    void KSGeometryToolbox::AddVolume( KSVolume* aVolume )
    {
        AddShape( aVolume );

        KSSurface** SideSurfaces;
        UInt_t SideSurfaceCount;
        aVolume->GetSideSurfaces( &SideSurfaces, &SideSurfaceCount );
        for( UInt_t SideSurfaceIndex = 0; SideSurfaceIndex < SideSurfaceCount; SideSurfaceIndex++ )
        {
            AddSurface( SideSurfaces[SideSurfaceIndex] );
        }

        KSVolume** ChildVolumes;
        UInt_t ChildVolumeCount;
        aVolume->GetChildVolumes( &ChildVolumes, &ChildVolumeCount );
        for( UInt_t ChildVolumeIndex = 0; ChildVolumeIndex < ChildVolumeCount; ChildVolumeIndex++ )
        {
            AddVolume( ChildVolumes[ChildVolumeIndex] );
        }

        KSSurface** ChildSurfaces;
        UInt_t ChildSurfaceCount;
        aVolume->GetChildSurfaces( &ChildSurfaces, &ChildSurfaceCount );
        for( UInt_t ChildSurfaceIndex = 0; ChildSurfaceIndex < ChildSurfaceCount; ChildSurfaceIndex++ )
        {
            AddSurface( ChildSurfaces[ChildSurfaceIndex] );
        }

        return;
    }
    KSSurface* KSGeometryToolbox::FindSurface( KSVolume* aCurrentVolume, const string& aFullName ) const
    {
        //TODO: implement
        return NULL;
    }
    KSVolume* KSGeometryToolbox::FindVolume( KSVolume* aCurrentVolume, const string& aFullName ) const
    {
        //TODO: implement
        return NULL;
    }

}
