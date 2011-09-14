#include "KSParticle.h"

#include "KSMagneticField.h"
#include "KSElectricField.h"

//#include "KSMessage.h"

namespace Kassiopeia
{

    KSParticle::~KSParticle()
    {
    }

    KSParticle::KSParticle() :
        fMagneticFieldCalculator( NULL ),
        fElectricFieldCalculator( NULL ),

        fPID( NULL ),
        fMass( NULL ),
        fCharge( NULL ),
        fTotalSpin( NULL ),
        fLifetime( NULL ),

        fTime( 0. ),
        fPosition( 0., 0., 0. ),
        fMomentum( 0., 0., 0. ),
        fVelocity( 0., 0., 0. ),
        fLorentzFactor( 0. ),
        fSpeed( 0. ),
        fKineticEnergy( 0. ),
        fPolarAngleToZ( 0. ),
        fAzimuthalAngleToX( 0. ),

        fGetPositionAction( &KSParticle::DoNothing ),
        fGetMomentumAction( &KSParticle::DoNothing ),
        fGetVelocityAction( &KSParticle::RecalculateVelocity ),
        fGetLorentzFactorAction( &KSParticle::RecalculateLorentzFactor ),
        fGetSpeedAction( &KSParticle::RecalculateSpeed ),
        fGetKineticEnergyAction( &KSParticle::RecalculateKineticEnergy ),
        fGetPolarAngleToZAction( &KSParticle::RecalculatePolarAngleToZ ),
        fGetAzimuthalAngleToXAction( &KSParticle::RecalculateAzimuthalAngleToX ),

        fMagneticField( 0., 0., 0. ),
        fElectricField( 0., 0., 0. ),
        fElectricPotential( 0. ),
        fGradientB( 0. ),
        fGradientE( 0. ),

        fGetMagneticFieldAction( &KSParticle::RecalculateMagneticField ),
        fGetElectricFieldAction( &KSParticle::RecalculateElectricField ),
        fGetElectricPotentialAction( &KSParticle::RecalculateElectricPotential ),
        fGetGradientBAction( &KSParticle::RecalculateGradientB ),
        fGetGradientEAction( &KSParticle::RecalculateGradientE ),

        fLongMomentum( 0. ),
        fTransMomentum( 0. ),
        fLongVelocity( 0. ),
        fTransVelocity( 0. ),
        fPolarAngleToB( 0. ),
        fCyclotronFrequency( 0. ),
        fOrbitalMagneticMoment( 0. ),
        fGuidingCenterPosition( 0., 0., 0. ),

        fGetLongMomentumAction( &KSParticle::RecalculateLongMomentum ),
        fGetTransMomentumAction( &KSParticle::RecalculateTransMomentum ),
        fGetLongVelocityAction( &KSParticle::RecalculateLongVelocity ),
        fGetTransVelocityAction( &KSParticle::RecalculateTransVelocity ),
        fGetPolarAngleToBAction( &KSParticle::RecalculatePolarAngleToB ),
        fGetCyclotronFrequencyAction( &KSParticle::RecalculateCyclotronFrequency ),
        fGetOrbitalMagneticMomentAction( &KSParticle::RecalculateOrbitalMagneticMoment )
    {
    }
    KSParticle::KSParticle( const KSParticle* aParticleToClone ) :
        fMagneticFieldCalculator( aParticleToClone->fMagneticFieldCalculator ),
        fElectricFieldCalculator( aParticleToClone->fElectricFieldCalculator ),

        fPID( aParticleToClone->fPID ),
        fMass( aParticleToClone->fMass ),
        fCharge( aParticleToClone->fCharge ),
        fTotalSpin( aParticleToClone->fTotalSpin ),
        fLifetime( aParticleToClone->fLifetime ),

        fTime( aParticleToClone->fTime ),
        fPosition( aParticleToClone->fPosition ),
        fMomentum( aParticleToClone->fMomentum ),
        fVelocity( aParticleToClone->fVelocity ),
        fLorentzFactor( aParticleToClone->fLorentzFactor ),
        fSpeed( aParticleToClone->fSpeed ),
        fKineticEnergy( aParticleToClone->fKineticEnergy ),
        fPolarAngleToZ( aParticleToClone->fPolarAngleToZ ),
        fAzimuthalAngleToX( aParticleToClone->fAzimuthalAngleToX ),

        fGetPositionAction( aParticleToClone->fGetPositionAction ),
        fGetMomentumAction( aParticleToClone->fGetMomentumAction ),
        fGetVelocityAction( aParticleToClone->fGetVelocityAction ),
        fGetLorentzFactorAction( aParticleToClone->fGetLorentzFactorAction ),
        fGetSpeedAction( aParticleToClone->fGetSpeedAction ),
        fGetKineticEnergyAction( aParticleToClone->fGetKineticEnergyAction ),
        fGetPolarAngleToZAction( aParticleToClone->fGetPolarAngleToZAction ),
        fGetAzimuthalAngleToXAction( aParticleToClone->fGetAzimuthalAngleToXAction ),

        fMagneticField( aParticleToClone->fMagneticField ),
        fElectricField( aParticleToClone->fElectricField ),
        fElectricPotential( aParticleToClone->fElectricPotential ),
        fGradientB( aParticleToClone->fGradientB ),
        fGradientE( aParticleToClone->fGradientE ),

        fGetMagneticFieldAction( aParticleToClone->fGetMagneticFieldAction ),
        fGetElectricFieldAction( aParticleToClone->fGetElectricFieldAction ),
        fGetElectricPotentialAction( aParticleToClone->fGetElectricPotentialAction ),
        fGetGradientBAction( aParticleToClone->fGetGradientBAction ),
        fGetGradientEAction( aParticleToClone->fGetGradientEAction ),

        fLongMomentum( aParticleToClone->fLongMomentum ),
        fTransMomentum( aParticleToClone->fTransMomentum ),
        fLongVelocity( aParticleToClone->fLongVelocity ),
        fTransVelocity( aParticleToClone->fTransVelocity ),
        fPolarAngleToB( aParticleToClone->fPolarAngleToB ),
        fCyclotronFrequency( aParticleToClone->fCyclotronFrequency ),
        fOrbitalMagneticMoment( aParticleToClone->fOrbitalMagneticMoment ),

        fGetLongMomentumAction( aParticleToClone->fGetLongMomentumAction ),
        fGetTransMomentumAction( aParticleToClone->fGetTransMomentumAction ),
        fGetLongVelocityAction( aParticleToClone->fGetLongVelocityAction ),
        fGetTransVelocityAction( aParticleToClone->fGetTransVelocityAction ),
        fGetPolarAngleToBAction( aParticleToClone->fGetPolarAngleToBAction ),
        fGetCyclotronFrequencyAction( aParticleToClone->fGetCyclotronFrequencyAction ),
        fGetOrbitalMagneticMomentAction( aParticleToClone->fGetOrbitalMagneticMomentAction )
    {
    }

