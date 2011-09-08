/*
 * KSTransformation.cxx
 *
 * created on: Feb 17, 2011
 * author: dlfurse
 */

#include "KSTransformation.h"

#include "TMath.h"

#include <iostream>

namespace Kassiopeia
{

    KSTransformation::KSTransformation() :
        fOrigin(0.,0.,0.),
        fXAxis(1.,0.,0.),
        fYAxis(0.,1.,0.),
        fZAxis(0.,0.,1.),
        fDisplacement(0.,0.,0.),
        fRotation()
    {
    }
    KSTransformation::~KSTransformation()
    {
    }

    void KSTransformation::LocalFromGlobal(const TVector3& point, TVector3& target) const
    {
        TVector3 PSub = point - fOrigin;

        target.SetXYZ(PSub.Dot(fXAxis),PSub.Dot(fYAxis),PSub.Dot(fZAxis));
        return;
    }
    void KSTransformation::GlobalFromLocal(const TVector3& point, TVector3& target) const
    {
        TVector3 PSub = point.X() * fXAxis + point.Y() * fYAxis + point.Z() * fZAxis;
        target = fOrigin + PSub;
        return;
    }

    void KSTransformation::Apply(TVector3& point) const
    {
        TVector3 LocalPoint;

        LocalFromGlobal(point,LocalPoint);
        LocalPoint = fRotation * LocalPoint;
        LocalPoint = fDisplacement + LocalPoint;
        GlobalFromLocal(LocalPoint,point);

        return;
    }
    void KSTransformation::ApplyRotation(TVector3& point) const
    {
        TVector3 LocalPoint;

        LocalFromGlobal(point,LocalPoint);
        LocalPoint = fRotation * LocalPoint;
        GlobalFromLocal(LocalPoint,point);

        return;
    }
    void KSTransformation::ApplyDisplacement(TVector3& point) const
    {
        TVector3 LocalPoint;
        LocalFromGlobal(point,LocalPoint);
        LocalPoint = fDisplacement + LocalPoint;
        GlobalFromLocal(LocalPoint,point);
        return;
    }

    void KSTransformation::SetOrigin(const TVector3& origin)
    {
        fOrigin = origin;
        return;
    }
    void KSTransformation::SetFrameAxisAngle(const Double_t& angle, const Double_t& theta, const Double_t& phi)
    {
        Double_t CosTheta = TMath::Cos((TMath::Pi()/180.) * theta);
        Double_t SinTheta = TMath::Sin((TMath::Pi()/180.) * theta);
        Double_t CosPhi = TMath::Cos((TMath::Pi()/180.) * phi);
        Double_t SinPhi = TMath::Sin((TMath::Pi()/180.) * phi);

        TVector3 Axis(SinTheta*CosPhi,SinTheta*SinPhi,CosTheta);
        Double_t Angle = (TMath::Pi()/180.) * angle;

        TRotation Orientation;
        Orientation.SetToIdentity();
        Orientation.Rotate(Angle,Axis);

        fXAxis.SetXYZ(1.,0.,0.);
        fXAxis = Orientation * fXAxis;

        fYAxis.SetXYZ(0.,1.,0.);
        fYAxis = Orientation * fYAxis;

        fZAxis.SetXYZ(0.,0.,1.);
        fZAxis = Orientation * fZAxis;

        return;
    }
    void KSTransformation::SetFrameEuler(const Double_t& phi, const Double_t& theta, const Double_t& psi)
    {
        Double_t Phi = (TMath::Pi()/180.) * phi;
        Double_t Theta = (TMath::Pi()/180.) * theta;
        Double_t Psi = (TMath::Pi()/180.) * psi;

        TRotation Orientation;
        Orientation.SetToIdentity();
        Orientation.SetXEulerAngles(Phi,Theta,Psi);

        fXAxis.SetXYZ(1.,0.,0.);
        fXAxis = Orientation * fXAxis;

        fYAxis.SetXYZ(0.,1.,0.);
        fYAxis = Orientation * fYAxis;

        fZAxis.SetXYZ(0.,0.,1.);
        fZAxis = Orientation * fZAxis;

        return;
    }
    void KSTransformation::SetXAxis(const TVector3& localx)
    {
        fXAxis = localx;
        return;
    }
    void KSTransformation::SetYAxis(const TVector3& localy)
    {
        fYAxis = localy;
        return;
    }
    void KSTransformation::SetZAxis(const TVector3& localz)
    {
        fZAxis = localz;
        return;
    }

    void KSTransformation::SetDisplacement(const TVector3& disp)
    {
        fDisplacement = disp;
        return;
    }
    void KSTransformation::SetDisplacement(const Double_t& xdisp, const Double_t& ydisp, const Double_t& zdisp)
    {
        fDisplacement.SetXYZ(xdisp,ydisp,zdisp);
        return;
    }

    void KSTransformation::SetRotationAxisAngle(const Double_t& angle, const Double_t& theta, const Double_t& phi)
    {
        Double_t CosTheta = TMath::Cos((TMath::Pi()/180.) * theta);
        Double_t SinTheta = TMath::Sin((TMath::Pi()/180.) * theta);
        Double_t CosPhi = TMath::Cos((TMath::Pi()/180.) * phi);
        Double_t SinPhi = TMath::Sin((TMath::Pi()/180.) * phi);

        TVector3 Axis(SinTheta*CosPhi,SinTheta*SinPhi,CosTheta);
        Double_t Angle = (TMath::Pi()/180.) * angle;

        fRotation.SetToIdentity();
        fRotation.Rotate(Angle,Axis);

        return;
    }
    void KSTransformation::SetRotationEuler(const Double_t& phi, const Double_t& theta, const Double_t& psi)
    {
        Double_t Phi = (TMath::Pi()/180.) * phi;
        Double_t Theta = (TMath::Pi()/180.) * theta;
        Double_t Psi = (TMath::Pi()/180.) * psi;

        fRotation.SetToIdentity();
        fRotation.SetXEulerAngles(Phi,Theta,Psi);

        return;
    }
    void KSTransformation::SetRotationConstructive(const Double_t& ztwist, const Double_t& xrot, const Double_t& zrot)
    {
        Double_t ZTwist = (TMath::Pi()/180.) * ztwist;
        Double_t XRot = (TMath::Pi()/180.) * xrot;
        Double_t ZRot = (TMath::Pi()/180.) * zrot;

        fRotation.SetToIdentity();
        fRotation.RotateZ(ZTwist);
        fRotation.RotateX(XRot);
        fRotation.RotateZ(ZRot);

        return;
    }

}
