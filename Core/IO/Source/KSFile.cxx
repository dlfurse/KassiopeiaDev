#include "KSFile.h"

namespace Kassiopeia
{

    KSFile::KSFile() :
        fKey( "" ),
        fPaths(),
        fBases(),
        fResolvedPath( "" ),
        fResolvedBase( "" ),
        fResolvedName( "" )
    {
    }
    KSFile::~KSFile()
    {
    }

    void KSFile::AddToBases( const string& aName )
    {
        fBases.push_back( aName );
        return;
    }
    void KSFile::AddToPaths( const string& aPath )
    {
        fPaths.push_back( aPath );
        return;
    }

    const string& KSFile::GetBase() const
    {
        return fResolvedBase;
    }
    const string& KSFile::GetPath() const
    {
        return fResolvedPath;
    }
    const string& KSFile::GetName() const
    {
        return fResolvedName;
    }

    const string KSFile::fDirectoryMark = string( "/" );
    const string KSFile::fExtensionMark = string( "." );

}
