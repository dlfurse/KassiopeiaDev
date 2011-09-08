/*
 *  KSSurfacePlacement.cxx
 *  Kassiopeia
 *
 *  Created by Noah Oblath on 6/22/11.
 *  Copyright 2011 MIT. All rights reserved.
 *
 */

#include "KSSurfacePlacement.h"

#include "KSSurface.h"
#include "KSTransformation.h"

//#include "KSGeometryToolbox.h"
//#include "KSBuilderFactoryPrototype.h"
//#include "KSMessage.h"

//******************
//KSSurfacePlacement
//******************

namespace Kassiopeia
{

    KSSurfacePlacement::KSSurfacePlacement() :
        KSPlacement(),
        fAbstractSurface( NULL )
    {
    }
    KSSurfacePlacement::~KSSurfacePlacement()
    {
    }

    void KSSurfacePlacement::MakeSurface( KSSurface** surface ) const
    {
        fAbstractSurface->MakeSurface( surface );
        (*surface)->SetName( GetName() );
        (*surface)->AddTagSet( GetTagSet() );
        (*surface)->Transform( GetTransformation() );
        return;
    }

    void KSSurfacePlacement::SetAbstractSurface( const KSAbstractSurface* surface )
    {
        fAbstractSurface = surface;
        return;
    }
    const KSAbstractSurface* KSSurfacePlacement::GetAbstractSurface() const
    {
        return fAbstractSurface;
    }

}

//*************************
//KSSurfacePlacementBuilder
//*************************

namespace Kassiopeia
{
/*
 template<> const string KSBuilderPrototype< KSGeometryToolbox, KSSurfacePlacementBuilder>::fTypeName = string("SurfacePlacement");
 template<> const string KSBuilderPrototype< KSGeometryToolbox, KSSurfacePlacementBuilder>::fSystemName = string("Geometry");
 static const KSBuilderFactoryPrototype< KSSurfacePlacementBuilder > sKSSurfacePlacementBuilderFactory = KSBuilderFactoryPrototype< KSSurfacePlacementBuilder >();

 KSSurfacePlacementBuilder::KSSurfacePlacementBuilder() :
 fPlacement(NULL),
 fParentContainer(NULL)
 {
 }

 KSSurfacePlacementBuilder::~KSSurfacePlacementBuilder()
 {
 delete fPlacement;
 }

 void KSSurfacePlacementBuilder::SetGeometryContainer( KSGeometryContainer* container )
 {
 fGeometryContainer = container;
 std::cout << "surface placement has set the geometry container to: " << fGeometryContainer << std::endl;
 return;
 }

 Bool_t KSSurfacePlacementBuilder::ProcessToken( const KSPseudoParameterToken* token )
 {
 KSXMLAttributeToken* tXMLToken = new KSXMLAttributeToken();
 tXMLToken->SetAttributeName(token->GetName());
 tXMLToken->SetAttributeValue(token->GetValue());
 Bool_t tResult = ProcessToken(tXMLToken);
 delete tXMLToken;
 return tResult;
 }

 Bool_t KSSurfacePlacementBuilder::ProcessToken( const KSPseudoEndToken* token )
 {
 KSXMLEndElementToken* tXMLToken = new KSXMLEndElementToken();
 tXMLToken->SetElementName(token->GetValue());
 Bool_t tResult = ProcessToken(tXMLToken);
 delete tXMLToken;
 return tResult;
 }

 Bool_t KSSurfacePlacementBuilder::ProcessToken( const KSXMLAttributeToken* token )
 {
 if (fPlacement == NULL) fPlacement = new KSSurfacePlacement();

 if (token->GetAttributeName() == string("surface"))
 {
 const KSGeometryContainerBuilder* tParentGCB = GetParentGeometryContainerBuilder();
 if (tParentGCB != NULL)
 {
 fParentContainer = tParentGCB->PassDownGeometryContainer();
 fPlacement->SetParent( fParentContainer );
 }
 else
 {
 ksmsg < "KSSurfacePlacementBuilder::ProcessToken( KSXMLAttributeToken* )";
 ksmsg(KSMessage::eError) << "The parent container has not been set. You may be trying to build this placement without using a geometry container." << newline;
 ksmsg << "All placement must be built inside of some geometry container (e.g. World or Assembly)." << eom;
 return kFALSE;
 }


 const KSAbstractSurface* tAbstractSurface = fManager->GetAbstractSurface( token->GetAttributeValue() );
 if (tAbstractSurface == NULL)
 {
 ksmsg < "KSSurfacePlacementBuilder::ProcessToken( KSXMLAttributeToken* )";
 ksmsg(KSMessage::eError) << "Abstract surface <" << token->GetAttributeValue() << "> was not found in the GeometryToolbox!" << eom;
 return kFALSE;
 }
 fPlacement->SetAbstractSurface( tAbstractSurface );
 return kTRUE;
 }
 if (token->GetAttributeName() == string("rotation_angle"))
 {
 fPlacement->SetRotationAngle( token->GetAttributeValue< Double_t >() );
 return kTRUE;
 }
 if (token->GetAttributeName() == string("rotation_axis_latitude"))
 {
 fPlacement->SetRotationAxisLatitude( token->GetAttributeValue< Double_t >() );
 return kTRUE;
 }
 if (token->GetAttributeName() == string("rotation_axis_longitude"))
 {
 fPlacement->SetRotationAxisLongitude( token->GetAttributeValue< Double_t >() );
 return kTRUE;
 }
 if (token->GetAttributeName() == string("displacement_x"))
 {
 fPlacement->SetDisplacementX( token->GetAttributeValue< Double_t >() );
 return kTRUE;
 }
 if (token->GetAttributeName() == string("displacement_y"))
 {
 fPlacement->SetDisplacementY( token->GetAttributeValue< Double_t >() );
 return kTRUE;
 }
 if (token->GetAttributeName() == string("displacement_z"))
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

 Bool_t KSSurfacePlacementBuilder::ProcessToken( const KSXMLEndElementToken* token )
 {
 if (token->GetElementName() != GetTypeName()) return kFALSE;

 if (fPlacement == NULL) fPlacement = new KSSurfacePlacement();

 fPlacement->SetName( GetInstanceName() );
 AssignOpenTags();

 fParentContainer->AddChildSurfacePlacement( fPlacement );
 fPlacement = NULL;
 return kTRUE;
 }

 const KSGeometryContainerBuilder* KSSurfacePlacementBuilder::GetParentGeometryContainerBuilder() const
 {
 const KSGeometryContainerBuilder* tGCB = NULL;
 const KSBuilderChainLink* tBuilderCL = fParent;
 while (tGCB == NULL && tBuilderCL != NULL)
 {
 tGCB = dynamic_cast< const KSGeometryContainerBuilder* > (tBuilderCL);
 tBuilderCL = tBuilderCL->GetParent();
 }
 return tGCB;
 }

 void KSSurfacePlacementBuilder::AssignOpenTags()
 {
 const vector< string >* tOpenTags = fManager->GetOpenTags();
 for (vector< string >::const_iterator tIter = tOpenTags->begin();
 tIter != tOpenTags->end();
 tIter++)
 {
 fPlacement->AssignTag( *tIter );
 }
 return;
 }
 */

}
