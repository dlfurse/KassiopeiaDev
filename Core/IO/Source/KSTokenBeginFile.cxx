#include "KSTokenBeginFile.h"

namespace Kassiopeia
{

    KSTokenBeginFile::KSTokenBeginFile() :
        KSToken(),
        fFilename( "" )
    {
    }
    KSTokenBeginFile::KSTokenBeginFile( const KSTokenBeginFile& aCopy ) :
            KSToken(),
            fFilename( aCopy.fFilename )
        {
        }
    KSTokenBeginFile::~KSTokenBeginFile()
    {
    }

    void KSTokenBeginFile::SetFilename( const string& filename )
    {
        fFilename = filename;
        return;
    }
    const string& KSTokenBeginFile::GetFilename() const
    {
        return fFilename;
    }

    const string& KSTokenBeginFile::GetTypeName() const
    {
        return fTypeName;
    }
    const string KSTokenBeginFile::fTypeName = string( "BeginFile" );

}
