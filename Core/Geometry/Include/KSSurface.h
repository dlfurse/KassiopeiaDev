/*!
 * @file KSSurface.h
 * @author Dan Furse
 *
 * @brief created on: Feb 17, 2011.  contains definitions for KSSurface, LogicalSurface and KSAbstractSurface
 *
 */

#ifndef KSSURFACE_H_
#define KSSURFACE_H_

#include "KSShape.h"

/*!
 * @class Kassiopeia::KSSurface
 * @author Dan Furse
 *
 * @brief this class represents an abstract surface augmented with properties and placed in a coordinate system.
 *
 * @sa KSGeometry
 */
namespace Kassiopeia
{

    class VisualizationProperties;
    class SurfaceCommandProperties;
    class SurfaceElectricalProperties;

    class KSVolume;

    class KSSurface :
        public KSShape
    {
        public:
            KSSurface();
            virtual ~KSSurface();

            //*********************
            //initialization system
            //*********************

        protected:
            virtual void InitializeGeometrySubclass();
            virtual void InitializeSurfaceSubclass() = 0;
            virtual void InitializeArea() = 0;

            //*****************
            //properties system
            //*****************

        public:
            void SetVisualizationProperties( const VisualizationProperties* properties );
            const VisualizationProperties* GetVisualizationProperties() const;

            void SetCommandProperties( const SurfaceCommandProperties* properties );
            const SurfaceCommandProperties* GetCommandProperties() const;

            void SetElectricalProperties( const SurfaceElectricalProperties* properties );
            const SurfaceElectricalProperties* GetElectricalProperties() const;

        private:
            const VisualizationProperties* fVisualizationProperties;
            const SurfaceCommandProperties* fSurfaceCommandProperties;
            const SurfaceElectricalProperties* fSurfaceElectricalProperties;

            //****************
            //structure system
            //****************

        public:
            //! set the parent volume of this surface.
            /*!
             * @param parent pointer to parent volume
             */
            void AssignParent( const KSVolume* parent );
            //! get the parent volume of this surface.
            /*!
             * @param parent the address of the parent is written at the address given here
             */
            void GetParent( const KSVolume** parent ) const;

        private:
            const KSVolume* fParent;

            //******************
            //positioning system
            //******************

        protected:
            //! transform this surface.  since surfaces can contain no objects, TransformVolumeSubclass() is simply called.
            /*!
             * @param transform transformation to be applied to the surface
             * @sa TransformSurfaceSubclass()
             */
            virtual void TransformGeometrySubclass( const KSTransformation* transform );

            //! hook for subclasses to transform themselves.
            /*!
             * @param transform transformation to be applied to the surface
             * @sa TransformGeometrySubclass()
             */
            virtual void TransformSurfaceSubclass( const KSTransformation* transform ) = 0;

            //****************
            //geometric system
            //****************

        public:
            //! see whether or not a given point in the global coordinate system is above the surface or not
            /*!
             * @param point object of query
             * @param result whether or not the point is above the surface is returned into this reference
             */
            virtual void IsAbove( const TVector3& point, Bool_t& result ) const = 0;

            //! generate an evenly distributed random point on this surface
            virtual TVector3 GetRandomSurfacePoint() const = 0;

            //! get the area of the surface in square meters
            const Double_t& GetArea() const;

        protected:
            Double_t fArea;
    };

}

/*!
 * @class Kassiopeia::KSAbstractSurface
 * @author Dan Furse
 *
 * @brief this class represents the idea of a surface with only its shape parameters set.
 *
 */
namespace Kassiopeia
{

    class KSAbstractSurface :
        public KSAbstractShape
    {
        public:
            KSAbstractSurface();
            virtual ~KSAbstractSurface();

            //**********
            //production
            //**********

        public:
            //! make a new surface of the appropriate type as implemented in subclasses.
            /*!
             * @param surface pointer to new surface is written at the address given here
             */
            void MakeSurface( KSSurface** surface ) const;

        protected:
            virtual void MakeSurfaceSubclass( KSSurface** aNewSurface ) const = 0;

    };

}

#endif /* KSSURFACE_H_ */
