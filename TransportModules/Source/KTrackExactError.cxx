#include "KTrackExactError.h"

namespace Kassiopeia
{

    KTrackExactError::KTrackExactError() :
        KTrackError()
    {
    }

    KTrackExactError::~KTrackExactError()
    {
    }

    void KTrackExactError::Reset()
    {
        return;
    }

    const Double_t& KTrackExactError::GetTimeError()
    {
        fTimeError = fData[0];
        return fTimeError;
    }

    const TVector3& KTrackExactError::GetPositionError()
    {
        fPositionError.SetXYZ( fData[1], fData[2], fData[3] );
        return fPositionError;
    }

    const TVector3& KTrackExactError::GetMomentumError()
    {
        fMomentumError.SetXYZ( fData[4], fData[5], fData[6] );
        return fMomentumError;
    }

} /* namespace Kassiopeia */
