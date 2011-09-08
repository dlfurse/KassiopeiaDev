#ifndef KSSHAPE_H_
#define KSSHAPE_H_

#include "KSGeometry.h"

#include "KSStepContainer.h"
#include "KSTransformation.h"

#include "Rtypes.h"
#include "TVector3.h"

/*!
 * @class Kassiopeia::KSShape
 * @author Dan Furse
 *
 * @brief base class for all geometry classes that represent forms
 */
namespace Kassiopeia
{
    class KSShapeVisitor;

    class KSShape :
        public KSGeometry
    {
        public:
            KSShape();
            virtual ~KSShape();

            virtual void SetName( const string& name );
            virtual const string& GetName() const;

        protected:
            string fName;

            //**************
            //visitor system
            //**************

        public:
            //! accept a visitor to this object (uses the acyclic visitor pattern).
            /*!
             * @param visitor visiting object
             */
            virtual void Accept( KSShapeVisitor* visitor ) = 0;

            //*********************
            //initialization system
            //*********************

        public:
            void SetParameter( const Char_t* name, const Double_t& value );
            void SetParameter( const Char_t* name, const Int_t& value );

        protected:
            virtual void SetParameterGeometrySubclass( const Char_t* name, const Double_t& value ) = 0;
            virtual void SetParameterGeometrySubclass( const Char_t* name, const Int_t& value ) = 0;
            virtual void InitializeGeometrySubclass() = 0;

            //******************
            //positioning system
            //******************

        public:
            //! transform this object.  first the coordinate system is transformed and then TransformGeometrySubclass() is called.
            /*!
             * @param transform transformation to be applied to the object
             * @sa TransformGeometrySubclass()
             */
            void Transform( const KSTransformation* transform );
            //! origin of local coordinate system expressed in global coordinates
            const TVector3& GetOrigin() const;
            //! x axis unit vector of local coordinate system expressed in global coordinates
            const TVector3& GetXAxis() const;
            //! y axis unit vector of local coordinate system expressed in global coordinates
            const TVector3& GetYAxis() const;
            //! z axis unit vector of local coordinate system expressed in global coordinates
            const TVector3& GetZAxis() const;

        protected:
            //! hook for subclasses to transform themselves.
            /*!
             * @param transform transformation to be applied to the object
             * @sa Transform()
             */
            virtual void TransformGeometrySubclass( const KSTransformation* transform ) = 0;
            TVector3 fOrigin;
            TVector3 fXAxis;
            TVector3 fYAxis;
            TVector3 fZAxis;
            ;

            //****************
            //geometric system
            //****************

            //! see whether or not a step container is in some sense 'near' to the object.  this is a very fast calculation and reliably returns 'kFALSE', but may unreliably return 'kTRUE'.
            /*!
             * @param container object of query
             * @param result whether or not the container is near the object is returned into this reference
             */
            virtual void IsNear( const KSStepContainer* container, Bool_t& result ) const = 0;

            //! see whether or not a step container contains points that the object also contains, and return the minimum point along the z axis of the step container where this occurs. a more expensive calculation than IsNear.
            /*!
             * @param container object of query
             * @param result whether or not the container might cross is returned into this reference
             * @param minimum the minimum point along the z axis of the container where the crossing might occur, if it might, is returned into this reference
             */
            virtual void MightCross( const KSStepContainer* container, Bool_t& result, Double_t& minimum ) const = 0;

            //! find the shortest distance to the object from a given point given in global coordinates.
            /*!
             * @param point object of query
             * @param distance shortest distance returned into this reference
             */
            virtual void DistanceTo( const TVector3& point, Double_t& distance ) const = 0;

            //! find the nearest point that is an element of the object from a given point in global coordinates.
            /*!
             * @param point object of query
             * @param closest nearest point returned into this reference
             */
            virtual void NearestPoint( const TVector3& point, TVector3& closest ) const = 0;
    };

}

/*!
 * @class Kassiopeia::KSAbstractShape
 * @author N Oblath
 *
 * @brief this class is represents a deferred instantiation of a shape object
 *
 */

namespace Kassiopeia
{
    class KSAbstractShape :
        public KSGeometry
    {
        public:
            KSAbstractShape();
            virtual ~KSAbstractShape();
    };
}

/*!
 * @class Kassiopeia::KSGeometryVisitor
 * @author Dan Furse
 *
 * @brief base class for all geometry visitors
 *
 * @details The geometry hierarchy follows the acyclic visitor pattern for drawing.
 */
namespace Kassiopeia
{

    class KSShapeVisitor
    {
        public:
            KSShapeVisitor();
            virtual ~KSShapeVisitor();
    };

}

#endif /* KSGEOMETRY_H_ */
