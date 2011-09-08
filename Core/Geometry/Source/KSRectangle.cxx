/*
 * KSRectangle.cxx
 *
 * created on: Mar 31, 2011
 * author: Joan Smith
 */

#include "KSRectangle.h"

#include "KSConst.h"
#include "KSRandom.h"
#include "KSBuilderFactoryPrototype.h"

#include "TMath.h"

//******
//KSRectangle
//******

namespace Kassiopeia
{
    KSRectangle::KSRectangle() :
        KSSurface(),
        fLength( 0. ),
        fWidth( 0. ),
        fHalfLength( 0. ),
        fHalfWidth( 0. ),
        fHalfDiagonal( 0. )
    {
    }
    KSRectangle::~KSRectangle()
    {
    }

    const Double_t& KSRectangle::GetLength() const
    {
        return fLength;
    }
    const Double_t& KSRectangle::GetWidth() const
    {
        return fWidth;
    }
    const Double_t& KSRectangle::GetHalfLength() const
    {
        return fHalfLength;
    }
    const Double_t& KSRectangle::GetHalfWidth() const
    {
        return fHalfWidth;
    }
    const Double_t& KSRectangle::GetHalfDiagonal() const
    {
        return fHalfDiagonal;
    }
    const Double_t& KSRectangle::GetArea() const
    {
        return fArea;
    }

    //**************
    //visitor system
    //**************

    void KSRectangle::Accept( KSShapeVisitor* visitor )
    {
        KSRectangleVisitor* MyVisitor = dynamic_cast< KSRectangleVisitor* >( visitor );
        if( MyVisitor != NULL )
        {
            MyVisitor->VisitRectangle( this );
        }
        return;
    }

    //*********************
    //initialization system
    //*********************

    void KSRectangle::SetParameterGeometrySubclass( const Char_t* name, const Double_t& value )
    {
        if( string( name ) == string( "length" ) )
        {
            fLength = value;
        }
        if( string( name ) == string( "width" ) )
        {
            fWidth = value;
        }
        return;
    }
    void KSRectangle::SetParameterGeometrySubclass( const Char_t* /*name*/, const Int_t& /*value*/)
    {
        return;
    }

    void KSRectangle::InitializeSurfaceSubclass()
    {
        fHalfLength = fLength / 2.;
        fHalfWidth = fWidth / 2.;
        fHalfDiagonal = TMath::Sqrt( fLength * fLength + fWidth * fWidth ) / 2.0;
        return;
    }

    void KSRectangle::InitializeArea()
    {
        fArea = fLength * fWidth;
        return;
    }

    //*****************
    //navigation system
    //*****************

    void KSRectangle::IsNear( const KSStepContainer* container, Bool_t& result ) const
    {
        register Double_t AdjustedDistance = (container->GetCenter() - fOrigin).Mag() - (container->GetDiagonal() + fHalfDiagonal);
        if( AdjustedDistance < 0 )
        {
            result = kTRUE;
            return;
        }
        result = kFALSE;
        return;
    }

    //~Joan 4/1
    /*   Bool_t KSRectangle::IsNear(const KSStepContainer* container, Bool_t& result ) const
     {
     register Double_t value = 0.01;
     // try a larger version of the geometry
     register Double_t newHeight = 2 * value;
     register Double_t newWidth = fWidth + value;
     register Double_t newLength = fLength + value;
     register Double_t newLine = sqrt( (newWidth * newWidth) + (newLength * newLength) );
     TVector3 localPoint = TVector3( (fLocation - p).Dot(fLocalX),
     (fLocation - p).Dot(fLocalY),
     (fLocation - p).Dot(fLocalZ) );
     return TMath::Sqrt(localPoint.X()*localPoint.X() + localPoint.Y() *localPoint.Y()) <= newLine &&
     localPoint.Z() <= newHeight/2  &&
     localPoint.Z() >= -newHeight/2;
     }
     */