    void KSParticle::PullFrom( const KSParticle* aParticleToCopyFrom )
    {
        fMagneticFieldCalculator = aParticleToCopyFrom->fMagneticFieldCalculator;
        fElectricFieldCalculator = aParticleToCopyFrom->fElectricFieldCalculator;

        fPID = aParticleToCopyFrom->fPID;
        fMass = aParticleToCopyFrom->fMass;
        fCharge = aParticleToCopyFrom->fCharge;
        fTotalSpin = aParticleToCopyFrom->fTotalSpin;
        fLifetime = aParticleToCopyFrom->fLifetime;

        fTime = aParticleToCopyFrom->fTime;
        fPosition = aParticleToCopyFrom->fPosition;
        fMomentum = aParticleToCopyFrom->fMomentum;
        fVelocity = aParticleToCopyFrom->fVelocity;
        fLorentzFactor = aParticleToCopyFrom->fLorentzFactor;
        fSpeed = aParticleToCopyFrom->fSpeed;
        fKineticEnergy = aParticleToCopyFrom->fKineticEnergy;
        fPolarAngleToZ = aParticleToCopyFrom->fPolarAngleToZ;
        fAzimuthalAngleToX = aParticleToCopyFrom->fAzimuthalAngleToX;

        fGetPositionAction = aParticleToCopyFrom->fGetPositionAction;
        fGetMomentumAction = aParticleToCopyFrom->fGetMomentumAction;
        fGetVelocityAction = aParticleToCopyFrom->fGetVelocityAction;
        fGetLorentzFactorAction = aParticleToCopyFrom->fGetLorentzFactorAction;
        fGetSpeedAction = aParticleToCopyFrom->fGetSpeedAction;
        fGetKineticEnergyAction = aParticleToCopyFrom->fGetKineticEnergyAction;
        fGetPolarAngleToZAction = aParticleToCopyFrom->fGetPolarAngleToZAction;
        fGetAzimuthalAngleToXAction = aParticleToCopyFrom->fGetAzimuthalAngleToXAction;

        fMagneticField = aParticleToCopyFrom->fMagneticField;
        fElectricField = aParticleToCopyFrom->fElectricField;
        fElectricPotential = aParticleToCopyFrom->fElectricPotential;
        fGradientB = aParticleToCopyFrom->fGradientB;
        fGradientE = aParticleToCopyFrom->fGradientE;

        fGetMagneticFieldAction = aParticleToCopyFrom->fGetMagneticFieldAction;
        fGetElectricFieldAction = aParticleToCopyFrom->fGetElectricFieldAction;
        fGetElectricPotentialAction = aParticleToCopyFrom->fGetElectricPotentialAction;
        fGetGradientBAction = aParticleToCopyFrom->fGetGradientBAction;
        fGetGradientEAction = aParticleToCopyFrom->fGetGradientEAction;

        fLongMomentum = aParticleToCopyFrom->fLongMomentum;
        fTransMomentum = aParticleToCopyFrom->fTransMomentum;
        fLongVelocity = aParticleToCopyFrom->fLongVelocity;
        fTransVelocity = aParticleToCopyFrom->fTransVelocity;
        fPolarAngleToB = aParticleToCopyFrom->fPolarAngleToB;
        fCyclotronFrequency = aParticleToCopyFrom->fCyclotronFrequency;
        fOrbitalMagneticMoment = aParticleToCopyFrom->fOrbitalMagneticMoment;

        fGetLongMomentumAction = aParticleToCopyFrom->fGetLongMomentumAction;
        fGetTransMomentumAction = aParticleToCopyFrom->fGetTransMomentumAction;
        fGetLongVelocityAction = aParticleToCopyFrom->fGetLongVelocityAction;
        fGetTransVelocityAction = aParticleToCopyFrom->fGetTransVelocityAction;
        fGetPolarAngleToBAction = aParticleToCopyFrom->fGetPolarAngleToBAction;
        fGetCyclotronFrequencyAction = aParticleToCopyFrom->fGetCyclotronFrequencyAction;
        fGetOrbitalMagneticMomentAction = aParticleToCopyFrom->fGetOrbitalMagneticMomentAction;
        fGetGCPositionAction = aParticleToCopyFrom->fGetGCPositionAction;
    }
    void KSParticle::PushTo( KSParticle* aParticleToCopyTo ) const
    {
        aParticleToCopyTo->fMagneticFieldCalculator = fMagneticFieldCalculator;
        aParticleToCopyTo->fElectricFieldCalculator = fElectricFieldCalculator;

        aParticleToCopyTo->fPID = fPID;
        aParticleToCopyTo->fMass = fMass;
        aParticleToCopyTo->fCharge = fCharge;
        aParticleToCopyTo->fTotalSpin = fTotalSpin;
        aParticleToCopyTo->fLifetime = fLifetime;

        aParticleToCopyTo->fTime = fTime;
        aParticleToCopyTo->fPosition = fPosition;
        aParticleToCopyTo->fMomentum = fMomentum;
        aParticleToCopyTo->fVelocity = fVelocity;
        aParticleToCopyTo->fLorentzFactor = fLorentzFactor;
        aParticleToCopyTo->fSpeed = fSpeed;
        aParticleToCopyTo->fKineticEnergy = fKineticEnergy;
        aParticleToCopyTo->fPolarAngleToZ = fPolarAngleToZ;
        aParticleToCopyTo->fAzimuthalAngleToX = fAzimuthalAngleToX;

        aParticleToCopyTo->fGetPositionAction = fGetPositionAction;
        aParticleToCopyTo->fGetMomentumAction = fGetMomentumAction;
        aParticleToCopyTo->fGetVelocityAction = fGetVelocityAction;
        aParticleToCopyTo->fGetLorentzFactorAction = fGetLorentzFactorAction;
        aParticleToCopyTo->fGetSpeedAction = fGetSpeedAction;
        aParticleToCopyTo->fGetKineticEnergyAction = fGetKineticEnergyAction;
        aParticleToCopyTo->fGetPolarAngleToZAction = fGetPolarAngleToZAction;
        aParticleToCopyTo->fGetAzimuthalAngleToXAction = fGetAzimuthalAngleToXAction;

        aParticleToCopyTo->fMagneticField = fMagneticField;
        aParticleToCopyTo->fElectricField = fElectricField;
        aParticleToCopyTo->fElectricPotential = fElectricPotential;
        aParticleToCopyTo->fGradientB = fGradientB;
        aParticleToCopyTo->fGradientE = fGradientE;

        aParticleToCopyTo->fGetMagneticFieldAction = fGetMagneticFieldAction;
        aParticleToCopyTo->fGetElectricFieldAction = fGetElectricFieldAction;
        aParticleToCopyTo->fGetElectricPotentialAction = fGetElectricPotentialAction;
        aParticleToCopyTo->fGetGradientBAction = fGetGradientBAction;
        aParticleToCopyTo->fGetGradientEAction = fGetGradientEAction;

        aParticleToCopyTo->fLongMomentum = fLongMomentum;
        aParticleToCopyTo->fTransMomentum = fTransMomentum;
        aParticleToCopyTo->fLongVelocity = fLongVelocity;
        aParticleToCopyTo->fTransVelocity = fTransVelocity;
        aParticleToCopyTo->fPolarAngleToB = fPolarAngleToB;
        aParticleToCopyTo->fCyclotronFrequency = fCyclotronFrequency;
        aParticleToCopyTo->fOrbitalMagneticMoment = fOrbitalMagneticMoment;

        aParticleToCopyTo->fGetLongMomentumAction = fGetLongMomentumAction;
        aParticleToCopyTo->fGetTransMomentumAction = fGetTransMomentumAction;
        aParticleToCopyTo->fGetLongVelocityAction = fGetLongVelocityAction;
        aParticleToCopyTo->fGetTransVelocityAction = fGetTransVelocityAction;
        aParticleToCopyTo->fGetPolarAngleToBAction = fGetPolarAngleToBAction;
        aParticleToCopyTo->fGetCyclotronFrequencyAction = fGetCyclotronFrequencyAction;
        aParticleToCopyTo->fGetOrbitalMagneticMomentAction = fGetOrbitalMagneticMomentAction;
        aParticleToCopyTo->fGetGCPositionAction = fGetGCPositionAction;

        return;
    }
    void KSParticle::ClearCache() const
    {
        fGetPositionAction = &KSParticle::DoNothing;
        fGetMomentumAction = &KSParticle::DoNothing;

        fGetVelocityAction = &KSParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSParticle::RecalculateLorentzFactor;
        fGetSpeedAction = &KSParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSParticle::RecalculateAzimuthalAngleToX;

        fGetMagneticFieldAction = &KSParticle::RecalculateMagneticField;
        fGetElectricFieldAction = &KSParticle::RecalculateElectricField;
        fGetElectricPotentialAction = &KSParticle::RecalculateElectricPotential;
        fGetGradientBAction = &KSParticle::RecalculateGradientB;
        fGetGradientEAction = &KSParticle::RecalculateGradientE;

        fGetLongMomentumAction = &KSParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSParticle::RecalculateOrbitalMagneticMoment;

        return;
    }
    void KSParticle::DoNothing() const
    {
        return;
    }
    void KSParticle::Print() const
    {
        //msg = eMessage;
        //msg < "KSParticle::Print";
        //msg << "Particle State:" << ret;
        //msg << "  id:         " << *fPID << ret;
        //msg << "  mass:       " << *fMass << ret;
        //msg << "  charge:     " << *fCharge << ret;
        //msg << "  total spin: " << *fTotalSpin << ret;
        //msg << "  lifetime:   " << *fLifetime << ret;
        //msg << ret;
        //msg << "  x:          " << fPosition.X() << ret;
        //msg << "  y:          " << fPosition.Y() << ret;
        //msg << "  z:          " << fPosition.Z() << ret;
        //msg << "  px:         " << fMomentum.X() << ret;
        //msg << "  py:         " << fMomentum.Y() << ret;
        //msg << "  pz:         " << fMomentum.Z() << end;
        return;
    }

