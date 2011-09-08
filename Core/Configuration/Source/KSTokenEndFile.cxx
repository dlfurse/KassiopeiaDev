#include "KSTokenEndFile.h"

namespace Kassiopeia
{

    KSTokenEndFile::KSTokenEndFile()
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

    const string KSTokenEndFile::fTypeName = string("EndFile");

}
