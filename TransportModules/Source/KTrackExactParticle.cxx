#include "KTrackExactParticle.h"

namespace Kassiopeia
{

    KTrackExactParticle::KTrackExactParticle() :
        KTrackParticle(),
        fGetMagneticFieldPtr( &KTrackExactParticle::RecalculateMagneticField ),
        fGetElectricFieldPtr( &KTrackExactParticle::RecalculateElectricField ),
        fGetElectricPotentialPtr( &KTrackExactParticle::RecalculateElectricPotential )
    {
    }
    KTrackExactParticle::~KTrackExactParticle()
    {
    }

    //*************
    //configuration
    //*************

    void KTrackExactParticle::Reset()
    {
        fGetMagneticFieldPtr = &KTrackExactParticle::RecalculateMagneticField;
        fGetElectricFieldPtr = &KTrackExactParticle::RecalculateElectricField;
        fGetElectricPotentialPtr = &KTrackExactParticle::RecalculateElectricPotential;
        return;
    }

    //*******
    //actions
    //*******

    void KTrackExactParticle::PullUpdate()
    {
        if( (GetTime() == fParticle->GetT()) && (GetPosition() == fParticle->GetPosition()) && (GetMomentum() == fParticle->GetMomentum()) )
        {
            return;
        }

        fData[0] = fParticle->GetT();
        fData[1] = fParticle->GetX();
        fData[2] = fParticle->GetY();
        fData[3] = fParticle->GetZ();
        fData[4] = fParticle->GetPX();
        fData[5] = fParticle->GetPY();
        fData[6] = fParticle->GetPZ();

        Reset();

        return;
    }
    void KTrackExactParticle::PushUpdate() const
    {
        fParticle->SetT( fData[0] );
        fParticle->SetPosition( TVector3( &fData[1] ) );
        fParticle->SetMomentum( TVector3( &fData[4] ) );
    }

    //*****************
    //dynamic variables
    //*****************

    //setters

    const Double_t& KTrackExactParticle::GetTime() const
    {
        fTime = fData[0];
        return fTime;
    }
    const TVector3& KTrackExactParticle::GetPosition() const
    {
        fPosition.SetXYZ( fData[1], fData[2], fData[3] );
        return fPosition;
    }
    const TVector3& KTrackExactParticle::GetMomentum() const
    {
        fMomentum.SetXYZ( fData[4], fData[5], fData[6] );
        return fMomentum;
    }
    const TVector3& KTrackExactParticle::GetVelocity() const
    {
        fVelocity = (1. / (GetMass() * GetLorentzFactor())) * GetMomentum();
        return fVelocity;
    }
    const Double_t& KTrackExactParticle::GetLorentzFactor() const
    {
        fLorentzFactor = TMath::Sqrt( 1. + GetMomentum().Mag2() / (GetMass() * GetMass() * KSConst::C() * KSConst::C()) );
        return fLorentzFactor;
    }
    const Double_t& KTrackExactParticle::GetKineticEnergy() const
    {
        fKineticEnergy = GetMomentum().Mag2() / ((1. + GetLorentzFactor()) * fMass);
        return fKineticEnergy;
    }

    const TVector3& KTrackExactParticle::GetMagneticField() const
    {
        (this->*fGetMagneticFieldPtr)();
        return fMagneticField;
    }
    const TVector3& KTrackExactParticle::GetElectricField() const
    {
        (this->*fGetElectricFieldPtr)();
        return fElectricField;
    }
    const Double_t& KTrackExactParticle::GetElectricPotential() const
    {
        (this->*fGetElectricPotentialPtr)();
        return fElectricPotential;
    }
    const Double_t& KTrackExactParticle::GetGradientB( const TVector3& aDirection ) const
    {
        static const Double_t Epsilon = 1.e-6;
        GetPosition();
        TVector3 Direction = aDirection.Unit();

        TVector3 RPlus = fPosition + Epsilon * Direction;
        TVector3 BPlus;
        fMagneticFieldCalculator->GetField( BPlus, RPlus, GetTime() );

        TVector3 RMinus = fPosition - Epsilon * Direction;
        TVector3 BMinus;
        fMagneticFieldCalculator->GetField( BMinus, RMinus, GetTime() );

        fGradientB = (BPlus - BMinus).Mag() / (2. * Epsilon);

        return fGradientB;
    }
    const Double_t& KTrackExactParticle::GetGradientE( const TVector3& aDirection ) const
    {
        static const Double_t Epsilon = 1.e-6;
        GetPosition();
        TVector3 Direction = aDirection.Unit();

        TVector3 RPlus = fPosition + Epsilon * Direction;
        TVector3 EPlus;
        fElectricFieldCalculator->GetField( EPlus, RPlus, GetTime() );

        TVector3 RMinus = fPosition - Epsilon * Direction;
        TVector3 EMinus;
        fElectricFieldCalculator->GetField( EMinus, RMinus, GetTime() );

        fGradientE = (EPlus - EMinus).Mag() / (2. * Epsilon);

        return fGradientE;
    }

