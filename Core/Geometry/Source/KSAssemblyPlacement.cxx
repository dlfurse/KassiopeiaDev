/*
 *  KSAssemblyPlacement.cxx
 *  Kassiopeia
 *
 *  Created by Noah Oblath on 6/22/11.
 *  Copyright 2011 MIT. All rights reserved.
 *
 */

#include "KSAssemblyPlacement.h"

#include "KSAssembly.h"
#include "KSVolume.h"
#include "KSTransformation.h"

//#include "KSGeometryToolbox.h"
//#include "KSBuilderFactoryPrototype.h"
//#include "KSMessage.h"

//*******************
//KSAssemblyPlacement
//*******************

namespace Kassiopeia
{

    KSAssemblyPlacement::KSAssemblyPlacement() :
        KSPlacement(),
        fAssembly( NULL )
    {
    }
    KSAssemblyPlacement::~KSAssemblyPlacement()
    {
    }

    void KSAssemblyPlacement::MakeAssembly( KSVolume** volume ) const
    {
        fAssembly->MakeAssembly( volume );
        (*volume)->SetName( GetName() );
        (*volume)->AddTagSet( GetTagSet() );
        (*volume)->Transform( GetTransformation() );
        return;
    }

    void KSAssemblyPlacement::SetAssembly( const KSAssembly* assembly )
    {
        fAssembly = assembly;
        return;
    }
    const KSAssembly* KSAssemblyPlacement::GetAssembly() const
    {
        return fAssembly;
    }

}

//**************************
//KSAssemblyPlacementBuilder
//**************************

namespace Kassiopeia
{

/*
 template< > const string KSBuilderPrototype< KSGeometryToolbox, KSAssemblyPlacementBuilder >::fTypeName = string( "AssemblyPlacement" );
 template< > const string KSBuilderPrototype< KSGeometryToolbox, KSAssemblyPlacementBuilder >::fSystemName = string( "Geometry" );
 static const KSBuilderFactoryPrototype< KSAssemblyPlacementBuilder > sKSAssemblyPlacementBuilderFactory = KSBuilderFactoryPrototype< KSAssemblyPlacementBuilder >();

 KSAssemblyPlacementBuilder::KSAssemblyPlacementBuilder() :
 KSGeometryContainerBuilder(),
 fPlacement( NULL ),
 fParentContainer( NULL )
 {
 }

 KSAssemblyPlacementBuilder::~KSAssemblyPlacementBuilder()
 {
 delete fPlacement;
 }

 KSGeometryContainer* KSAssemblyPlacementBuilder::PassDownGeometryContainer() const
 {
 return fPlacement;
 }

 Bool_t KSAssemblyPlacementBuilder::ProcessToken( const KSPseudoParameterToken* token )
 {
 KSXMLAttributeToken* tXMLToken = new KSXMLAttributeToken();
 tXMLToken->SetAttributeName( token->GetName() );
 tXMLToken->SetAttributeValue( token->GetValue() );
 Bool_t tResult = ProcessToken( tXMLToken );
 delete tXMLToken;
 return tResult;
 }

 Bool_t KSAssemblyPlacementBuilder::ProcessToken( const KSPseudoEndToken* token )
 {
 KSXMLEndElementToken* tXMLToken = new KSXMLEndElementToken();
 tXMLToken->SetElementName( token->GetValue() );
 Bool_t tResult = ProcessToken( tXMLToken );
 delete tXMLToken;
 return tResult;
 }

 Bool_t KSAssemblyPlacementBuilder::ProcessBuilder( const KSBuilder* token )
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

 Bool_t KSAssemblyPlacementBuilder::ProcessToken( const KSXMLAttributeToken* token )
 {
 if( fPlacement == NULL ) fPlacement = new KSAssemblyPlacement();

 if( token->GetAttributeName() == string( "assembly" ) )
 {
 const KSGeometryContainerBuilder* tParentGCB = GetParentGeometryContainerBuilder();
 if( tParentGCB != NULL)
 {
 fParentContainer = tParentGCB->PassDownGeometryContainer();
 fPlacement->SetParent( fParentContainer );
 }
 else
 {
 ksmsg < "KSAssemblyPlacementBuilder::ProcessToken( KSXMLAttributeToken* )";
 ksmsg( KSMessage::eError ) << "The parent container has not been set. You may be trying to build this placement without using a geometry container." << newline;
 ksmsg << "All placement must be built inside of some geometry container (e.g. World or Assembly)." << eom;
 return kFALSE;
 }

 const KSAssembly* tAssembly = fManager->GetAssembly( token->GetAttributeValue() );
 if( tAssembly == NULL)
 {
 ksmsg < "KSAssemblyPlacementBuilder::ProcessToken( KSXMLAttributeToken* )";
 ksmsg( KSMessage::eError ) << "Assembly <" << token->GetAttributeValue() << "> was not found in the GeometryToolbox!" << eom;
 return kFALSE;
 }

 fPlacement->SetAssembly( tAssembly );
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

 Bool_t KSAssemblyPlacementBuilder::ProcessToken( const KSXMLEndElementToken* token )
 {
 if( token->GetElementName() != GetTypeName() ) return kFALSE;

 if( fPlacement == NULL ) fPlacement = new KSAssemblyPlacement();

 fPlacement->SetName( GetInstanceName() );
 AssignOpenTags();

 fParentContainer->AddChildAssemblyPlacement( fPlacement );
 fPlacement = NULL;
 return kTRUE;
 }

 const KSGeometryContainerBuilder* KSAssemblyPlacementBuilder::GetParentGeometryContainerBuilder() const
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

 void KSAssemblyPlacementBuilder::AssignOpenTags()
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
