/*
 * KSBox.cxx
 *
 * created on: Apr 12, 2011
 * author: Dan Furse
 */

#include "KSBox.h"
#include "KSRectangle.h"

#include "KSRandom.h"

//***
//Box
//***

/*
 *        Z
 *        |                     Top
 *        |                     |
 *        +------Y              |      (Back)
 *       /              +-------|----------+
 *      /              /.       |         /|
 *     X              / .       v        / |
 *                   /  .               /  |
 *                  +------------------+   |
 *                  |   .              |   |
 *        Left----->|   .              |  <----Right
 *                  |   .              |   |
 *                  |   . . . . . . . .|. .+
 *                  |  .               |  /
 *                  | .                | /
 *                  |.  Front          |/
 *                  +------------------+
 *                              ^
 *                              |
 *                              Bottom
 */

namespace Kassiopeia
{

    KSBox::KSBox() :
        KSBoxLikeVolume(),
        fLength( 0. ),
        fWidth( 0. ),
        fHeight( 0. ),
        fHalfDiagonal( 0. )
    {
        KSTransformation T;
        T.SetOrigin( fOrigin );
        T.SetXAxis( fXAxis );
        T.SetYAxis( fYAxis );
        T.SetZAxis( fZAxis );

        T.SetRotationEuler( 0., 0., 0. );
        fSideSurfaces[eSideNumberTop] = new KSRectangle();
        fSideSurfaces[eSideNumberTop]->Transform( &T );

        T.SetRotationEuler( 0., 180., 0. );
        fSideSurfaces[eSideNumberBottom] = new KSRectangle();
        fSideSurfaces[eSideNumberBottom]->Transform( &T );

        T.SetRotationEuler( 180., 90., 0. );
        fSideSurfaces[eSideNumberRight] = new KSRectangle();
        fSideSurfaces[eSideNumberRight]->Transform( &T );

        T.SetRotationEuler( 0., 90., 0. );
        fSideSurfaces[eSideNumberLeft] = new KSRectangle();
        fSideSurfaces[eSideNumberLeft]->Transform( &T );

        T.SetRotationEuler( 90., 90., 0. );
        fSideSurfaces[eSideNumberFront] = new KSRectangle();
        fSideSurfaces[eSideNumberFront]->Transform( &T );

        T.SetRotationEuler( 270., 90., 0. );
        fSideSurfaces[eSideNumberBack] = new KSRectangle();
        fSideSurfaces[eSideNumberBack]->Transform( &T );
    }
    KSBox::~KSBox()
    {
    }

    //**************
    //visitor system
    //**************

    void KSBox::Accept( KSShapeVisitor* visitor )
    {
        KSBoxVisitor* MyVisitor = dynamic_cast< KSBoxVisitor* >( visitor );
        if( MyVisitor != NULL )
        {
            MyVisitor->VisitBox( this );
        }
        return;
    }

    //*********************
    //initialization system
    //*********************

    void KSBox::SetParameterGeometrySubclass( const Char_t* name, const Double_t& value )
    {
        if( strcmp( name, "length" ) == 0 )
        {
            fLength = value;
            return;
        }
        else if( strcmp( name, "width" ) == 0 )
        {
            fWidth = value;
            return;
        }
        else if( strcmp( name, "height" ) == 0 )
        {
            fHeight = value;
            return;
        }
        return;
    }

    void KSBox::SetParameterGeometrySubclass( const Char_t* /*name*/, const Int_t& /*value*/)
    {
        return;
    }

    void KSBox::InitializeCapacityAndArea()
    {
        fArea = fSideSurfaces[eSideNumberTop]->GetArea() + fSideSurfaces[eSideNumberBottom]->GetArea() + fSideSurfaces[eSideNumberRight]->GetArea() + fSideSurfaces[eSideNumberLeft]->GetArea() + fSideSurfaces[eSideNumberFront]->GetArea() + fSideSurfaces[eSideNumberBack]->GetArea();
        fCapacity = fWidth * fHeight * fLength;
    }

    void KSBox::InitializeBoxLikeVolumeSubclass()
    {
        fHalfDiagonal = TMath::Sqrt( fLength * fLength + fWidth * fWidth + fHeight * fHeight ) / 2.0;
        return;
    }

    void KSBox::InitializeTop()
    {
        KSTransformation T;
        T.SetOrigin( fOrigin );
        T.SetXAxis( fXAxis );
        T.SetYAxis( fYAxis );
        T.SetZAxis( fZAxis );

        T.SetDisplacement( fOrigin - fSideSurfaces[eSideNumberTop]->GetOrigin() );
        fSideSurfaces[eSideNumberTop]->Transform( &T );

        fSideSurfaces[eSideNumberTop]->SetParameter( "length", fLength );
        fSideSurfaces[eSideNumberTop]->SetParameter( "width", fWidth );

        T.SetDisplacement( (1. / 2.) * fHeight * fZAxis );
        fSideSurfaces[eSideNumberTop]->Transform( &T );

        return;
    }

