/*
 * KSGeometry.cxx
 *
 * created on: Feb 17, 2011
 * author: dlfurse
 */

#include "KSShape.h"

#include <iostream>

namespace Kassiopeia
{

    KSShape::KSShape() :
    fName("(anonymous)"),
    fOrigin( 0., 0., 0. ),
    fXAxis( 1., 0., 0. ),
    fYAxis( 0., 1., 0. ),
    fZAxis( 0., 0., 1. )
    {
    }
    KSShape::~KSShape()
    {
    }

    void KSShape::SetName(const string& name)
    {
        fName = name;
        return;
    }
    const string& KSShape::GetName() const
    {
        return fName;
    }


    //*********************
    //initialization system
    //*********************

    void KSShape::SetParameter( const Char_t* name, const Double_t& value )
    {
        SetParameterGeometrySubclass( name, value );
        InitializeGeometrySubclass();
        return;
    }
    void KSShape::SetParameter( const Char_t* name, const Int_t& value )
    {
        SetParameterGeometrySubclass( name, value );
        InitializeGeometrySubclass();
        return;
    }

    //******************
    //positioning system
    //******************

    void KSShape::Transform( const KSTransformation* transform )
    {
        transform->ApplyRotation( fOrigin );
        transform->ApplyDisplacement( fOrigin );
        transform->ApplyRotation( fXAxis );
        transform->ApplyRotation( fYAxis );
        transform->ApplyRotation( fZAxis );

        TransformGeometrySubclass( transform );

        return;
    }

    const TVector3& KSShape::GetOrigin() const
    {
        return fOrigin;
    }
    const TVector3& KSShape::GetXAxis() const
    {
        return fXAxis;
    }
    const TVector3& KSShape::GetYAxis() const
    {
        return fYAxis;
    }
    const TVector3& KSShape::GetZAxis() const
    {
        return fZAxis;
    }

}

//**************
//abstract shape
//**************

namespace Kassiopeia
{

    KSAbstractShape::KSAbstractShape()
    {
    }

    KSAbstractShape::~KSAbstractShape()
    {
    }

}


//*************
//shape visitor
//*************

namespace Kassiopeia
{

    KSShapeVisitor::KSShapeVisitor()
    {
    }

    KSShapeVisitor::~KSShapeVisitor()
    {
    }

}
