/*
 * KSAssembly.cxx
 *
 * created on: Mar 29, 2011
 * author: dlfurse
 */

#include "KSAssembly.h"

#include "KSVolume.h"

#include "KSAssemblyPlacement.h"
#include "KSVolumePlacement.h"
#include "KSSurfacePlacement.h"

//#include "KSGeometryToolbox.h"
//#include "KSBuilderFactoryPrototype.h"
//#include "KSMessage.h"

namespace Kassiopeia
{

    KSAssembly::KSAssembly() :
        KSGeometry(),
        fAbstractVolume( NULL ),
        fAssemblyPlacements(),
        fVolumePlacements(),
        fSurfacePlacements()
    {
    }

    KSAssembly::~KSAssembly()
    {
        while( fAssemblyPlacements.size() != 0 )
        {
            delete fAssemblyPlacements.back();
            fAssemblyPlacements.pop_back();
        }
        while( fVolumePlacements.size() != 0 )
        {
            delete fVolumePlacements.back();
            fVolumePlacements.pop_back();
        }
        while( fSurfacePlacements.size() != 0 )
        {
            delete fSurfacePlacements.back();
            fSurfacePlacements.pop_back();
        }
    }

    //**********
    //production
    //**********

    void KSAssembly::MakeAssembly( KSVolume** volume ) const
    {
        fAbstractVolume->MakeVolume( volume );
        (*volume)->SetName( GetName() );
        (*volume)->AddTagSet( GetTagSet() );

        UInt_t tChildCount;

        tChildCount = fAssemblyPlacements.size();
        if( tChildCount != 0 )
        {
            KSVolume** tChildAssemblies = new KSVolume*[tChildCount];
            for( UInt_t tIndex = 0; tIndex < tChildCount; tIndex++ )
            {
                //actually make the child assembly
                fAssemblyPlacements[tIndex]->MakeAssembly( &tChildAssemblies[tIndex] );
            }
            (*volume)->AssignChildVolumes( tChildAssemblies, tChildCount );
        }

        tChildCount = fVolumePlacements.size();
        if( tChildCount != 0 )
        {
            KSVolume** tChildVolumes = new KSVolume*[tChildCount];
            for( UInt_t tIndex = 0; tIndex < tChildCount; tIndex++ )
            {
                //actually make the child volume
                fVolumePlacements[tIndex]->MakeVolume( &tChildVolumes[tIndex] );
            }
            (*volume)->AssignChildVolumes( tChildVolumes, tChildCount );
        }

        tChildCount = fSurfacePlacements.size();
        if( tChildCount != 0 )
        {
            KSSurface** tChildSurfaces = new KSSurface*[tChildCount];
            for( UInt_t tIndex = 0; tIndex < tChildCount; tIndex++ )
            {
                //actually make the child surface
                fSurfacePlacements[tIndex]->MakeSurface( &tChildSurfaces[tIndex] );
            }
            (*volume)->AssignChildSurfaces( tChildSurfaces, tChildCount );
        }
        return;
    }

    void KSAssembly::SetAbstractVolume( const KSAbstractVolume* volume )
    {
        fAbstractVolume = volume;
        return;
    }

    const KSAbstractVolume* KSAssembly::GetAbstractVolume() const
    {
        return fAbstractVolume;
    }

    //**********
    //placements
    //**********

    void KSAssembly::AddChildAssemblyPlacement( KSAssemblyPlacement* placement )
    {
        fAssemblyPlacements.push_back( placement );
        return;
    }

    void KSAssembly::AddChildVolumePlacement( KSVolumePlacement* placement )
    {
        fVolumePlacements.push_back( placement );
        return;
    }

    void KSAssembly::AddChildSurfacePlacement( KSSurfacePlacement* placement )
    {
        fSurfacePlacements.push_back( placement );
        return;
    }

}

//*****************
//KSAssemblyBuilder
//*****************