    //*****************
    //static properties
    //*****************

    const Long_t& KSParticle::GetPID() const
    {
        return *fPID;
    }
    const Double_t& KSParticle::GetMass() const
    {
        return *fMass;
    }
    const Double_t& KSParticle::GetCharge() const
    {
        return *fCharge;
    }
    const Double_t& KSParticle::GetTotalSpin() const
    {
        return *fTotalSpin;
    }
    const Double_t& KSParticle::GetLifetime() const
    {
        return *fLifetime;
    }

    //****
    //time
    //****

    void KSParticle::SetT( const Double_t t )
    {
        fTime = t;
        return;
    }
    const Double_t& KSParticle::GetT() const
    {
        return fTime;
    }

    //********
    //position
    //********

    const TVector3& KSParticle::GetPosition() const
    {
        (this->*fGetPositionAction)();
        return fPosition;
    }
    Double_t KSParticle::GetX() const
    {
        (this->*fGetPositionAction)();
        return fPosition.X();
    }
    Double_t KSParticle::GetY() const
    {
        (this->*fGetPositionAction)();
        return fPosition.Y();
    }
    Double_t KSParticle::GetZ() const
    {
        (this->*fGetPositionAction)();
        return fPosition.Z();
    }

    void KSParticle::SetPosition( const TVector3& aPosition )
    {
        fPosition = aPosition;

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSParticle::SetPosition";
        //msg << "KSBasicParticle: [" << this << "] setting fPosition" << ret;
        //msg << "[" << fPosition.X() << ", " << fPosition.Y() << ", " << fPosition.Z() << "]" << end;
#endif

        fGetMagneticFieldAction = &KSParticle::RecalculateMagneticField;
        fGetElectricFieldAction = &KSParticle::RecalculateElectricField;
        fGetElectricPotentialAction = &KSParticle::RecalculateElectricPotential;

        fGetLongMomentumAction = &KSParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSParticle::RecalculateOrbitalMagneticMoment;

        return;
    }
    void KSParticle::SetPosition( const Double_t& anX, const Double_t& aY, const Double_t& aZ )
    {
        fPosition.SetXYZ( anX, aY, aZ );

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSParticle::SetPosition";
        //msg << "KSBasicParticle: [" << this << "] setting fPosition" << ret;
        //msg << "[" << fPosition.X() << ", " << fPosition.Y() << ", " << fPosition.Z() << "]" << end;
#endif

        fGetMagneticFieldAction = &KSParticle::RecalculateMagneticField;
        fGetElectricFieldAction = &KSParticle::RecalculateElectricField;
        fGetElectricPotentialAction = &KSParticle::RecalculateElectricPotential;

        fGetLongMomentumAction = &KSParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSParticle::RecalculateOrbitalMagneticMoment;

        return;
    }
    void KSParticle::SetX( const Double_t& anX )
    {
        fPosition.SetX( anX );

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSParticle::SetPosition";
        //msg << "KSBasicParticle: [" << this << "] setting fPosition" << ret;
        //msg << "[" << fPosition.X() << ", " << fPosition.Y() << ", " << fPosition.Z() << "]" << end;
#endif

        fGetMagneticFieldAction = &KSParticle::RecalculateMagneticField;
        fGetElectricFieldAction = &KSParticle::RecalculateElectricField;
        fGetElectricPotentialAction = &KSParticle::RecalculateElectricPotential;

        fGetLongMomentumAction = &KSParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSParticle::RecalculateOrbitalMagneticMoment;

        return;
    }
    void KSParticle::SetY( const Double_t& aY )
    {
        fPosition.SetY( aY );

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSParticle::SetPosition";
        //msg << "KSBasicParticle: [" << this << "] setting fPosition" << ret;
        //msg << "[" << fPosition.X() << ", " << fPosition.Y() << ", " << fPosition.Z() << "]" << end;
#endif

        fGetMagneticFieldAction = &KSParticle::RecalculateMagneticField;
        fGetElectricFieldAction = &KSParticle::RecalculateElectricField;
        fGetElectricPotentialAction = &KSParticle::RecalculateElectricPotential;

        fGetLongMomentumAction = &KSParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSParticle::RecalculateOrbitalMagneticMoment;
        return;
    }
    void KSParticle::SetZ( const Double_t& aZ )
    {
        fPosition.SetZ( aZ );

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSParticle::SetPosition";
        //msg << "KSBasicParticle: [" << this << "] setting fPosition" << ret;
        //msg << "[" << fPosition.X() << ", " << fPosition.Y() << ", " << fPosition.Z() << "]" << end;
#endif

        fGetMagneticFieldAction = &KSParticle::RecalculateMagneticField;
        fGetElectricFieldAction = &KSParticle::RecalculateElectricField;
        fGetElectricPotentialAction = &KSParticle::RecalculateElectricPotential;

        fGetLongMomentumAction = &KSParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSParticle::RecalculateOrbitalMagneticMoment;

        return;
    }

    void KSParticle::RecalculatePosition() const
    {
        //this function should not be called since position is a basic variable
        return;
    }

    //********
    //momentum
    //********

    const TVector3& KSParticle::GetMomentum() const
    {
        (this->*fGetMomentumAction)();
        return fMomentum;
    }
    Double_t KSParticle::GetPX() const
    {
        (this->*fGetMomentumAction)();
        return fMomentum.X();
    }
    Double_t KSParticle::GetPY() const
    {
        (this->*fGetMomentumAction)();
        return fMomentum.Y();
    }
    Double_t KSParticle::GetPZ() const
    {
        (this->*fGetMomentumAction)();
        return fMomentum.Z();
    }