    const Double_t& KTrackExactParticle::GetLongMomentum() const
    {
        fLongMomentum = GetMomentum().Dot( GetMagneticField().Unit() );
        return fLongMomentum;
    }
    const Double_t& KTrackExactParticle::GetTransMomentum() const
    {
        fTransMomentum = (GetMomentum() - GetMomentum().Dot( GetMagneticField().Unit() )).Mag();
        return fTransMomentum;
    }
    const Double_t& KTrackExactParticle::GetLongVelocity() const
    {
        fLongVelocity = GetLongMomentum() / (GetMass() * GetLorentzFactor());
        return fLongVelocity;
    }
    const Double_t& KTrackExactParticle::GetTransVelocity() const
    {
        fTransVelocity = GetTransMomentum() / (GetMass() * GetLorentzFactor());
        return fTransVelocity;
    }
    const Double_t& KTrackExactParticle::GetCyclotronFrequency() const
    {
        fCyclotronFrequency = (TMath::Abs( fCharge ) * GetMagneticField().Mag()) / (2. * KSConst::Pi() * GetLorentzFactor() * GetMass());
        return fCyclotronFrequency;
    }
    const Double_t& KTrackExactParticle::GetOrbitalMagneticMoment() const
    {
        fOrbitalMagneticMoment = (GetTransMomentum() * GetTransMomentum()) / (2. * GetMagneticField().Mag() * GetMass());
        return fOrbitalMagneticMoment;
    }

