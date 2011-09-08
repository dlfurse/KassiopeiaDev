/*!
 * @file KSVolume.h
 * @author Dan Furse
 *
 * @brief created on: Feb 17, 2011. contains definitions of KSVolume and KSAbstractVolume
 *
 */

#ifndef KSVOLUME_H_
#define KSVOLUME_H_

#include "KSShape.h"

#include <vector>
using std::vector;

/*!
 * @class Kassiopeia::KSVolume
 * @author Dan Furse
 *
 * @brief base class for all volume classes
 */
namespace Kassiopeia
{

    class VisualizationProperties;
    class VolumeCommandProperties;
    class VolumeElectricalProperties;

    class KSSurface;

    class KSVolume :
        public KSShape
    {
        public:
            KSVolume( const UInt_t& sidecount );
            virtual ~KSVolume();

        private:
            KSVolume();

            //*********************
            //initialization system
            //*********************

        protected:
            virtual void InitializeGeometrySubclass();
            virtual void InitializeVolumeSubclass() = 0;
            virtual void InitializeCapacityAndArea() = 0;

            //*****************
            //properties system
            //*****************

        public:
            void AssignVisualizationProperties( const VisualizationProperties* properties );
            const VisualizationProperties* GetVisualizationProperties() const;

            void AssignVolumeCommandProperties( const VolumeCommandProperties* properties );
            const VolumeCommandProperties* GetVolumeCommandProperties() const;

            void AssignVolumeElectricalProperties( const VolumeElectricalProperties* properties );
            const VolumeElectricalProperties* GetVolumeElectricalProperties() const;

        private:
            const VisualizationProperties* fVisualizationProperties;
            const VolumeCommandProperties* fVolumeCommandProperties;
            const VolumeElectricalProperties* fVolumeElectricalProperties;

            /* old functions
             public:
             void AssignTag(const string& tag);
             void AssignTags(const TagSet* tags);

             public:
             void SetVisualizationProperties( const VisualizationProperties* properties );
             void SetVisualizationProperties( const VisualizationProperties* properties, const Char_t* sidename );
             const VisualizationProperties* GetVisualizationProperties() const;
             const VisualizationProperties* GetVisualizationProperties( const Char_t* sidename ) const;

             void AssignEntryActions(const vector< KSCommand* >* entry);
             const vector< KSCommand* >* GetEntryActions() const;

             void AssignExitActions(const vector< KSCommand* >* entry);
             const vector< KSCommand* >* GetExitActions() const;

             private:
             const vector< KSCommand* >* fEntryActions;
             const vector< KSCommand* >* fExitActions;
             */

            //****************
            //structure system
            //****************
        public:
            //! get a pointer to a side surface by name.
            /*!
             * @param side the address of the corresponding side is written at the address given here
             * @param name a name of a side
             */
            virtual void GetSideSurface( const Char_t* name, KSSurface** side ) const = 0;
            //! get the array of pointers to side surfaces.
            /*!
             * @param sides the address of the array of pointers to side surfaces is written at the address given here.
             * @param count the number of sides.
             */
            void GetSideSurfaces( KSSurface*** sides, UInt_t* count ) const;

            //! set the parent volume of this volume.
            /*!
             * @param parent pointer to parent volume
             */
            void AssignParent( KSVolume* parent );
            //! get the parent volume of this volume.
            /*!
             * @param parent the address of the parent is written at the address given here
             */
            void GetParent( KSVolume** parent ) const;

            //! set the array of pointers to child volumes.  this array is subsequently owned by this object and it and its contents will be deleted in destruction.
            /*!
             * @param children an array of pointers to child volumes
             * @param count the number of child volumes
             */
            void AssignChildVolumes( KSVolume** children, UInt_t& count );
            //! get the array of pointers to child volumes.
            /*!
             * @param children the address of the array of pointers to child volumes is written at the address given here.
             * @param count the number of child volumes is written at the address given here.
             */
            void GetChildVolumes( KSVolume*** children, UInt_t* count ) const;

            //! set the array of pointers to child surfaces.  this array is subsequently owned by this object and it and its contents will be deleted in destruction.
            /*!
             * @param children an array of pointers to child surfaces
             * @param count the number of child surfaces
             */
            void AssignChildSurfaces( KSSurface** children, UInt_t& count );
            //! get the array of pointers to child surfaces.
            /*!
             * @param children the address of the array of pointers to child surfaces is written at the address given here.
             * @param count the number of child surfaces is written at the address given here.
             */
            void GetChildSurfaces( KSSurface*** children, UInt_t* count ) const;

            //! get the array of pointers to side surfaces.
            /*!
             * @param sides the address of the array of pointers to side surfaces is written at the address given here.
             * @param count the number of side surfaces is written at the address given here.
             */

        protected:
            KSSurface** fSideSurfaces;
            UInt_t fSideSurfaceCount;

            KSVolume* fParent;

            KSSurface** fChildSurfaces;
            UInt_t fChildSurfaceCount;

            KSVolume** fChildVolumes;
            UInt_t fChildVolumeCount;

            //******************
            //positioning system
            //******************

        protected:
            //! transform this volume.  the volumes and surfaces are contained by this volumes are transformed first, then the sides are transformed, then TransformVolumeSubclass() is called.
            /*!
             * @param transform transformation to be applied to the volume
             * @sa TransformVolumeSubclass()
             */
            virtual void TransformGeometrySubclass( const KSTransformation* transform );

            //! hook for subclasses to transform themselves.
            /*!
             * @param transform transformation to be applied to the volume
             * @sa TransformGeometrySubclass()
             */
            virtual void TransformVolumeSubclass( const KSTransformation* transform ) = 0;

            //****************
            //geometric system
            //****************

        public:
            //! see whether or not a given point in the global coordinate system is inside the volume or not.
            /*!
             * @param point object of query
             * @param result whether or not the point is in the volume is returned into this reference
             */
            virtual void IsInside( const TVector3& point, Bool_t& result ) const = 0;

            //! generate an evenly distributed random point in this volume
            virtual TVector3 GetRandomVolumePoint() const = 0;

            //! generate an evenly distributed random point on the surface of this volume
            virtual TVector3 GetRandomSurfacePoint() const = 0;

            //! get the capacity of this volume in liters.
            const Double_t& GetCapacity() const;

            //! get the surface area of this volume in square meters.
            const Double_t& GetArea() const;

        protected:
            Double_t fCapacity;
            Double_t fArea;

    };

}

/*!
 * @class Kassiopeia::KSAbstractVolume
 * @author Dan Furse
 *
 * @brief this class represents the idea of a volume with only its shape parameters set.
 *
 */
namespace Kassiopeia
{
    class KSVolume;

    class KSAbstractVolume :
        public KSAbstractShape
    {
        public:
            KSAbstractVolume();
            virtual ~KSAbstractVolume();

            //**********
            //production
            //**********

        public:
            //! make a new volume of the appropriate type as implemented in subclasses.
            /*!
             * @param volume pointer to new volume is written at the address given here
             */
            void MakeVolume( KSVolume** aNewVolume ) const;

        protected:
            virtual void MakeVolumeSubclass( KSVolume** aNewVolume ) const = 0;

    };

}

#endif /* KSVOLUME_H_ */