    void KSParticle::SetMomentum( const TVector3& aMomentum )
    {
        fMomentum = aMomentum;

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSEMParticle::SetMomentum";
        //msg << "KSEMParticle: [" << this << "] setting fMomentum" << ret;
        //msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << end;
#endif

        fGetVelocityAction = &KSParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSParticle::RecalculateLorentzFactor;
        fGetSpeedAction = &KSParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSParticle::RecalculateAzimuthalAngleToX;

        fGetLongMomentumAction = &KSParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSParticle::RecalculateOrbitalMagneticMoment;

        return;
    }
    void KSParticle::SetMomentum( const Double_t& anX, const Double_t& aY, const Double_t& aZ )
    {
        fMomentum.SetXYZ( anX, aY, aZ );

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSEMParticle::SetMomentum";
        //msg << "KSEMParticle: [" << this << "] setting fMomentum" << ret;
        //msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << end;
#endif

        fGetVelocityAction = &KSParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSParticle::RecalculateLorentzFactor;
        fGetSpeedAction = &KSParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSParticle::RecalculateAzimuthalAngleToX;

        fGetLongMomentumAction = &KSParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSParticle::RecalculateOrbitalMagneticMoment;

        return;
    }
    void KSParticle::SetPX( const Double_t& anX )
    {
        fMomentum.SetX( anX );

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSEMParticle::SetMomentum";
        //msg << "KSEMParticle: [" << this << "] setting fMomentum" << ret;
        //msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << end;
#endif

        fGetVelocityAction = &KSParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSParticle::RecalculateLorentzFactor;
        fGetSpeedAction = &KSParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSParticle::RecalculateAzimuthalAngleToX;

        fGetLongMomentumAction = &KSParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSParticle::RecalculateOrbitalMagneticMoment;

        return;
    }
    void KSParticle::SetPY( const Double_t& aY )
    {
        fMomentum.SetY( aY );

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSEMParticle::SetMomentum";
        //msg << "KSEMParticle: [" << this << "] setting fMomentum" << ret;
        //msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << end;
#endif

        fGetVelocityAction = &KSParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSParticle::RecalculateLorentzFactor;
        fGetSpeedAction = &KSParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSParticle::RecalculateAzimuthalAngleToX;

        fGetLongMomentumAction = &KSParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSParticle::RecalculateOrbitalMagneticMoment;

        return;
    }
    void KSParticle::SetPZ( const Double_t& aZ )
    {
        fMomentum.SetZ( aZ );

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSEMParticle::SetMomentum";
        //msg << "KSEMParticle: [" << this << "] setting fMomentum" << ret;
        //msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << end;
#endif

        fGetVelocityAction = &KSParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSParticle::RecalculateLorentzFactor;
        fGetSpeedAction = &KSParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSParticle::RecalculateAzimuthalAngleToX;

        fGetLongMomentumAction = &KSParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSParticle::RecalculateOrbitalMagneticMoment;

        return;
    }

    void KSParticle::RecalculateMomentum() const
    {
        //this function should not be called since momentum is a basic variable
        return;
    }

    //********
    //velocity
    //********

    const TVector3& KSParticle::GetVelocity() const
    {
        (this->*fGetVelocityAction)();
        return fVelocity;
    }

    void KSParticle::SetVelocity( const TVector3& NewVelocity )
    {
        register Double_t Speed = NewVelocity.Mag();
        register Double_t LorentzFactor = 1.0 / TMath::Sqrt( 1.0 - (Speed * Speed / (KSConst::C() * KSConst::C())) );

        fMomentum = GetMass() * LorentzFactor * NewVelocity;
        fVelocity = NewVelocity;
        fLorentzFactor = LorentzFactor;
        fSpeed = Speed;

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSEMParticle::SetVelocity";
        //msg << "KSEMParticle: [" << this << "] setting fVelocity" << ret;
        //msg << "[" << fVelocity.X() << ", " << fVelocity.Y() << ", " << fVelocity.Z() << "]" << ret;
        //msg << "KSEMParticle: [" << this << "] fMomentum has been recalculated" << ret;
        //msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << ret;
        //msg << "KSEMParticle: [" << this << "] fLorentzFactor and fSpeed have been secondarily recalculated" << ret;
        //msg << "[" << fLorentzFactor << "]" << ret;
        //msg << "[" << fSpeed << "]" << end;
#endif

        fGetVelocityAction = &KSParticle::DoNothing;
        fGetLorentzFactorAction = &KSParticle::DoNothing;
        fGetSpeedAction = &KSParticle::DoNothing;
        fGetKineticEnergyAction = &KSParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSParticle::RecalculateAzimuthalAngleToX;

        fGetLongMomentumAction = &KSParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSParticle::RecalculateOrbitalMagneticMoment;

        return;
    }

    void KSParticle::RecalculateVelocity() const
    {
        fVelocity = (1. / (GetMass() * GetLorentzFactor())) * fMomentum;

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSParticle::RecalculateVelocity";
        //msg << "KSParticle: [" << this << "] recalculating fVelocity" << ret;
        //msg << "[" << fVelocity.X() << ", " << fVelocity.Y() << ", " << fVelocity.Z() << "]" << end;
#endif

        fGetVelocityAction = &KSParticle::DoNothing;

        return;
    }

    //*****
    //speed
    //*****

    const Double_t& KSParticle::GetSpeed() const
    {
        (this->*fGetSpeedAction)();
        return fSpeed;
    }

    void KSParticle::SetSpeed( const Double_t& NewSpeed )
    {
        register Double_t LorentzFactor = 1.0 / TMath::Sqrt( 1.0 - NewSpeed * NewSpeed / (KSConst::C() * KSConst::C()) );
        register Double_t MomentumMagnitude = GetMass() * KSConst::C() * TMath::Sqrt( LorentzFactor * LorentzFactor - 1.0 );

        fMomentum.SetMag( MomentumMagnitude );
        fLorentzFactor = LorentzFactor;
        fSpeed = NewSpeed;

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSEMParticle::SetSpeed";
        //msg << "KSEMParticle: [" << this << "] setting fSpeed" << ret;
        //msg << "[" << fSpeed << "]" << ret;
        //msg << "KSEMParticle: [" << this << "] fMomentum has been recalculated" << ret;
        //msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << ret;
        //msg << "KSEMParticle: [" << this << "] fLorentzFactor has been secondarily recalculated" << ret;
        //msg << "[" << fLorentzFactor << "]" << end;
#endif

        fGetVelocityAction = &KSParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSParticle::DoNothing;
        fGetSpeedAction = &KSParticle::DoNothing;
        fGetKineticEnergyAction = &KSParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSParticle::RecalculateAzimuthalAngleToX;

        fGetLongMomentumAction = &KSParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSParticle::RecalculateOrbitalMagneticMoment;

        return;
    }

    void KSParticle::RecalculateSpeed() const
    {
        fSpeed = GetVelocity().Mag();

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSParticle::RecalculateSpeed";
        //msg << "KSParticle: [" << this << "] recalculating fSpeed" << ret;
        //msg << "[" << fSpeed << "]" << end;
#endif

        fGetSpeedAction = &KSParticle::DoNothing;

        return;
    }

    //**************
    //lorentz factor
    //**************

    const Double_t& KSParticle::GetLorentzFactor() const
    {
        (this->*fGetLorentzFactorAction)();
        return fLorentzFactor;
    }