    //setters
    /*

    void KTrackExactParticle::SetTime( const Double_t& aTime )
    {
        fData[0] = aTime;
        fGetMagneticFieldPtr = &KTrackExactParticle::RecalculateMagneticField;
        fGetElectricFieldPtr = &KTrackExactParticle::RecalculateElectricField;
        fGetElectricPotentialPtr = &KTrackExactParticle::RecalculateElectricPotential;
        return;
    }
    void KTrackExactParticle::SetPosition( const TVector3& aPosition )
    {
        fData[1] = aPosition.X();
        fData[2] = aPosition.X();
        fData[3] = aPosition.X();
        fGetMagneticFieldPtr = &KTrackExactParticle::RecalculateMagneticField;
        fGetElectricFieldPtr = &KTrackExactParticle::RecalculateElectricField;
        fGetElectricPotentialPtr = &KTrackExactParticle::RecalculateElectricPotential;
        return;
    }
    void KTrackExactParticle::SetMomentum( const TVector3& aMomentum )
    {
        fData[4] = aMomentum.X();
        fData[5] = aMomentum.X();
        fData[6] = aMomentum.X();
        return;
    }
    void KTrackExactParticle::SetVelocity( const TVector3& aVelocity )
    {
        register Double_t Speed = aVelocity.Mag();
        register Double_t LorentzFactor = 1. / TMath::Sqrt( 1. - (Speed * Speed / (KSConst::C() * KSConst::C())) );
        register Double_t Scale = GetMass() * LorentzFactor;
        fData[4] = Scale * aVelocity.X();
        fData[5] = Scale * aVelocity.Y();
        fData[6] = Scale * aVelocity.Z();
        return;
    }
    void KTrackExactParticle::SetLorentzFactor( const Double_t& aLorentzFactor )
    {
        register Double_t NewMomentumMagnitude = GetMass() * KSConst::C() * TMath::Sqrt( aLorentzFactor * aLorentzFactor - 1. );
        register Double_t OldMomentumMagnitude = TMath::Sqrt( fData[4] * fData[4] + fData[5] * fData[5] + fData[6] * fData[6] );
        register Double_t Scale = NewMomentumMagnitude / OldMomentumMagnitude;
        fData[4] *= Scale;
        fData[5] *= Scale;
        fData[6] *= Scale;
        return;
    }
    void KTrackExactParticle::SetKineticEnergy( const Double_t& aKineticEnergy )
    {
        register Double_t NewMomentumMagnitude = (aKineticEnergy / KSConst::C()) * TMath::Sqrt( 1. + (2. * GetMass() * KSConst::C() * KSConst::C()) / aKineticEnergy );
        register Double_t OldMomentumMagnitude = TMath::Sqrt( fData[4] * fData[4] + fData[5] * fData[5] + fData[6] * fData[6] );
        register Double_t Scale = NewMomentumMagnitude / OldMomentumMagnitude;
        fData[4] *= Scale;
        fData[5] *= Scale;
        fData[6] *= Scale;
        return;
    }
    void KTrackExactParticle::SetLongMomentum( const Double_t& aLongMomentum )
    {
        TVector3 LongMomentumIncrement = (aLongMomentum - GetLongMomentum()) * GetMagneticField().Unit();
        fData[4] += LongMomentumIncrement.X();
        fData[5] += LongMomentumIncrement.Y();
        fData[6] += LongMomentumIncrement.Z();
        return;
    }
    void KTrackExactParticle::SetTransMomentum( const Double_t& aTransMomentum )
    {
        TVector3 LongMomentumVector = GetLongMomentum() * GetMagneticField().Unit();
        TVector3 TransMomentumIncrement = (aTransMomentum - GetTransMomentum()) * (GetMomentum() - LongMomentumVector).Unit();
        fData[4] += TransMomentumIncrement.X();
        fData[5] += TransMomentumIncrement.Y();
        fData[6] += TransMomentumIncrement.Z();
        return;
    }
    void KTrackExactParticle::SetLongVelocity( const Double_t& aLongVelocity )
    {
        TVector3 LongVelocityIncrement = (aLongVelocity - GetLongVelocity()) * GetMagneticField().Unit();
        TVector3 Velocity = GetVelocity() + LongVelocityIncrement;
        Double_t Speed = Velocity.Mag();
        Double_t LorentzFactor = 1. / TMath::Sqrt( 1. - (Speed * Speed / (KSConst::C() * KSConst::C())) );
        Double_t Scale = GetMass() * LorentzFactor;
        fData[4] = Scale * Velocity.X();
        fData[5] = Scale * Velocity.Y();
        fData[6] = Scale * Velocity.Z();
        return;
    }
    void KTrackExactParticle::SetTransVelocity( const Double_t& aTransVelocity )
    {
        TVector3 LongVelocityVector = GetLongVelocity() * GetMagneticField().Unit();
        TVector3 TransVelocityIncrement = (aTransVelocity - GetTransVelocity()) * (GetVelocity() - LongVelocityVector).Unit();
        TVector3 Velocity = GetVelocity() + TransVelocityIncrement;
        Double_t Speed = Velocity.Mag();
        Double_t LorentzFactor = 1. / TMath::Sqrt( 1. - (Speed * Speed / (KSConst::C() * KSConst::C())) );
        Double_t Scale = GetMass() * LorentzFactor;
        fData[4] = Scale * Velocity.X();
        fData[5] = Scale * Velocity.Y();
        fData[6] = Scale * Velocity.Z();
        return;
    }
    void KTrackExactParticle::SetCyclotronFrequency( const Double_t& aCyclotronFrequency )
    {
        register Double_t LorentzFactor = (GetCharge() * GetMagneticField().Mag()) / (2. * KSConst::Pi() * GetMass() * aCyclotronFrequency);
        register Double_t NewMomentumMagnitude = GetMass() * KSConst::C() * TMath::Sqrt( LorentzFactor * LorentzFactor - 1. );
        register Double_t OldMomentumMagnitude = TMath::Sqrt( fData[4] * fData[4] + fData[5] * fData[5] + fData[6] * fData[6] );
        register Double_t Scale = NewMomentumMagnitude / OldMomentumMagnitude;
        fData[4] *= Scale;
        fData[5] *= Scale;
        fData[6] *= Scale;
    }
    void KTrackExactParticle::SetOrbitalMagneticMoment( const Double_t& anOrbitalMagneticMoment )
    {
        Double_t TransMomentumMagnitude = TMath::Sqrt( 2.0 * GetMass() * GetMagneticField().Mag() * anOrbitalMagneticMoment );
        TVector3 LongMomentumVector = GetLongMomentum() * GetMagneticField().Unit();
        TVector3 TransMomentumIncrement = (TransMomentumMagnitude - GetTransMomentum()) * (GetMomentum() - LongMomentumVector).Unit();
        fData[4] += TransMomentumIncrement.X();
        fData[5] += TransMomentumIncrement.Y();
        fData[6] += TransMomentumIncrement.Z();
        return;
    }
    */

    //cache

    void KTrackExactParticle::DoNothing() const
    {
        return;
    }
    void KTrackExactParticle::RecalculateMagneticField() const
    {
        fMagneticFieldCalculator->GetField( fMagneticField, GetPosition(), GetTime() );
        fGetMagneticFieldPtr = &KTrackExactParticle::DoNothing;
        return;
    }
    void KTrackExactParticle::RecalculateElectricField() const
    {
        fElectricFieldCalculator->GetField( fElectricField, GetPosition(), GetTime() );
        fGetElectricFieldPtr = &KTrackExactParticle::DoNothing;
        return;
    }
    void KTrackExactParticle::RecalculateElectricPotential() const
    {
        fElectricFieldCalculator->GetPhi( fElectricPotential, GetPosition(), GetTime() );
        fGetElectricPotentialPtr = &KTrackExactParticle::DoNothing;
        return;
    }

} /* namespace Kassiopeia */