    void KSBox::InitializeBottom()
    {
        KSTransformation T;
        T.SetOrigin( fOrigin );
        T.SetXAxis( fXAxis );
        T.SetYAxis( fYAxis );
        T.SetZAxis( fZAxis );

        T.SetDisplacement( fOrigin - fSideSurfaces[eSideNumberBottom]->GetOrigin() );
        fSideSurfaces[eSideNumberBottom]->Transform( &T );

        fSideSurfaces[eSideNumberBottom]->SetParameter( "length", fLength );
        fSideSurfaces[eSideNumberBottom]->SetParameter( "width", fWidth );

        T.SetDisplacement( (-1. / 2.) * fHeight * fZAxis );
        fSideSurfaces[eSideNumberBottom]->Transform( &T );

        return;
    }

    void KSBox::InitializeFront()
    {
        KSTransformation T;
        T.SetOrigin( fOrigin );
        T.SetXAxis( fXAxis );
        T.SetYAxis( fYAxis );
        T.SetZAxis( fZAxis );

        T.SetDisplacement( fOrigin - fSideSurfaces[eSideNumberFront]->GetOrigin() );
        fSideSurfaces[eSideNumberFront]->Transform( &T );

        fSideSurfaces[eSideNumberFront]->SetParameter( "length", fWidth );
        fSideSurfaces[eSideNumberFront]->SetParameter( "width", fHeight );

        T.SetDisplacement( (1. / 2.) * fLength * fXAxis );
        fSideSurfaces[eSideNumberFront]->Transform( &T );

        return;
    }

    void KSBox::InitializeBack()
    {
        KSTransformation T;
        T.SetOrigin( fOrigin );
        T.SetXAxis( fXAxis );
        T.SetYAxis( fYAxis );
        T.SetZAxis( fZAxis );

        T.SetDisplacement( fOrigin - fSideSurfaces[eSideNumberBack]->GetOrigin() );
        fSideSurfaces[eSideNumberBack]->Transform( &T );

        fSideSurfaces[eSideNumberBack]->SetParameter( "length", fWidth );
        fSideSurfaces[eSideNumberBack]->SetParameter( "width", fHeight );

        T.SetDisplacement( (-1. / 2.) * fLength * fXAxis );
        fSideSurfaces[eSideNumberBack]->Transform( &T );

        return;
    }

    void KSBox::InitializeRight()
    {
        KSTransformation T;
        T.SetOrigin( fOrigin );
        T.SetXAxis( fXAxis );
        T.SetYAxis( fYAxis );
        T.SetZAxis( fZAxis );

        T.SetDisplacement( fOrigin - fSideSurfaces[eSideNumberBack]->GetOrigin() );
        fSideSurfaces[eSideNumberBack]->Transform( &T );

        fSideSurfaces[eSideNumberBack]->SetParameter( "length", fLength );
        fSideSurfaces[eSideNumberBack]->SetParameter( "width", fHeight );

        T.SetDisplacement( (1. / 2.) * fWidth * fYAxis );
        fSideSurfaces[eSideNumberBack]->Transform( &T );

        return;
    }

    void KSBox::InitializeLeft()
    {
        KSTransformation T;
        T.SetOrigin( fOrigin );
        T.SetXAxis( fXAxis );
        T.SetYAxis( fYAxis );
        T.SetZAxis( fZAxis );

        T.SetDisplacement( fOrigin - fSideSurfaces[eSideNumberBack]->GetOrigin() );
        fSideSurfaces[eSideNumberBack]->Transform( &T );

        fSideSurfaces[eSideNumberBack]->SetParameter( "length", fLength );
        fSideSurfaces[eSideNumberBack]->SetParameter( "width", fHeight );

        T.SetDisplacement( (-1. / 2.) * fWidth * fYAxis );
        fSideSurfaces[eSideNumberBack]->Transform( &T );

        return;
    }

    //******************
    //positioning system
    //******************

    void KSBox::TransformVolumeSubclass( const KSTransformation* /*transform*/)
    {
    }

    //****************
    //geometric system
    //****************

    void KSBox::IsNear( const KSStepContainer* /*container*/, Bool_t& /*result*/) const
    {
    }

    void KSBox::MightCross( const KSStepContainer* /*container*/, Bool_t& /*result*/, Double_t& /*minimum*/) const
    {
    }

