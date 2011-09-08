/*
 *  KSVolumePlacement.cxx
 *  Kassiopeia
 *
 *  Created by Noah Oblath on 6/22/11.
 *  Copyright 2011 MIT. All rights reserved.
 *
 */

#include "KSVolumePlacement.h"

#include "KSVolume.h"
#include "KSTransformation.h"

//#include "KSGeometryToolbox.h"
//#include "KSBuilderFactoryPrototype.h"
//#include "KSMessage.h"

//*****************
//KSVolumePlacement
//*****************

namespace Kassiopeia
{

    KSVolumePlacement::KSVolumePlacement() :
        KSPlacement(),
        fAbstractVolume( NULL )
    {
    }

    KSVolumePlacement::~KSVolumePlacement()
    {
    }

    void KSVolumePlacement::MakeVolume( KSVolume** volume ) const
    {
        fAbstractVolume->MakeVolume( volume );
        (*volume)->SetName( GetName() );
        (*volume)->AddTagSet( GetTagSet() );
        (*volume)->Transform( GetTransformation() );
        return;
    }

    void KSVolumePlacement::SetAbstractVolume( const KSAbstractVolume* volume )
    {
        fAbstractVolume = volume;
        return;
    }
    const KSAbstractVolume* KSVolumePlacement::GetAbstractVolume() const
    {
        return fAbstractVolume;
    }

}

//************************
//KSVolumePlacementBuilder
//************************

namespace Kassiopeia
{

/*
 template< > const string KSBuilderPrototype< KSGeometryToolbox, KSVolumePlacementBuilder >::fTypeName = string( "VolumePlacement" );
 template< > const string KSBuilderPrototype< KSGeometryToolbox, KSVolumePlacementBuilder >::fSystemName = string( "Geometry" );
 static const KSBuilderFactoryPrototype< KSVolumePlacementBuilder > sKSVolumePlacementBuilderFactory = KSBuilderFactoryPrototype< KSVolumePlacementBuilder >();

 KSVolumePlacementBuilder::KSVolumePlacementBuilder() :
 KSGeometryContainerBuilder(),
 fPlacement( NULL ),
 fParentContainer( NULL )
 {
 }

 KSVolumePlacementBuilder::~KSVolumePlacementBuilder()
 {
 delete fPlacement;
 }

 KSGeometryContainer* KSVolumePlacementBuilder::PassDownGeometryContainer() const
 {
 return fPlacement;
 }

 Bool_t KSVolumePlacementBuilder::ProcessToken( const KSPseudoParameterToken* token )
 {
 KSXMLAttributeToken* tXMLToken = new KSXMLAttributeToken();
 tXMLToken->SetAttributeName( token->GetName() );
 tXMLToken->SetAttributeValue( token->GetValue() );
 Bool_t tResult = ProcessToken( tXMLToken );
 delete tXMLToken;
 return tResult;
 }

 Bool_t KSVolumePlacementBuilder::ProcessToken( const KSPseudoEndToken* token )
 {
 KSXMLEndElementToken* tXMLToken = new KSXMLEndElementToken();
 tXMLToken->SetElementName( token->GetValue() );
 Bool_t tResult = ProcessToken( tXMLToken );
 delete tXMLToken;
 return tResult;
 }

 Bool_t KSVolumePlacementBuilder::ProcessBuilder( const KSBuilder* token )
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

 Bool_t KSVolumePlacementBuilder::ProcessToken( const KSXMLAttributeToken* token )
 {
 if( fPlacement == NULL ) fPlacement = new KSVolumePlacement();

 if( token->GetAttributeName() == string( "volume" ) )
 {
 const KSGeometryContainerBuilder* tParentGCB = GetParentGeometryContainerBuilder();
 if( tParentGCB != NULL)
 {
 fParentContainer = tParentGCB->PassDownGeometryContainer();
 fPlacement->SetParent( fParentContainer );
 }
 else
 {
 ksmsg < "KSVolumePlacementBuilder::ProcessToken( KSXMLAttributeToken* )";
 ksmsg( KSMessage::eError ) << "The parent container has not been set. You may be trying to build this placement without using a geometry container." << newline;
 ksmsg << "All placement must be built inside of some geometry container (e.g. World or Assembly)." << eom;
 return kFALSE;
 }

 const KSAbstractVolume* tAbstractVolume = fManager->GetAbstractVolume( token->GetAttributeValue() );
 if( tAbstractVolume == NULL)
 {
 ksmsg < "KSVolumePlacementBuilder::ProcessToken( KSXMLAttributeToken* )";
 ksmsg( KSMessage::eError ) << "Abstract volume <" << token->GetAttributeValue() << "> was not found in the GeometryToolbox!" << eom;
 return kFALSE;
 }

 fPlacement->SetAbstractVolume( tAbstractVolume );
 return kTRUE;
 }
 if( token->GetAttributeName() == string( "rotation_angle" ) )
 {
 fPlacement->SetRotationAngle( token->GetAttributeValue< Double_t >() );
 return kTRUE;
 }
 if( token->GetAttributeName() == string( "rotation_axis_latitude" ) )
 {
 fPlacement->SetRotationAxisLatitude( token->GetAttributeValue< Double_t >() );
 return kTRUE;
 }
 if( token->GetAttributeName() == string( "rotation_axis_longitude" ) )
 {
 fPlacement->SetRotationAxisLongitude( token->GetAttributeValue< Double_t >() );
 return kTRUE;
 }
 if( token->GetAttributeName() == string( "displacement_x" ) )
 {
 fPlacement->SetDisplacementX( token->GetAttributeValue< Double_t >() );
 return kTRUE;
 }
 if( token->GetAttributeName() == string( "displacement_y" ) )
 {
 fPlacement->SetDisplacementY( token->GetAttributeValue< Double_t >() );
 return kTRUE;
 }
 if( token->GetAttributeName() == string( "displacement_z" ) )
 {
 fPlacement->SetDisplacementZ( token->GetAttributeValue< Double_t >() );
 return kTRUE;
 }
 if( token->GetAttributeName() == string( "tag" ) )
 {
 fPlacement->AssignTag( token->GetAttributeValue() );
 return kTRUE;
 }
 return kFALSE;
 }

 Bool_t KSVolumePlacementBuilder::ProcessToken( const KSXMLEndElementToken* token )
 {
 if( token->GetElementName() != GetTypeName() ) return kFALSE;

 if( fPlacement == NULL ) fPlacement = new KSVolumePlacement();

 fPlacement->SetName( GetInstanceName() );
 AssignOpenTags();

 fParentContainer->AddChildVolumePlacement( fPlacement );
 fPlacement = NULL;
 return kTRUE;
 }

 const KSGeometryContainerBuilder* KSVolumePlacementBuilder::GetParentGeometryContainerBuilder() const
 {
 const KSGeometryContainerBuilder* tGCB = NULL;
 const KSBuilderChainLink* tBuilderCL = fParent;
 while( tGCB == NULL && tBuilderCL != NULL )
 {
 tGCB = dynamic_cast< const KSGeometryContainerBuilder* >( tBuilderCL );
 tBuilderCL = tBuilderCL->GetParent();
 }
 return tGCB;
 }

 void KSVolumePlacementBuilder::AssignOpenTags()
 {
 const vector< string >* tOpenTags = fManager->GetOpenTags();
 for( vector< string >::const_iterator tIter = tOpenTags->begin(); tIter != tOpenTags->end(); tIter++ )
 {
 fPlacement->AssignTag( *tIter );
 }
 return;
 }
 */

}