    void KSParticle::SetLorentzFactor( const Double_t& NewLorentzFactor )
    {
        register Double_t MomentumMagnitude = GetMass() * KSConst::C() * TMath::Sqrt( NewLorentzFactor * NewLorentzFactor - 1.0 );

        fMomentum.SetMag( MomentumMagnitude );
        fLorentzFactor = NewLorentzFactor;

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSEMParticle::SetLorentzFactor";
        //msg << "KSEMParticle: [" << this << "] setting fLorentzFactor" << ret;
        //msg << "[" << fLorentzFactor << "]" << ret;
        //msg << "KSEMParticle: [" << this << "] fMomentum has been recalculated" << ret;
        //msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << end;
#endif

        fGetVelocityAction = &KSParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSParticle::DoNothing;
        fGetSpeedAction = &KSParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSParticle::RecalculateAzimuthalAngleToX;

        fGetLongMomentumAction = &KSParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSParticle::RecalculateOrbitalMagneticMoment;

        return;
    }

    void KSParticle::RecalculateLorentzFactor() const
    {
        fLorentzFactor = TMath::Sqrt( 1.0 + fMomentum.Mag2() / (GetMass() * GetMass() * KSConst::C() * KSConst::C()) );

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSParticle::RecalculateLorentzFactor";
        //msg << "KSParticle: [" << this << "] recalculating fLorentzFactor" << ret;
        //msg << "[" << fLorentzFactor << "]" << end;
#endif

        fGetLorentzFactorAction = &KSParticle::DoNothing;

        return;
    }

    //**************
    //kinetic energy
    //**************

    const Double_t& KSParticle::GetKineticEnergy() const
    {
        (this->*fGetKineticEnergyAction)();
        return fKineticEnergy;
    }

    void KSParticle::SetKineticEnergy( const Double_t& NewKineticEnergy )
    {
        register Double_t NewKineticEnergy_SI = NewKineticEnergy * KSConst::Q();
        register Double_t MomentumMagnitude = (NewKineticEnergy_SI / KSConst::C()) * TMath::Sqrt( 1.0 + (2.0 * GetMass() * KSConst::C() * KSConst::C()) / NewKineticEnergy_SI );

        fMomentum.SetMag( MomentumMagnitude );
        fKineticEnergy = NewKineticEnergy;

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSEMParticle::SetKineticEnergy";
        //msg << "KSEMParticle: [" << this << "] setting fKineticEnergy" << ret;
        //msg << "[" << fKineticEnergy << "]" << ret;
        //msg << "KSEMParticle: [" << this << "] fMomentum has been recalculated" << ret;
        //msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << end;
#endif

        fGetVelocityAction = &KSParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSParticle::RecalculateLorentzFactor;
        fGetSpeedAction = &KSParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSParticle::DoNothing;
        fGetPolarAngleToZAction = &KSParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSParticle::RecalculateAzimuthalAngleToX;

        fGetLongMomentumAction = &KSParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSParticle::RecalculateOrbitalMagneticMoment;

        return;
    }

    void KSParticle::RecalculateKineticEnergy() const
    {
        fKineticEnergy = fMomentum.Mag2() / ((1.0 + GetLorentzFactor()) * GetMass() * KSConst::Q());

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSParticle::RecalculateKineticEnergy";
        //msg << "KSParticle: [" << this << "] recalculating fKineticEnergy" << ret;
        //msg << "[" << fKineticEnergy << "]" << end;
#endif

        fGetKineticEnergyAction = &KSParticle::DoNothing;

        return;
    }

    //****************
    //polar angle to z
    //****************

    const Double_t& KSParticle::GetPolarAngleToZ() const
    {
        (this->*fGetPolarAngleToZAction)();
        return fPolarAngleToZ;
    }

    void KSParticle::SetPolarAngleToZ( const Double_t& NewPolarAngleToZ )
    {
        register Double_t MomentumMagnitude = fMomentum.Mag();
        register Double_t NewPolarAngleToZ_SI = NewPolarAngleToZ / 180. * KSConst::Pi();

        fMomentum.SetXYZ( MomentumMagnitude * TMath::Sin( NewPolarAngleToZ_SI ) * TMath::Cos( GetAzimuthalAngleToX() ), MomentumMagnitude * TMath::Sin( NewPolarAngleToZ_SI ) * TMath::Sin( GetAzimuthalAngleToX() ), MomentumMagnitude * TMath::Cos( NewPolarAngleToZ_SI ) );
        fPolarAngleToZ = NewPolarAngleToZ;

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSEMParticle::SetPolarAngleToZ";
        //msg << "KSEMParticle: [" << this << "] setting fPolarAngleToZ" << ret;
        //msg << "[" << fPolarAngleToZ << "]" << end;
#endif

        fGetVelocityAction = &KSParticle::RecalculateVelocity;
        //fGetLorentzFactorAction unchanged
        //fGetSpeedAction unchanged
        //fGetKineticEnergyAction unchanged
        fGetPolarAngleToZAction = &KSParticle::DoNothing;
        //fGetAzimuthalAngleToXAction unchanged

        fGetLongMomentumAction = &KSParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSParticle::RecalculatePolarAngleToB;
        //fGetCyclotronFrequencyAction unchanged
        fGetOrbitalMagneticMomentAction = &KSParticle::RecalculateOrbitalMagneticMoment;

        return;
    }

    void KSParticle::RecalculatePolarAngleToZ() const
    {
        fPolarAngleToZ = (180. / KSConst::Pi()) * TMath::ACos( fMomentum.Z() / fMomentum.Mag() );

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSParticle::RecalculatePolarAngleToZ";
        //msg << "KSParticle: [" << this << "] recalculating fPolarAngleToZ";
        //msg << "[" << fPolarAngleToZ << "]" << ret;
#endif

        fGetPolarAngleToZAction = &KSParticle::DoNothing;

        return;
    }

    //********************
    //azimuthal angle to x
    //********************

    const Double_t& KSParticle::GetAzimuthalAngleToX() const
    {
        (this->*fGetAzimuthalAngleToXAction)();
        return fAzimuthalAngleToX;
    }

    void KSParticle::SetAzimuthalAngleToX( const Double_t& NewAzimuthalAngleToX )
    {
        register Double_t NewAzimuthalAngleToX_SI = (KSConst::Pi() / 180.) * NewAzimuthalAngleToX;
        register Double_t PolarAngleToZ_SI = (KSConst::Pi() / 180.) * GetPolarAngleToZ();
        register Double_t MomentumMagnitude = fMomentum.Mag();

        fMomentum.SetXYZ( MomentumMagnitude * TMath::Sin( PolarAngleToZ_SI ) * TMath::Cos( NewAzimuthalAngleToX_SI ), MomentumMagnitude * TMath::Sin( PolarAngleToZ_SI ) * TMath::Sin( NewAzimuthalAngleToX_SI ), MomentumMagnitude * TMath::Cos( PolarAngleToZ_SI ) );
        fAzimuthalAngleToX = NewAzimuthalAngleToX;

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSEMParticle::SetAzimuthalAngleToX";
        //msg << "KSEMParticle: [" << this << "] setting fAzimuthalAngleToX" << ret;
        //msg << "[" << fAzimuthalAngleToX << "]" << end;
#endif

        fGetVelocityAction = &KSParticle::RecalculateVelocity;
        //fGetLorentzFactorAction unchanged
        //fGetSpeedAction unchanged
        //fGetKineticEnergyAction unchanged
        //fGetPolarAngleToZAction unchanged
        fGetAzimuthalAngleToXAction = &KSParticle::DoNothing;

        fGetLongMomentumAction = &KSParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSParticle::RecalculatePolarAngleToB;
        //fGetCyclotronFrequencyAction unchanged
        fGetOrbitalMagneticMomentAction = &KSParticle::RecalculateOrbitalMagneticMoment;

        return;
    }