    void KSBox::DistanceTo( const TVector3& point, Double_t& distance ) const
    {
        ///Adapted from "Geometric Tools for Computer Graphics" p.396
        ///by P. Schneider and D. Eberly
        ///Morgan Kaufmann Publishers 2003

        Double_t LocalPoint[3] =
            { (point - fOrigin).Dot( fXAxis ), (point - fOrigin).Dot( fYAxis ), (point - fOrigin).Dot( fZAxis ) };

        Double_t BoxDimensions[3] =
            { fLength, fWidth, fHeight };

        Double_t SquaredDistance = 0;
        Double_t temp = 0;

        for( UInt_t i = 0; i < 3; i++ )
        {
            if( LocalPoint[i] < (-1.0 * BoxDimensions[i]) / 2.0 )
            {
                temp = LocalPoint[i] + BoxDimensions[i] / 2.0;
                SquaredDistance += temp * temp;
            }
            else if( LocalPoint[i] > (BoxDimensions[i]) / 2.0 )
            {
                temp = LocalPoint[i] - BoxDimensions[i] / 2.0;
                SquaredDistance += temp * temp;
            }
        }

        distance = TMath::Sqrt( SquaredDistance );
    }

    void KSBox::NearestPoint( const TVector3& point, TVector3& closest ) const
    {
        ///Adapted from "Geometric Tools for Computer Graphics" p.396
        ///by P. Schneider and D. Eberly
        ///Morgan Kaufmann Publishers 2003

        Double_t LocalPoint[3] =
            { (point - fOrigin).Dot( fXAxis ), (point - fOrigin).Dot( fYAxis ), (point - fOrigin).Dot( fZAxis ) };

        Double_t ClosestPoint[3] =
            { 0, 0, 0 };

        Double_t BoxDimensions[3] =
            { fLength, fWidth, fHeight };

        for( UInt_t i = 0; i < 3; i++ )
        {
            if( LocalPoint[i] < (-1.0 * BoxDimensions[i]) / 2.0 )
            {
                ClosestPoint[i] = -1.0 * BoxDimensions[i] / 2.0;

            }
            else if( LocalPoint[i] > (BoxDimensions[i]) / 2.0 )
            {
                ClosestPoint[i] = BoxDimensions[i] / 2.0;
            }
            else
            {
                ClosestPoint[i] = LocalPoint[i];
            }

        }

        closest = ClosestPoint[0] * fXAxis + ClosestPoint[1] * fYAxis + ClosestPoint[2] * fZAxis + fOrigin;

    }

    void KSBox::IsInside( const TVector3& /*point*/, Bool_t& /*result*/) const
    {
    }

    TVector3 KSBox::GetRandomVolumePoint() const
    {
        Double_t xpos = KSRandom::GetInstance()->Uniform( (-1.0 * fWidth / 2.0), (fWidth / 2.0) );
        Double_t ypos = KSRandom::GetInstance()->Uniform( (-1.0 * fHeight / 2.0), (fHeight / 2.0) );
        Double_t zpos = KSRandom::GetInstance()->Uniform( (-1.0 * fLength / 2.0), (fLength / 2.0) );
        return xpos * fXAxis + ypos * fYAxis + zpos * fZAxis + fOrigin;
    }

    TVector3 KSBox::GetRandomSurfacePoint() const
    {
        Double_t aRandomPartition = KSRandom::GetInstance()->Uniform( 0.0, fArea );
        Double_t aPartition = fArea;

        aPartition -= fSideSurfaces[eSideNumberTop]->GetArea();
        if( aRandomPartition >= aPartition )
        {
            return fSideSurfaces[eSideNumberTop]->GetRandomSurfacePoint();
        }

        aPartition -= fSideSurfaces[eSideNumberBottom]->GetArea();
        if( aRandomPartition >= aPartition )
        {
            return fSideSurfaces[eSideNumberBottom]->GetRandomSurfacePoint();
        }

        aPartition -= fSideSurfaces[eSideNumberFront]->GetArea();
        if( aRandomPartition >= aPartition )
        {
            return fSideSurfaces[eSideNumberFront]->GetRandomSurfacePoint();
        }

        aPartition -= fSideSurfaces[eSideNumberBack]->GetArea();
        if( aRandomPartition >= aPartition )
        {
            return fSideSurfaces[eSideNumberBack]->GetRandomSurfacePoint();
        }

        aPartition -= fSideSurfaces[eSideNumberRight]->GetArea();
        if( aRandomPartition >= aPartition )
        {
            return fSideSurfaces[eSideNumberRight]->GetRandomSurfacePoint();
        }

        aPartition -= fSideSurfaces[eSideNumberLeft]->GetArea();
        if( aRandomPartition >= aPartition )
        {
            return fSideSurfaces[eSideNumberLeft]->GetRandomSurfacePoint();
        }

        //this should never happen, and if it's coded right it will never happen, but without it the compiler complains
        return fSideSurfaces[eSideNumberTop]->GetOrigin();
    }

}

