/*
 * KSStepContainer.h
 *
 * created on: Mar 6, 2011
 * author: dlfurse
 */

#ifndef KSSTEPCONTAINER_H_
#define KSSTEPCONTAINER_H_

#include "TMath.h"
#include "TVector3.h"

/*!
 * @class Kassiopeia::KSStepContainer
 * @author Dan
 *
 * @brief a container for a step used for boundary crossing checks
 * @details
 * this step container is a simple cylindrical pillbox that encloses the complete trajectory for a step.
 *
 */
namespace Kassiopeia
{

    class KSStepContainer
    {
        public:
            KSStepContainer();
            ~KSStepContainer();

            void SetCenter( const TVector3& center );
            const TVector3& GetCenter() const;

            void SetDirection( const TVector3& direction );
            const TVector3& GetDirection() const;

            void SetStart( const TVector3& start );
            const TVector3& GetStart() const;

            void SetEnd( const TVector3& end );
            const TVector3& GetEnd() const;

            void SetRadius( const Double_t& radius );
            const Double_t& GetRadius() const;

            void SetLength( const Double_t& length );
            const Double_t& GetLength() const;

            const Double_t& GetDiagonal() const;

            void RecalculateStartEnd();
            void RecalculateCenterDirection();

        private:
            TVector3 fCenter;
            TVector3 fDirection;
            Double_t fLength;

            TVector3 fStart;
            TVector3 fEnd;

            Double_t fRadius;

            Double_t fDiagonal;
    };

    inline void KSStepContainer::SetCenter( const TVector3& center )
    {
        fCenter = center;
        return;
    }
    inline const TVector3& KSStepContainer::GetCenter() const
    {
        return fCenter;
    }

    inline void KSStepContainer::SetDirection( const TVector3& direction )
    {
        fDirection = direction.Unit();
        return;
    }
    inline const TVector3& KSStepContainer::GetDirection() const
    {
        return fDirection;
    }

    inline void KSStepContainer::SetStart( const TVector3& start )
    {
        fStart = start;
        return;
    }
    inline const TVector3& KSStepContainer::GetStart() const
    {
        return fStart;
    }

    inline void KSStepContainer::SetEnd( const TVector3& end )
    {
        fEnd = end;
        return;
    }
    inline const TVector3& KSStepContainer::GetEnd() const
    {
        return fEnd;
    }

    inline void KSStepContainer::SetRadius( const Double_t& radius )
    {
        fRadius = radius;
        return;
    }
    inline const Double_t& KSStepContainer::GetRadius() const
    {
        return fRadius;
    }

    inline void KSStepContainer::SetLength( const Double_t& length )
    {
        fLength = length;
        return;
    }
    inline const Double_t& KSStepContainer::GetLength() const
    {
        return fLength;
    }

    inline const Double_t& KSStepContainer::GetDiagonal() const
    {
        return fDiagonal;
    }

    inline void KSStepContainer::RecalculateStartEnd()
    {
        //radius, center, direction, and length are primary in this function.
        //start, end, diagonal must be recalculated here.

        register Double_t X = fCenter.X();
        register Double_t Y = fCenter.Y();
        register Double_t Z = fCenter.Z();

        register Double_t DX = fLength * fDirection.X();
        register Double_t DY = fLength * fDirection.Y();
        register Double_t DZ = fLength * fDirection.Z();

        fStart.SetXYZ( X - DX, Y - DY, Z - DZ );

        fEnd.SetXYZ( X + DX, Y + DY, Z + DZ );

        fDiagonal = TMath::Sqrt( fLength * fLength + fRadius * fRadius );

        return;
    }
    inline void KSStepContainer::RecalculateCenterDirection()
    {
        //radius, start, and end are primary in this function.
        //center, direction, length, and ellipsezeta must be recalculated here.

        register Double_t X = fStart.X();
        register Double_t Y = fStart.Y();
        register Double_t Z = fStart.Z();

        register Double_t DX = fEnd.X() - fStart.X();
        register Double_t DY = fEnd.Y() - fStart.Y();
        register Double_t DZ = fEnd.Z() - fStart.Z();

        fLength = TMath::Sqrt( DX * DX + DY * DY + DZ * DZ );

        fDirection.SetXYZ( DX / fLength, DY / fLength, DZ / fLength );

        fCenter.SetXYZ( X + DX / 2., Y + DY / 2., Z + DZ / 2. );

        fDiagonal = TMath::Sqrt( fLength * fLength + fRadius * fRadius );

        return;
    }

}

#endif /* KSSTEPCONTAINER_H_ */