    void KSParticle::RecalculateAzimuthalAngleToX() const
    {
        register Double_t RadialComponent = TMath::Sqrt( GetMomentum().X() * GetMomentum().X() + GetMomentum().Y() * GetMomentum().Y() );
        register Double_t NewCosPhi = GetMomentum().X() / RadialComponent;

        if( GetMomentum().Y() >= 0. )
        {
            fAzimuthalAngleToX = (180. / KSConst::Pi()) * TMath::ACos( NewCosPhi );
        }
        else
        {
            fAzimuthalAngleToX = (180. / KSConst::Pi()) * (2. - TMath::ACos( NewCosPhi ));
        }

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSParticle::RecalculateAzimuthalAngleToX";
        //msg << "KSParticle: [" << this << "] recalculating fAzimuthalAngleToX" << ret;
        //msg << "[" << fAzimuthalAngleToX << "]" << end;
#endif

        fGetAzimuthalAngleToXAction = &KSParticle::DoNothing;

        return;
    }

    //**************
    //magnetic field
    //**************

    const TVector3& KSParticle::GetMagneticField() const
    {
        (this->*fGetMagneticFieldAction)();
        return fMagneticField;
    }

    void KSParticle::SetMagneticField( const TVector3& aMagneticField )
    {
        fMagneticField = aMagneticField;

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSParticle::SetMagneticField";
        //msg << "KSParticle: [" << this << "] setting fMagneticField" << ret;
        //msg << "[" << fMagneticField.X() << ", " << fMagneticField.Y() << ", " << fMagneticField.Z() << "]" << end;
#endif

        fGetMagneticFieldAction = &KSParticle::DoNothing;

        return;
    }

    void KSParticle::RecalculateMagneticField() const
    {
        fMagneticFieldCalculator->GetField( fMagneticField, GetPosition(), GetT() );
        fGetMagneticFieldAction = &KSParticle::DoNothing;
    }

    //**************
    //electric field
    //**************

    const TVector3& KSParticle::GetElectricField() const
    {
        (this->*fGetElectricFieldAction)();
        return fElectricField;
    }
    void KSParticle::RecalculateElectricField() const
    {
        fElectricFieldCalculator->GetField( fElectricField, GetPosition(), GetT() );
        fGetElectricFieldAction = &KSParticle::DoNothing;
    }

    void KSParticle::SetElectricField( const TVector3& aElectricField )
    {
        fElectricField = aElectricField;

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSParticle::SetElectricField";
        //msg << "KSParticle: [" << this << "] setting fElectricField" << ret;
        //msg << "[" << fElectricField.X() << ", " << fElectricField.Y() << ", " << fElectricField.Z() << "]" << end;
#endif

        fGetElectricFieldAction = &KSParticle::DoNothing;

        return;
    }

    //******************
    //electric potential
    //******************

    const Double_t& KSParticle::GetElectricPotential() const
    {
        (this->*fGetElectricPotentialAction)();
        return fElectricPotential;
    }

    void KSParticle::SetElectricPotential( const Double_t& anElectricPotential )
    {
        fElectricPotential = anElectricPotential;

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSParticle::SetElectricPotential";
        //msg << "KSParticle: [" << this << "] setting fElectricPotential" << ret;
        //msg << "[" << fElectricPotential << "]" << end;
#endif

        fGetElectricPotentialAction = &KSParticle::DoNothing;

        return;
    }

    void KSParticle::RecalculateElectricPotential() const
    {
        fElectricFieldCalculator->GetPhi( fElectricPotential, GetPosition(), GetT() );
        fGetElectricPotentialAction = &KSParticle::DoNothing;
    }

    //***********************
    //magnetic field gradient
    //***********************

    const Double_t& KSParticle::GetGradientB( const TVector3& Direction ) const
    {
        static Double_t Epsilon = 1.0e-6;
        TVector3 BAhead;
        TVector3 BBehind;
        fMagneticFieldCalculator->GetField( BAhead, GetPosition() + Epsilon * Direction, GetT() );
        fMagneticFieldCalculator->GetField( BBehind, GetPosition() - Epsilon * Direction, GetT() );

        fGradientB = ((BAhead.Mag() - BBehind.Mag()) / (2.0 * Epsilon));

        return fGradientB;
    }

    void KSParticle::SetGradientB( const Double_t& )
    {

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSParticle::SetElectricPotential";
        //msg << "KSParticle: [" << this << "] setting fElectricPotential" << ret;
        //msg << "[" << fElectricPotential << "]" << end;
#endif

        return;
    }

    void KSParticle::RecalculateGradientB() const
    {
        return;
    }

    //***********************
    //electric field gradient
    //***********************

    const Double_t& KSParticle::GetGradientE( const TVector3& Direction ) const
    {
        static Double_t Epsilon = 1.0e-6;
        TVector3 EAhead;
        TVector3 EBehind;
        fElectricFieldCalculator->GetField( EAhead, GetPosition() + Epsilon * Direction, GetT() );
        fElectricFieldCalculator->GetField( EBehind, GetPosition() - Epsilon * Direction, GetT() );

        fGradientE = ((EAhead.Mag() - EBehind.Mag()) / (2.0 * Epsilon));

        return fGradientE;
    }

    void KSParticle::SetGradientE( const Double_t& )
    {
        return;
    }

    void KSParticle::RecalculateGradientE() const
    {
        return;
    }

    //*********************
    //longitudinal momentum
    //*********************

    void KSParticle::SetLongMomentum( const Double_t& aNewLongMomentum )
    {
        TVector3 LongMomentumVector = GetMagneticField();
        LongMomentumVector.SetMag( aNewLongMomentum - GetLongMomentum() );

        fMomentum += LongMomentumVector;
        fLongMomentum = aNewLongMomentum;

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSEMParticle::SetLongMomentum";
        //msg << "KSEMParticle: [" << this << "] setting fLongMomentum" << ret;
        //msg << "[" << fLongMomentum << "]" << ret;
        //msg << "KSEMParticle: [" << this << "] fMomentum has been recalculated" << ret;
        //msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << end;
#endif

        fGetVelocityAction = &KSParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSParticle::RecalculateLorentzFactor;
        fGetSpeedAction = &KSParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSParticle::RecalculateAzimuthalAngleToX;

        fGetLongMomentumAction = &KSParticle::DoNothing;
        //fGetTransMomentumAction unchanged
        fGetLongVelocityAction = &KSParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSParticle::RecalculateCyclotronFrequency;
        //fGetOrbitalMagneticMomentAction unchanged

        return;
    }
    const Double_t& KSParticle::GetLongMomentum() const
    {
        (this->*fGetLongMomentumAction)();
        return fLongMomentum;
    }
    void KSParticle::RecalculateLongMomentum() const
    {
        fLongMomentum = GetMagneticField().Unit().Dot( fMomentum );

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSEMParticle::RecalculateLongMomentum";
        //msg << "KSEMParticle: [" << this << "] recalculating fLongMomentum" << ret;
        //msg << "[" << fLongMomentum << "]" << end;
#endif

        fGetLongMomentumAction = &KSParticle::DoNothing;

        return;
    }

