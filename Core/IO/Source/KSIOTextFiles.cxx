#include "KSIOTextFiles.h"

#include "KSIOToolbox.h"

namespace Kassiopeia
{

    KSConfigTextFile::KSConfigTextFile( const string& aKey ) :
        KSTextFile()
    {
        fKey = aKey;
        KSIOToolbox::GetInstance()->AddConfigTextFile( this );
    }
    KSConfigTextFile::~KSConfigTextFile()
    {
        KSIOToolbox::GetInstance()->RemoveConfigTextFile( this );
    }

    KSDataTextFile::KSDataTextFile( const string& aKey ) :
        KSTextFile()
    {
        fKey = aKey;
        KSIOToolbox::GetInstance()->AddDataTextFile( this );
    }
    KSDataTextFile::~KSDataTextFile()
    {
        KSIOToolbox::GetInstance()->RemoveDataTextFile( this );
    }

    KSScratchTextFile::KSScratchTextFile( const string& aKey ) :
        KSTextFile()
    {
        fKey = aKey;
        KSIOToolbox::GetInstance()->AddScratchTextFile( this );
    }
    KSScratchTextFile::~KSScratchTextFile()
    {
        KSIOToolbox::GetInstance()->RemoveScratchTextFile( this );
    }

}
