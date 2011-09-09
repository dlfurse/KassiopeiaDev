/*!
 * @file KSRectangle.h
 *
 * @author Joan Smith
 *
 * @brief file containing declarations for the KSRectangle, KSAbstractRectangle, and KSRectangleVisitor classes
 */

#ifndef KSRECTANGLE_H_
#define KSRECTANGLE_H_

#include "KSSurface.h"

//#include "KSBuilderPrototype.h"
//#include "KSGeometryToolbox.h"

/*!
 * @class Kassiopeia::KSRectangle
 * @author Joan Smith
 *
 * @brief a class which represents a rectangular surface.
 *
 * @details
 * local origin: at the center of the rectangle.
 * local coordinate system: z axis points normal to the rectangle, and the x and y axes lie in the plane of the rectangle.
 * free parameters: length is in the x axis, width in the y axis
 *
 */
namespace Kassiopeia
{

    class KSRectangle :
        public KSSurface
    {
        public:
            KSRectangle();
            virtual ~KSRectangle();

            //! get the length of the rectangle.
            const Double_t& GetLength() const;
            //! get the width of the rectangle.
            const Double_t& GetWidth() const;
            //! get the half length of the rectangle.
            const Double_t& GetHalfLength() const;
            //! get the half width of the rectangle.
            const Double_t& GetHalfWidth() const;
            //! get the diagonal half length of the rectangle.
            const Double_t& GetHalfDiagonal() const;
            //! get the area of the rectangle.
            const Double_t& GetArea() const;

        private:
            Double_t fLength;
            Double_t fWidth;
            Double_t fHalfLength;
            Double_t fHalfWidth;
            Double_t fHalfDiagonal;

            //**************
            //visitor system
            //**************

        public:
            virtual void Accept( KSShapeVisitor* visitor );

            //*********************
            //initialization system
            //*********************

        protected:
            virtual void SetParameterGeometrySubclass( const Char_t* name, const Double_t& value );
            virtual void SetParameterGeometrySubclass( const Char_t* name, const Int_t& value );
            virtual void InitializeSurfaceSubclass();
            virtual void InitializeArea();

            //******************
            //positioning system
            //******************

        protected:
            virtual void TransformSurfaceSubclass( const KSTransformation* transform );

            //****************
            //geometric system
            //****************

        public:
            /*!
             * @brief implementation of IsNear() declared in the KSSurface class.
             * @details
             * this function operates by first calculating the distance between the center of the rectangle and the center of the trajectory container.
             * from this distance, the radius of the rectangle and the diagonal length of the trajectory container are subtracted.
             * if the result is negative, kFALSE is returned, otherwise kTRUE is returned.
             */
            virtual void IsNear( const KSStepContainer* container, Bool_t& result ) const;
            /*!
             * @brief implementation of MightCross() declared in the KSSurface class.
             * @details
             * NOT DONE!
             */
            virtual void MightCross( const KSStepContainer* container, Bool_t& result, Double_t& minimum ) const;
            /*!
             * @brief implementation of DistanceTo() declared in the KSSurface class.
             * @details
             * NOT DONE!
             */
            virtual void DistanceTo( const TVector3& point, Double_t& distance ) const;
            /*!
             * @brief implementation of NearestPoint() declared in the KSSurface class.
             * @details
             * this function operates by first setting the return vector reference to the radial component of vector connecting the center of the rectangle to the given point.
             * if the magnitude squared of this vector is smaller than the radius squared, then this vector is already the closest one in the rectangle to the given point, and the function simply returns at this stage.
             * otherwise, the calculated radial component is too large to still be in the rectangle, so its length is set to be that of the radius of the rectangle, putting the return vector reference on the edge of the rectangle.
             * now the return vector reference is correct, and the function returns.
             */
            virtual void NearestPoint( const TVector3& point, TVector3& closest ) const;
            /*!
             * @brief implementation of IsAbove() declared in the KSSurface class.
             * @details
             * this function operates by taking the dot product of the vector connecting the point to the center of the rectangle and the local z axis.
             * if the result is positive, the point is above, if not it is not above.
             */
            virtual void IsAbove( const TVector3& point, Bool_t& result ) const;

            virtual TVector3 GetRandomSurfacePoint() const;
    };

}

/*!
 * @class Kassiopeia::KSAbstractRectangle
 * @author Dan Furse
 *
 * @brief this class builds a rectangle
 */
namespace Kassiopeia
{

    class KSAbstractRectangle :
        public KSAbstractSurface
    {
        public:
            KSAbstractRectangle( const Double_t& length, const Double_t& width );
            virtual ~KSAbstractRectangle();

        protected:
            virtual void MakeSurfaceSubclass( KSSurface** surface ) const;

        private:
            Double_t fLength;
            Double_t fWidth;
    };

}

/*!
 * @class Kassiopeia::KSRectangleVisitor
 * @author Dan Furse
 *
 * @brief interface for a class which can visit a rectangle
 */
namespace Kassiopeia
{

    class KSRectangleVisitor :
        public virtual KSShapeVisitor
    {
        public:
            KSRectangleVisitor();
            virtual ~KSRectangleVisitor();

            virtual void VisitRectangle( KSRectangle* rectangle ) = 0;
    };

}

/*!
 * @class Kassopeia::KSRectangleBuilder
 * @author Dan Furse
 * @author Jan Behrens
 *
 * @brief this class builds rectangles and puts them in the geometry toolbox
 */
namespace Kassiopeia
{

/* builder builder builder builder builder
 class KSRectangleBuilder :
 public KSBuilderPrototype< KSGeometryToolbox, KSRectangleBuilder >
 {
 public:
 KSRectangleBuilder();
 virtual ~KSRectangleBuilder();

 protected:
 virtual Bool_t ProcessToken( const KSPseudoParameterToken* token );
 virtual Bool_t ProcessToken( const KSPseudoEndToken* token );

 virtual Bool_t ProcessToken( const KSXMLAttributeToken* token );
 virtual Bool_t ProcessToken( const KSXMLEndElementToken* token );

 //virtual void AssignOpenTags();

 private:
 KSAbstractRectangle* fAbstractRectangle;
 Double_t fLength; //x dimension
 Double_t fWidth;  //y dimension
 };
 */
}

#endif /* KSRECTANGLE_H_ */