    void KSRectangle::MightCross( const KSStepContainer* /*container*/, Bool_t& /*result*/, Double_t& /*minimum*/) const
    {
        return;
    }

    void KSRectangle::DistanceTo( const TVector3& point, Double_t& distance ) const
    {
        register Double_t PointXCoordinate = (point.X() - fOrigin.X()) * fXAxis.X() + (point.Y() - fOrigin.Y()) * fXAxis.Y() + (point.Z() - fOrigin.Z()) * fXAxis.Z();
        register Double_t PointYCoordinate = (point.X() - fOrigin.X()) * fYAxis.X() + (point.Y() - fOrigin.Y()) * fYAxis.Y() + (point.Z() - fOrigin.Z()) * fYAxis.Z();
        register Double_t PointZCoordinate = (point.X() - fOrigin.X()) * fZAxis.X() + (point.Y() - fOrigin.Y()) * fZAxis.Y() + (point.Z() - fOrigin.Z()) * fZAxis.Z();
        register Double_t XDistance;
        register Double_t YDistance;

        if( PointXCoordinate > fHalfLength )
        {
            XDistance = PointXCoordinate - fHalfLength;
        }
        else if( PointXCoordinate < -fHalfLength )
        {
            XDistance = PointXCoordinate + fHalfLength;
        }
        else
        {
            XDistance = 0.;
        }

        if( PointYCoordinate > fHalfWidth )
        {
            YDistance = PointYCoordinate - fHalfWidth;
        }
        else if( PointYCoordinate < -fHalfWidth )
        {
            YDistance = PointYCoordinate + fHalfWidth;
        }
        else
        {
            YDistance = 0.;
        }

        distance = TMath::Sqrt( XDistance * XDistance + YDistance * YDistance + PointZCoordinate * PointZCoordinate );

        return;
    }

    //~Jan 2011/7/6 - taken from KSSquare
    void KSRectangle::NearestPoint( const TVector3& point, TVector3& closest ) const
    {
        register Double_t PointXCoordinate = (point.X() - fOrigin.X()) * fXAxis.X() + (point.Y() - fOrigin.Y()) * fXAxis.Y() + (point.Z() - fOrigin.Z()) * fXAxis.Z();
        register Double_t PointYCoordinate = (point.X() - fOrigin.X()) * fYAxis.X() + (point.Y() - fOrigin.Y()) * fYAxis.Y() + (point.Z() - fOrigin.Z()) * fYAxis.Z();
        register Double_t XCoordinate;
        register Double_t YCoordinate;

        if( PointXCoordinate > fHalfLength )
        {
            XCoordinate = fHalfLength;
        }
        else if( PointXCoordinate < -fHalfLength )
        {
            XCoordinate = -fHalfLength;
        }
        else
        {
            XCoordinate = PointXCoordinate;
        }

        if( PointYCoordinate > fHalfWidth )
        {
            YCoordinate = fHalfWidth;
        }
        else if( PointYCoordinate < -fHalfWidth )
        {
            YCoordinate = -fHalfWidth;
        }
        else
        {
            YCoordinate = PointYCoordinate;
        }

        closest = XCoordinate * fXAxis + YCoordinate * fYAxis + fOrigin;

        return;
    }

    void KSRectangle::IsAbove( const TVector3& point, Bool_t& result ) const
    {
        register Double_t ZCoordinate = (point.X() - fOrigin.X()) * fZAxis.X() + (point.Y() - fOrigin.Y()) * fZAxis.Y() + (point.Z() - fOrigin.Z()) * fZAxis.Z();
        if( ZCoordinate > 0. )
        {
            result = kTRUE;
            return;
        }
        result = kFALSE;
        return;
    }

    //******************
    //positioning system
    //******************

    void KSRectangle::TransformSurfaceSubclass( const KSTransformation* /*transform*/)
    {
        return;
    }

    //******************
    //surface properties
    //******************