    //*******************
    //transverse momentum
    //*******************

    void KSParticle::SetTransMomentum( const Double_t& NewTransMomentum )
    {
        TVector3 LongMomentumVector = GetLongMomentum() * GetMagneticField().Unit();
        TVector3 TransMomentumVector = fMomentum - LongMomentumVector;
        TransMomentumVector.SetMag( NewTransMomentum );

        fMomentum = LongMomentumVector + TransMomentumVector;
        fTransMomentum = NewTransMomentum;

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSEMParticle::SetTransMomentum";
        //msg << "KSEMParticle: [" << this << "] setting fTransMomentum" << ret;
        //msg << "[" << fTransMomentum << "]" << ret;
        //msg << "KSEMParticle: [" << this << "] fMomentum has been recalculated" << ret;
        //msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << end;
#endif

        fGetVelocityAction = &KSParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSParticle::RecalculateLorentzFactor;
        fGetSpeedAction = &KSParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSParticle::RecalculateAzimuthalAngleToX;

        //fGetLongMomentumAction unchanged
        fGetTransMomentumAction = &KSParticle::DoNothing;
        fGetLongVelocityAction = &KSParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSParticle::RecalculateOrbitalMagneticMoment;

        return;
    }
    const Double_t& KSParticle::GetTransMomentum() const
    {
        (this->*fGetTransMomentumAction)();
        return fTransMomentum;
    }
    void KSParticle::RecalculateTransMomentum() const
    {
        fTransMomentum = TMath::Sqrt( fMomentum.Mag2() - GetLongMomentum() * GetLongMomentum() );

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSEMParticle::RecalculateTransMomentum";
        //msg << "KSEMParticle: [" << this << "] recalculating fTransMomentum" << ret;
        //msg << "[" << fTransMomentum << "]" << end;
#endif

        fGetTransMomentumAction = &KSParticle::DoNothing;

        return;
    }

    //*********************************************************************************
    //longitudinal velocity
    //*********************************************************************************

    void KSParticle::SetLongVelocity( const Double_t& NewLongVelocity )
    {
        TVector3 LongVelocityVector = GetMagneticField();
        LongVelocityVector.SetMag( NewLongVelocity - GetLongVelocity() );

        fVelocity += LongVelocityVector;
        fSpeed = fVelocity.Mag();
        fLorentzFactor = 1.0 / TMath::Sqrt( 1.0 - (fSpeed * fSpeed / (KSConst::C() * KSConst::C())) );
        fMomentum = (GetMass() * fLorentzFactor) * fVelocity;
        fLongVelocity = NewLongVelocity;

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSEMParticle::SetLongVelocity";
        //msg << "KSEMParticle: [" << this << "] setting fLongVelocity" << ret;
        //msg << "[" << fLongVelocity << "]" << ret;
        //msg << "KSEMParticle: [" << this << "] fMomentum has been recalculated" << ret;
        //msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << ret;
        //msg << "KSEMParticle: [" << this << "] fVelocity, fLorentzFactor and fSpeed have been secondarily recalculated" << ret;
        //msg << "[" << fVelocity.X() << ", " << fVelocity.Y() << ", " << fVelocity.Z() << "]" << ret;
        //msg << "[" << fLorentzFactor << "]" << ret;
        //msg << "[" << fSpeed << "]" << end;
#endif

        fGetVelocityAction = &KSParticle::DoNothing;
        fGetLorentzFactorAction = &KSParticle::DoNothing;
        fGetSpeedAction = &KSParticle::DoNothing;
        fGetKineticEnergyAction = &KSParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSParticle::RecalculateAzimuthalAngleToX;

        fGetLongMomentumAction = &KSParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSParticle::DoNothing;
        fGetTransVelocityAction = &KSParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSParticle::RecalculateOrbitalMagneticMoment;

        return;
    }
    const Double_t& KSParticle::GetLongVelocity() const
    {
        (this->*fGetLongVelocityAction)();
        return fLongVelocity;
    }
    void KSParticle::RecalculateLongVelocity() const
    {
        fLongVelocity = GetLongMomentum() / (GetMass() * GetLorentzFactor());

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSEMParticle::RecalculateLongVelocity";
        //msg << "KSEMParticle: [" << this << "] recalculating fLongVelocity" << ret;
        //msg << "[" << fLongVelocity << "]" << end;
#endif

        fGetLongVelocityAction = &KSParticle::DoNothing;

        return;
    }

    //*******************
    //transverse velocity
    //*******************

    void KSParticle::SetTransVelocity( const Double_t& NewTransVelocity )
    {
        TVector3 TransVelocityVector = GetVelocity() - GetLongVelocity() * GetMagneticField().Unit();
        TransVelocityVector.SetMag( NewTransVelocity - GetTransVelocity() );

        fVelocity += TransVelocityVector;
        fSpeed = fVelocity.Mag();
        fLorentzFactor = 1.0 / TMath::Sqrt( 1.0 - (fSpeed * fSpeed / (KSConst::C() * KSConst::C())) );
        fMomentum = (GetMass() * fLorentzFactor) * fVelocity;
        fTransVelocity = NewTransVelocity;

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSEMParticle::SetTransVelocity";
        //msg << "KSEMParticle: [" << this << "] setting fTransVelocity" << ret;
        //msg << "[" << fTransVelocity << "]" << ret;
        //msg << "KSEMParticle: [" << this << "] fMomentum has been recalculated" << ret;
        //msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << ret;
        //msg << "KSEMParticle: [" << this << "] fVelocity, fLorentzFactor and fSpeed have been secondarily recalculated" << ret;
        //msg << "[" << fVelocity.X() << ", " << fVelocity.Y() << ", " << fVelocity.Z() << "]" << ret;
        //msg << "[" << fLorentzFactor << "]" << ret;
        //msg << "[" << fSpeed << "]";
#endif

        fGetVelocityAction = &KSParticle::DoNothing;
        fGetLorentzFactorAction = &KSParticle::DoNothing;
        fGetSpeedAction = &KSParticle::DoNothing;
        fGetKineticEnergyAction = &KSParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSParticle::RecalculateAzimuthalAngleToX;

        fGetLongMomentumAction = &KSParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSParticle::DoNothing;
        fGetPolarAngleToBAction = &KSParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSParticle::RecalculateOrbitalMagneticMoment;

        return;
    }
    const Double_t& KSParticle::GetTransVelocity() const
    {
        (this->*fGetTransVelocityAction)();
        return fTransVelocity;
    }
    void KSParticle::RecalculateTransVelocity() const
    {
        fTransVelocity = GetTransMomentum() / (GetMass() * GetLorentzFactor());

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSEMParticle::RecalculateTransVelocity";
        //msg << "KSEMParticle: [" << this << "] recalculating fTransVelocity" << ret;
        //msg << "[" << fTransVelocity << "]" << end;
#endif

        fGetTransVelocityAction = &KSParticle::DoNothing;

        return;
    }

    //****************
    //polar angle to B
    //****************