namespace Kassiopeia
{

/*
 template< > const string KSBuilderPrototype< KSGeometryToolbox, KSAssemblyBuilder >::fTypeName = string( "Assembly" );
 template< > const string KSBuilderPrototype< KSGeometryToolbox, KSAssemblyBuilder >::fSystemName = string( "Geometry" );
 static const KSBuilderFactoryPrototype< KSAssemblyBuilder > sKSAssemblyBuilderFactory = KSBuilderFactoryPrototype< KSAssemblyBuilder >();

 KSAssemblyBuilder::KSAssemblyBuilder() :
 KSGeometryContainerBuilder(),
 fAssembly( NULL )
 {
 }

 KSAssemblyBuilder::~KSAssemblyBuilder()
 {
 delete fAssembly;
 }

 KSGeometryContainer* KSAssemblyBuilder::PassDownGeometryContainer() const
 {
 return fAssembly;
 }

 Bool_t KSAssemblyBuilder::ProcessToken( const KSPseudoParameterToken* token )
 {
 KSXMLAttributeToken* tXMLToken = new KSXMLAttributeToken();
 tXMLToken->SetAttributeName( token->GetName() );
 tXMLToken->SetAttributeValue( token->GetValue() );
 Bool_t tResult = ProcessToken( tXMLToken );
 delete tXMLToken;
 return tResult;
 }

 Bool_t KSAssemblyBuilder::ProcessToken( const KSPseudoEndToken* token )
 {
 KSXMLEndElementToken* tXMLToken = new KSXMLEndElementToken();
 tXMLToken->SetElementName( token->GetValue() );
 Bool_t tResult = ProcessToken( tXMLToken );
 delete tXMLToken;
 return tResult;
 }

 Bool_t KSAssemblyBuilder::ProcessBuilder( const KSBuilder* token )
 {
 if( token->GetTypeName() == string( "SurfacePlacement" ) )
 {
 return kTRUE;
 }
 if( token->GetTypeName() == string( "VolumePlacement" ) )
 {
 return kTRUE;
 }
 if( token->GetTypeName() == string( "AssemblyPlacement" ) )
 {
 return kTRUE;
 }
 if( token->GetTypeName() == string( "Div" ) )
 {
 return kTRUE;
 }
 return kFALSE;
 }

 Bool_t KSAssemblyBuilder::ProcessToken( const KSXMLAttributeToken* token )
 {
 if( fAssembly == NULL)
 {
 fAssembly = new KSAssembly();
 fAssembly->SetName( GetInstanceName() );
 }

 if( token->GetAttributeName() == string( "volume" ) )
 {
 const KSAbstractVolume* tAbstractVolume = fManager->GetAbstractVolume( token->GetAttributeValue() );
 if( tAbstractVolume == NULL)
 {
 ksmsg < "KSVolumePlacementBuilder::ProcessToken( KSXMLAttributeToken* )";
 ksmsg( KSMessage::eError ) << "Volume <" << token->GetAttributeValue() << "> was not found in the GeometryToolbox!" << eom;
 return kFALSE;
 }

 fAssembly->SetAbstractVolume( tAbstractVolume );
 return kTRUE;
 }
 if( token->GetAttributeName() == string( "tag" ) )
 {
 fAssembly->AssignTag( token->GetAttributeValue() );
 return kTRUE;
 }
 return kFALSE;
 }

 Bool_t KSAssemblyBuilder::ProcessToken( const KSXMLEndElementToken* token )
 {
 if( token->GetElementName() != GetTypeName() ) return kFALSE;

 if( fAssembly == NULL)
 {
 fAssembly = new KSAssembly();
 fAssembly->SetName( GetInstanceName() );
 }
 AssignOpenTags();

 fManager->AddAssembly( fAssembly );
 fAssembly = NULL;
 return kTRUE;
 }

 void KSAssemblyBuilder::AssignOpenTags()
 {
 const vector< string >* tOpenTags = fManager->GetOpenTags();
 for( vector< string >::const_iterator tIter = tOpenTags->begin(); tIter != tOpenTags->end(); tIter++ )
 {
 fAssembly->AssignTag( *tIter );
 }
 return;
 }
 */

}