    TVector3 KSRectangle::GetRandomSurfacePoint() const
    {
        register Double_t XOffset = KSRandom::GetInstance()->Uniform( (-1.0 * fLength / 2.0), (fLength / 2.0) );
        register Double_t YOffset = KSRandom::GetInstance()->Uniform( (-1.0 * fWidth / 2.0), (fWidth / 2.0) );
        return XOffset * fXAxis + YOffset * fYAxis + fOrigin;
    }

}

//******************
//abstract rectangle
//******************

namespace Kassiopeia
{

    KSAbstractRectangle::KSAbstractRectangle( const Double_t& length, const Double_t& width ) :
        fLength( length ),
        fWidth( width )
    {
    }
    KSAbstractRectangle::~KSAbstractRectangle()
    {
    }

    void KSAbstractRectangle::MakeSurfaceSubclass( KSSurface** surface ) const
    {
        KSRectangle* NewRectangle = new KSRectangle();
        NewRectangle->SetParameter( "length", fLength );
        NewRectangle->SetParameter( "width", fWidth );
        *surface = NewRectangle;
        return;
    }

}

//*****************
//rectangle visitor
//*****************

namespace Kassiopeia
{

    KSRectangleVisitor::KSRectangleVisitor()
    {
    }

    KSRectangleVisitor::~KSRectangleVisitor()
    {
    }

}

//*****************
//rectangle builder
//*****************

namespace Kassiopeia
{

    /* builder builder builder builder
    template<> const string KSBuilderPrototype< KSGeometryToolbox, KSRectangleBuilder >::fTypeName = string("Rectangle");
    template<> const string KSBuilderPrototype< KSGeometryToolbox, KSRectangleBuilder >::fSystemName = string("Geometry");
    static const KSBuilderFactoryPrototype< KSRectangleBuilder > sKSRectangleBuilderFactory = KSBuilderFactoryPrototype< KSRectangleBuilder >();

    KSRectangleBuilder::KSRectangleBuilder() :
        fAbstractRectangle( NULL ),
        fLength( 0. ),
        fWidth( 0. )
    {
    }
    KSRectangleBuilder::~KSRectangleBuilder()
    {
        if( fAbstractRectangle != NULL )
        {
            delete fAbstractRectangle;
            fAbstractRectangle = NULL;
        }
    }

    Bool_t KSRectangleBuilder::ProcessToken( const KSPseudoParameterToken* token )
    {
        if( token->GetName() == string( "length" ) )
        {
            fLength = token->GetValue< Double_t >();
            return kTRUE;
        }
        if( token->GetName() == string( "width" ) )
        {
            fWidth = token->GetValue< Double_t >();
            return kTRUE;
        }
        return kFALSE;
    }
    Bool_t KSRectangleBuilder::ProcessToken( const KSPseudoEndToken* token)
    {
        fAbstractRectangle = new KSAbstractRectangle( fLength, fWidth );;
        //fAbstractRectangle->SetName( GetInstanceName() );
        //fManager->AddAbstractSurface( fAbstractRectangle );
        fAbstractRectangle = NULL;
        return kTRUE;
    }

    Bool_t KSRectangleBuilder::ProcessToken( const KSXMLAttributeToken* token )
    {
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
        return kFALSE;
    }
    Bool_t KSRectangleBuilder::ProcessToken( const KSXMLEndElementToken* token)
    {
        fAbstractRectangle = new KSAbstractRectangle( fLength, fWidth );
        //fAbstractRectangle->SetName( GetInstanceName() );
        //fManager->AddAbstractSurface( fAbstractRectangle );
        fAbstractRectangle = NULL;
        return kTRUE;
    }
    */

//*****************

/* don't know what the fuck this is don't know what the fuck this is
 void KSRectangleBuilder::AssignOpenTags()
 {
 const vector< string >* tOpenTags = fManager->GetOpenTags();
 for( vector< string >::const_iterator tIter = tOpenTags->begin(); tIter != tOpenTags->end(); tIter++ )
 {
 fRectangle->AssignTag( *tIter );
 }
 return;
 }
 */

}

