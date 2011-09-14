#include "KSFile.h"

#include <iostream>
using std::cout;
using std::endl;

namespace Kassiopeia
{

    KSFile::KSFile() :
        fKey( "" ),
        fPaths(),
        fBases(),
        fResolvedPath( "" ),
        fResolvedBase( "" ),
        fResolvedName( "" ),
        fState( eClosed )
    {
    }
    KSFile::~KSFile()
    {
    }

    void KSFile::SetKey( const string& aKey )
    {
        fKey = aKey;
        return;
    }
    const string& KSFile::GetKey() const
    {
        return fKey;
    }

    void KSFile::AddToNames( const string& aName )
    {
        fNames.push_back( aName );
        return;
    }
    void KSFile::AddToBases( const string& aBase )
    {
        fBases.push_back( aBase );
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

    Bool_t KSFile::Open( Mode aMode )
    {
        if( fState == eClosed )
        {
            if( OpenFileSubclass( aMode ) == kTRUE )
            {
                fState = eOpen;
                return kTRUE;
            }
            else
            {
                return kFALSE;
            }
        }
        return kTRUE;
    }
    Bool_t KSFile::IsOpen()
    {
        if( fState == eOpen )
        {
            return kTRUE;
        }
        return kFALSE;
    }

    Bool_t KSFile::Close()
    {
        if( fState == eOpen )
        {
            if( CloseFileSubclass() == kTRUE )
            {
                fState = eClosed;
                return kTRUE;
            }
            else
            {
                return kFALSE;
            }
        }
        return kTRUE;
    }
    Bool_t KSFile::IsClosed()
    {
        if( fState == eClosed )
        {
            return kTRUE;
        }
        return kFALSE;
    }

    const string KSFile::fDirectoryMark = string( "/" );
    const string KSFile::fExtensionMark = string( "." );

}
