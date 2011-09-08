#include "KSTokenBeginFile.h"

namespace Kassiopeia
{

    KSTokenBeginFile::KSTokenBeginFile() :
        fFilename("")
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

    const string KSTokenBeginFile::fTypeName = string("StartFile");

}
