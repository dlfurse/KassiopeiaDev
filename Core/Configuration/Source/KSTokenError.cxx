#include "KSTokenError.h"

namespace Kassiopeia
{

    KSTokenError::KSTokenError() :
        KSToken(),
        fMessage( "" )
    {
    }

    KSTokenError::~KSTokenError()
    {
    }

    void KSTokenError::SetMessage( const string& message )
    {
        fMessage = message;
        return;
    }
    const string& KSTokenError::GetMessage() const
    {
        return fMessage;
    }
    const string& KSTokenError::GetTypeName() const
    {
        return fTypeName;
    }

    const string KSTokenError::fTypeName = string( "Error" );

}
