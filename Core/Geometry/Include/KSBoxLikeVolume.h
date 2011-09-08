/*!
 * @file KSBoxLikeVolume.h
 * @author Dan Furse
 * @author Jan Behrens
 *
 * @brief contains class definitions for KSBoxLikeVolume and LogicalBoxLikeVolume
 */

#ifndef KSBOXLIKEVOLUME_H_
#define KSBOXLIKEVOLUME_H_

#include "KSVolume.h"

/*!
 * @class Kassiopeia::KSBoxLikeVolume
 * @author Dan Furse
 * @author Jan Behrens
 *
 * @brief this class represents a volume with six sides, labeled top, bottom, front, back, left, and right.
 */
namespace Kassiopeia
{

    class KSBoxLikeVolume :
        public KSVolume
    {
        public:
            KSBoxLikeVolume();
            virtual ~KSBoxLikeVolume();

        public:
            enum
            {
                eSideNumberTop = 0,
                eSideNumberBottom = 1,
                eSideNumberFront = 2,
                eSideNumberBack = 3,
                eSideNumberRight = 4,
                eSideNumberLeft= 5
            };

            //*********************
            //initialization system
            //*********************

        protected:
            virtual void InitializeVolumeSubclass();
            virtual void InitializeBoxLikeVolumeSubclass() = 0;
            virtual void InitializeTop() = 0;
            virtual void InitializeBottom() = 0;
            virtual void InitializeFront() = 0;
            virtual void InitializeBack() = 0;
            virtual void InitializeRight() = 0;
            virtual void InitializeLeft() = 0;

            //*****************
            //structural system
            //*****************

        public:
            virtual void GetSideSurface( const Char_t* name, KSSurface** side ) const;
            virtual void GetTop( KSSurface** side ) const;
            virtual void GetBottom( KSSurface** side ) const;
            virtual void GetFront( KSSurface** side ) const;
            virtual void GetBack( KSSurface** side ) const;
            virtual void GetRight( KSSurface** side ) const;
            virtual void GetLeft( KSSurface** side ) const;
    };

}

#endif /* KSBOXLIKEVOLUME_H_ */
