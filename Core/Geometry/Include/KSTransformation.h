/*
 * KSTransformation.h
 *
 * created on: Feb 17, 2011
 * author: dlfurse
 */

#ifndef KSTRANSFORMATION_H_
#define KSTRANSFORMATION_H_

#include "Rtypes.h"
#include "TVector3.h"
#include "TRotation.h"

/*!
 * @class Kassiopeia::KSTransformation
 * @author Dan Furse
 *
 * @brief a class that encapsulates a transformation of a geometric object.
 */
namespace Kassiopeia
{

    class KSTransformation
    {
        public:
            KSTransformation();
            virtual ~KSTransformation();

            void Apply( TVector3& point ) const;
            void ApplyRotation( TVector3& point ) const;
            void ApplyDisplacement( TVector3& point ) const;

            void SetOrigin( const TVector3& origin );
            void SetFrameAxisAngle( const Double_t& angle, const Double_t& theta, const Double_t& phi );
            void SetFrameEuler( const Double_t& alpha, const Double_t& beta, const Double_t& gamma );
            void SetXAxis( const TVector3& xaxis );
            void SetYAxis( const TVector3& yaxis );
            void SetZAxis( const TVector3& zaxis );
            const TVector3& GetOrigin() const;
            const TVector3& GetXAxis() const;
            const TVector3& GetYAxis() const;
            const TVector3& GetZAxis() const;

            void SetDisplacement( const TVector3& disp );
            void SetDisplacement( const Double_t& xdisp, const Double_t& ydisp, const Double_t& zdisp );
            const TVector3& GetDisplacement() const;

            void SetRotationAxisAngle( const Double_t& angle, const Double_t& theta, const Double_t& phi );
            void SetRotationEuler( const Double_t& phi, const Double_t& theta, const Double_t& psi );
            void SetRotationConstructive( const Double_t& ztwist, const Double_t& xrot, const Double_t& zrot );
            const TRotation& GetRotation() const;

        private:
            void LocalFromGlobal( const TVector3& point, TVector3& target ) const;
            void GlobalFromLocal( const TVector3& point, TVector3& target ) const;

            TVector3 fOrigin;
            TVector3 fXAxis;
            TVector3 fYAxis;
            TVector3 fZAxis;

            TVector3 fDisplacement;
            TRotation fRotation;
    };

    inline const TVector3& KSTransformation::GetOrigin() const
    {
        return fOrigin;
    }
    inline const TVector3& KSTransformation::GetXAxis() const
    {
        return fXAxis;
    }
    inline const TVector3& KSTransformation::GetYAxis() const
    {
        return fYAxis;
    }
    inline const TVector3& KSTransformation::GetZAxis() const
    {
        return fZAxis;
    }

    inline const TVector3& KSTransformation::GetDisplacement() const
    {
        return fDisplacement;
    }

    inline const TRotation& KSTransformation::GetRotation() const
    {
        return fRotation;
    }

}

#endif /* KSTRANSFORMATION_H_ */
