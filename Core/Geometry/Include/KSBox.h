/*!
 * @file KSBox.h
 * @brief contains class declarations for KSBox, KSAbstractBox, KSBoxVisitor, and KSBoxBuilder
 *
 * @details
 * <b>Revision History:</b>
 * Date   Name   Brief description
 * Fri Mar  4 08:01:30 EST 2011  J. Barrett  First version
 *
 */

#ifndef KSBOX_H_
#define KSBOX_H_

#include "KSBoxLikeVolume.h"

namespace Kassiopeia
{

    class KSBox :
        public KSBoxLikeVolume
    {
        public:
            KSBox();
            virtual ~KSBox();

            const Double_t& GetLength() const;
            const Double_t& GetWidth() const;
            const Double_t& GetHeight() const;
            const Double_t& GetHalfDiagonal() const;

        private:
            Double_t fLength;
            Double_t fWidth;
            Double_t fHeight;
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
            virtual void InitializeCapacityAndArea();
            virtual void InitializeBoxLikeVolumeSubclass();
            virtual void InitializeTop();
            virtual void InitializeBottom();
            virtual void InitializeFront();
            virtual void InitializeBack();
            virtual void InitializeRight();
            virtual void InitializeLeft();

            //******************
            //positioning system
            //******************

        protected:
            virtual void TransformVolumeSubclass( const KSTransformation* transform );

            //****************
            //geometric system
            //****************

        public:
            virtual void IsNear( const KSStepContainer* container, Bool_t& result ) const;
            virtual void MightCross( const KSStepContainer* container, Bool_t& result, Double_t& minimum ) const;
            virtual void DistanceTo( const TVector3& point, Double_t& distance ) const;
            virtual void NearestPoint( const TVector3& point, TVector3& closest ) const;
            virtual void IsInside( const TVector3& point, Bool_t& result ) const;
            virtual TVector3 GetRandomVolumePoint() const;
            virtual TVector3 GetRandomSurfacePoint() const;

    };

    inline const Double_t& KSBox::GetLength() const
    {
        return fLength;
    }
    inline const Double_t& KSBox::GetWidth() const
    {
        return fWidth;
    }
    inline const Double_t& KSBox::GetHeight() const
    {
        return fHeight;
    }
    inline const Double_t& KSBox::GetHalfDiagonal() const
    {
        return fHalfDiagonal;
    }

}

/*!
 * @class Kassiopeia::KSAbstractBox
 * @author Dan Furse
 *
 * @brief this class builds boxes
 */
namespace Kassiopeia
{

    class KSAbstractBox :
        public KSAbstractVolume
    {
        public:
            KSAbstractBox();
            virtual ~KSAbstractBox();

            void SetParameters( const Double_t& length, const Double_t& width, const Double_t& height );

        protected:
            virtual void MakeVolumeSubclass( KSVolume** volume ) const;

        private:
            Double_t fLength;
            Double_t fWidth;
            Double_t fHeight;
    };

}

/*!
 * @class Kassiopeia::KSBoxVisitor
 * @author Dan Furse
 *
 * @brief this class visits boxes
 */
namespace Kassiopeia
{

    class KSBoxVisitor :
        public virtual KSShapeVisitor
    {
        public:
            KSBoxVisitor();
            virtual ~KSBoxVisitor();

            virtual void VisitBox( KSBox* box ) = 0;
    };
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

/*

#include "KSBuilderPrototype.h"
#include "KSGeometryToolbox.h"

*/

/*!
 * @class Kassiopeia::KSBoxBuilder
 * @author Dan Furse
 *
 * @brief this class builds boxes and puts them in the geometry toolbox
 */

/*
namespace Kassiopeia
{

    class KSBoxBuilder :
        public KSBuilderPrototype< KSGeometryToolbox, KSBoxBuilder >
    {
        public:
            KSBoxBuilder();
            virtual ~KSBoxBuilder();

        protected:
            virtual Bool_t ProcessToken( const KSPseudoParameterToken* token );
            virtual Bool_t ProcessToken( const KSPseudoEndToken* token );

            virtual Bool_t ProcessToken( const KSTokenAttribute* token );
            virtual Bool_t ProcessToken( const KSTokenEndElement* token );

        private:
            KSAbstractBox* fBox;
            Double_t fLength;
            Double_t fWidth;
            Double_t fHeight;
    };

}
*/

#endif /* KSBox_H_ */

