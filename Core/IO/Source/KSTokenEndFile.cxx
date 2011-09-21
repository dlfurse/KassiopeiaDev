#include "KSTokenEndFile.h"

namespace Kassiopeia
{

    KSTokenEndFile::KSTokenEndFile() :
        KSToken(),
        fFilename( "" )
    {
    }
    KSTokenEndFile::KSTokenEndFile( const KSTokenEndFile& aCopy) :
        KSToken(),
        fFilename( aCopy.fFilename )
    {
    }
    KSTokenEndFile::~KSTokenEndFile()
    {
    }

    void KSTokenEndFile::SetFilename( const string& filename )
    {
        fFilename = filename;
        return;
    }
    const string& KSTokenEndFile::GetFilename() const
    {
        return fFilename;
    }

    const string& KSTokenEndFile::GetTypeName() const
    {
        return fTypeName;
    }
    const string KSTokenEndFile::fTypeName = string( "EndFile" );

}
