#include "KSIORootFiles.h"

namespace Kassiopeia
{

    KSDataRootFile::KSDataRootFile( const string& aKey ) :
        KSRootFile()
    {
        fKey = aKey;
        KSIOToolbox::GetInstance()->AddDataRootFile( this );
    }
    KSDataRootFile::~KSDataRootFile()
    {
        KSIOToolbox::GetInstance()->RemoveDataRootFile( this );
    }

    KSScratchRootFile::KSScratchRootFile( const string& aKey ) :
        KSRootFile()
    {
        fKey = aKey;
        KSIOToolbox::GetInstance()->AddScratchRootFile( this );
    }
    KSScratchRootFile::~KSScratchRootFile()
    {
        KSIOToolbox::GetInstance()->RemoveScratchRootFile( this );
    }

}