    void KSParticle::SetPolarAngleToB( const Double_t& NewPolarAngleToB )
    {
        register Double_t NewPolarAngleToB_SI = (KSConst::Pi() / 180.) * NewPolarAngleToB;
        register Double_t MomentumMagnitude = fMomentum.Mag();
        TVector3 LongUnit = GetMagneticField().Unit();
        TVector3 TransUnit = (fMomentum - GetLongMomentum() * LongUnit).Unit();

        fMomentum = MomentumMagnitude * TMath::Cos( NewPolarAngleToB_SI ) * LongUnit + MomentumMagnitude * TMath::Sin( NewPolarAngleToB_SI ) * TransUnit;
        fPolarAngleToB = NewPolarAngleToB;

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSEMParticle::SetPolarAngleToB";
        //msg << "KSEMParticle: [" << this << "] setting fPolarAngleToB" << ret;
        //msg << "[" << fPolarAngleToB << "]" << end;
#endif

        fGetVelocityAction = &KSParticle::RecalculateVelocity;
        //fGetLorentzFactorAction unchanged
        //fGetSpeedAction unchanged
        //fGetKineticEnergyAction unchanged
        fGetPolarAngleToZAction = &KSParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSParticle::RecalculateAzimuthalAngleToX;

        fGetLongMomentumAction = &KSParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSParticle::DoNothing;
        //fGetCyclotronFrequencyAction unchanged
        fGetOrbitalMagneticMomentAction = &KSParticle::RecalculateOrbitalMagneticMoment;

        return;
    }
    const Double_t& KSParticle::GetPolarAngleToB() const
    {
        (this->*fGetPolarAngleToBAction)();
        return fPolarAngleToB;
    }
    void KSParticle::RecalculatePolarAngleToB() const
    {
        fPolarAngleToB = TMath::ACos( (fMomentum * fMagneticField) / (fMagneticField.Mag() * fMomentum.Mag()) ) * 180. / KSConst::Pi();

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSEMParticle::RecalculatePolarAngleToB";
        //msg << "KSEMParticle: [" << this << "] recalculating fPolarAngleToB" << ret;
        //msg << "[" << fPolarAngleToB << "]" << end;
#endif

        fGetPolarAngleToBAction = &KSParticle::DoNothing;

        return;
    }

    //*******************
    //cyclotron frequency
    //*******************

    void KSParticle::SetCyclotronFrequency( const Double_t& NewCyclotronFrequency )
    {
        register Double_t LorentzFactor = (GetCharge() * GetMagneticField().Mag()) / (2.0 * KSConst::Pi() * GetMass() * NewCyclotronFrequency);
        register Double_t MomentumMagnitude = GetMass() * KSConst::C() * TMath::Sqrt( LorentzFactor * LorentzFactor - 1.0 );

        fMomentum.SetMag( MomentumMagnitude );
        fLorentzFactor = LorentzFactor;
        fCyclotronFrequency = NewCyclotronFrequency;

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSEMParticle::SetCyclotronFrequency";
        //msg << "KSEMParticle: [" << this << "] setting fCyclotronFrequency" << ret;
        //msg << "[" << fCyclotronFrequency << "]" << ret;
        //msg << "KSEMParticle: [" << this << "] fMomentum has been recalculated" << ret;
        //msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << ret;
        //msg << "KSEMParticle: [" << this << "] fLorentzFactor has been secondarily recalculated" << ret;
        //msg << "[" << fLorentzFactor << "]" << end;
#endif

        fGetVelocityAction = &KSParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSParticle::DoNothing;
        fGetSpeedAction = &KSParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSParticle::RecalculateAzimuthalAngleToX;

        fGetLongMomentumAction = &KSParticle::RecalculateLongMomentum;
        fGetTransMomentumAction = &KSParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSParticle::DoNothing;
        fGetOrbitalMagneticMomentAction = &KSParticle::RecalculateOrbitalMagneticMoment;

        return;
    }
    void KSParticle::RecalculateCyclotronFrequency() const
    {
        fCyclotronFrequency = (TMath::Abs( GetCharge() ) * GetMagneticField().Mag()) / (2.0 * KSConst::Pi() * GetMass() * GetLorentzFactor());

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSEMParticle::RecalculateCyclotronFrequency";
        //msg << "KSEMParticle: [" << this << "] recalculating fCyclotronFrequency" << ret;
        //msg << "[" << fCyclotronFrequency << "]" << end;
#endif

        fGetCyclotronFrequencyAction = &KSParticle::DoNothing;

        return;
    }
    const Double_t& KSParticle::GetCyclotronFrequency() const
    {
        (this->*fGetCyclotronFrequencyAction)();
        return fCyclotronFrequency;
    }

    //***********************
    //orbital magnetic moment
    //***********************

    const Double_t& KSParticle::GetOrbitalMagneticMoment() const
    {

        (this->*fGetOrbitalMagneticMomentAction)();
        return fOrbitalMagneticMoment;
    }
    void KSParticle::SetOrbitalMagneticMoment( const Double_t& NewOrbitalMagneticMoment )
    {
        register Double_t TransMomentumMagnitude = TMath::Sqrt( 2.0 * GetMass() * GetMagneticField().Mag() * NewOrbitalMagneticMoment );
        TVector3 TransMomentumVector = fMomentum - GetLongMomentum() * GetMagneticField().Unit();
        TransMomentumVector.SetMag( TransMomentumMagnitude - GetTransMomentum() );

        fMomentum += TransMomentumVector;
        fTransMomentum = TransMomentumMagnitude;
        fOrbitalMagneticMoment = NewOrbitalMagneticMoment;

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSEMParticle::SetOrbitalMagneticMoment";
        //msg << "KSEMParticle: [" << this << "] setting fOrbitalMagneticMoment" << ret;
        //msg << "[" << fOrbitalMagneticMoment << "]" << ret;
        //msg << "KSEMParticle: [" << this << "] fMomentum has been recalculated" << ret;
        //msg << "[" << fMomentum.X() << ", " << fMomentum.Y() << ", " << fMomentum.Z() << "]" << ret;
        //msg << "KSEMParticle: [" << this << "] fTransMomentum has been secondarily recalculated" << ret;
        //msg << "[" << fTransMomentum << "]" << end;
#endif

        fGetVelocityAction = &KSParticle::RecalculateVelocity;
        fGetLorentzFactorAction = &KSParticle::RecalculateLorentzFactor;
        fGetSpeedAction = &KSParticle::RecalculateSpeed;
        fGetKineticEnergyAction = &KSParticle::RecalculateKineticEnergy;
        fGetPolarAngleToZAction = &KSParticle::RecalculatePolarAngleToZ;
        fGetAzimuthalAngleToXAction = &KSParticle::RecalculateAzimuthalAngleToX;

        //fGetLongMomentumAction unchanged
        fGetTransMomentumAction = &KSParticle::RecalculateTransMomentum;
        fGetLongVelocityAction = &KSParticle::RecalculateLongVelocity;
        fGetTransVelocityAction = &KSParticle::RecalculateTransVelocity;
        fGetPolarAngleToBAction = &KSParticle::RecalculatePolarAngleToB;
        fGetCyclotronFrequencyAction = &KSParticle::RecalculateCyclotronFrequency;
        fGetOrbitalMagneticMomentAction = &KSParticle::DoNothing;

        return;
    }
    void KSParticle::RecalculateOrbitalMagneticMoment() const
    {
        fOrbitalMagneticMoment = (GetTransMomentum() * GetTransMomentum()) / (2.0 * GetMass() * GetMagneticField().Mag());

#ifdef DEBUG_VERBOSE
        //msg = eDebug;
        //msg < "KSEMParticle::RecalculateOrbitalMagneticMoment";
        //msg << "KSEMParticle: [" << this << "] recalculating fOrbitalMagneticMoment" << ret;
        //msg << "[" << fOrbitalMagneticMoment << "]" << end;
#endif

        fGetOrbitalMagneticMomentAction = &KSParticle::DoNothing;

        return;
    }

} /* namespace Kassiopeia */