//*****************
//abstract box
//*****************

namespace Kassiopeia
{

    KSAbstractBox::KSAbstractBox() :
        fLength( 0. ),
        fWidth( 0. ),
        fHeight( 0. )
    {
    }
    KSAbstractBox::~KSAbstractBox()
    {
    }

    void KSAbstractBox::SetParameters( const Double_t& length, const Double_t& width, const Double_t& height )
    {
        fLength = length;
        fWidth = width;
        fHeight = height;
        return;
    }

    void KSAbstractBox::MakeVolumeSubclass( KSVolume** volume ) const
    {
        KSBox* NewBox = new KSBox();
        NewBox->SetParameter( "length", fLength );
        NewBox->SetParameter( "width", fWidth );
        NewBox->SetParameter( "height", fHeight );
        *volume = NewBox;
        return;
    }

}

//****************
//box visitor
//****************

namespace Kassiopeia
{

    KSBoxVisitor::KSBoxVisitor()
    {
    }

    KSBoxVisitor::~KSBoxVisitor()
    {
    }

}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////                                                   /////
/////  BBBB   U   U  IIIII  L      DDDD   EEEEE  RRRR   /////
/////  B   B  U   U    I    L      D   D  E      R   R  /////
/////  BBBB   U   U    I    L      D   D  EE     RRRR   /////
/////  B   B  U   U    I    L      D   D  E      R   R  /////
/////  BBBB    UUU   IIIII  LLLLL  DDDD   EEEEE  R   R  /////
/////                                                   /////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

#include "KSBuilderFactoryPrototype.h"

namespace Kassiopeia
{

    template< > const string KSBuilderPrototype< KSGeometryToolbox, KSBoxBuilder >::fTypeName = string( "Box" );
    template< > const string KSBuilderPrototype< KSGeometryToolbox, KSBoxBuilder >::fSystemName = string( "Geometry" );
    static const KSBuilderFactoryPrototype< KSBoxBuilder > sKSBoxBuilderFactory = KSBuilderFactoryPrototype< KSBoxBuilder >();

    KSBoxBuilder::KSBoxBuilder() :
        fBox( NULL ),
        fLength( 0. ),
        fWidth( 0. ),
        fHeight( 0. )
    {
    }

    KSBoxBuilder::~KSBoxBuilder()
    {
        if( fBox != NULL )
        {
            delete fBox;
            fBox = NULL;
        }
    }

    Bool_t KSBoxBuilder::ProcessToken( const KSPseudoParameterToken* token )
    {
        KSTokenAttribute* tXMLToken = new KSTokenAttribute();
        tXMLToken->SetAttributeName( token->GetName() );
        tXMLToken->SetAttributeValue( token->GetValue() );
        Bool_t tResult = ProcessToken( tXMLToken );
        delete tXMLToken;
        return tResult;
    }

    Bool_t KSBoxBuilder::ProcessToken( const KSPseudoEndToken* token )
    {
        KSTokenEndElement* tXMLToken = new KSTokenEndElement();
        tXMLToken->SetElementName( token->GetValue() );
        Bool_t tResult = ProcessToken( tXMLToken );
        delete tXMLToken;
        return tResult;
    }

    Bool_t KSBoxBuilder::ProcessToken( const KSTokenAttribute* token )
    {
        if( fBox == NULL ) fBox = new KSAbstractBox();

        if( token->GetAttributeName() == string( "length" ) )
        {
            fLength = token->GetAttributeValue< Double_t >();
            return kTRUE;
        }
        if( token->GetAttributeName() == string( "width" ) )
        {
            fWidth = token->GetAttributeValue< Double_t >();
            return kTRUE;
        }
        if( token->GetAttributeName() == string( "height" ) )
        {
            fHeight = token->GetAttributeValue< Double_t >();
            return kTRUE;
        }
        if( token->GetAttributeName() == string( "tag" ) )
        {
            fBox->AddTag( token->GetAttributeValue() );
            return kTRUE;
        }
        return kFALSE;
    }
    Bool_t KSBoxBuilder::ProcessToken( const KSTokenEndElement* token )
    {
        fBox->SetName( GetInstanceName() );
        fBox->SetParameters( fLength, fWidth, fHeight );

        fManager->AddAbstractVolume( fBox );
        fBox = NULL;
        return kTRUE;
    }

//*****************

/*
 void KSBoxBuilder::AssignOpenTags()
 {
 const vector< string >* tOpenTags = fManager->GetOpenTags();
 for( vector< string >::const_iterator tIter = tOpenTags->begin(); tIter != tOpenTags->end(); tIter++ )
 {
 fBox->AssignTag( *tIter );
 }
 return;
 }
 */

}
