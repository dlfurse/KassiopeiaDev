#include "KSTextFile.h"

#include "KSIOMessage.h"

namespace Kassiopeia
{

    KSTextFile::KSTextFile() :
        fFile( NULL )
    {
    }
    KSTextFile::~KSTextFile()
    {
    }

    Bool_t KSTextFile::OpenFileSubclass( Mode aMode )
    {
        vector< string >::iterator NameIt;
        for( NameIt = fNames.begin(); NameIt != fNames.end(); NameIt++ )
        {
            if( aMode == eRead )
            {
                fFile = new fstream( (*NameIt).c_str(), ios_base::in );
            }
            if( aMode == eWrite )
            {
                fFile = new fstream( (*NameIt).c_str(), ios_base::out );
            }
            if( aMode == eAppend )
            {
                fFile = new fstream( (*NameIt).c_str(), ios_base::app );
            }

            iomsg + eDebug;
            iomsg < "KSTextFile::Open";
            iomsg << "key <" << fKey << "> attempting at <" << *NameIt << ">" << eom;

            if( fFile->fail() == kTRUE )
            {
                delete fFile;
                fFile = NULL;
                continue;
            }

            fResolvedPath = (*NameIt).substr(0,(*NameIt).find_last_of( fDirectoryMark ));
            fResolvedBase = (*NameIt).substr((*NameIt).find_last_of( fDirectoryMark ) + 1);
            fResolvedName = *NameIt;

            iomsg + eNormal;
            iomsg < "KSTextFile::Open";
            iomsg << "key <" << fKey << "> successfully associated with file <" << fResolvedName << ">" << eom;

            return kTRUE;
        }

        vector< string >::iterator BaseIt;
        vector< string >::iterator PathIt;
        for( BaseIt = fBases.begin(); BaseIt != fBases.end(); BaseIt++ )
        {
            for( PathIt = fPaths.begin(); PathIt != fPaths.end(); PathIt++ )
            {
                if( aMode == eRead )
                {
                    fFile = new fstream( (*PathIt + fDirectoryMark + *BaseIt).c_str(), ios_base::in );
                }
                if( aMode == eWrite )
                {
                    fFile = new fstream( (*PathIt + fDirectoryMark + *BaseIt).c_str(), ios_base::out );
                }
                if( aMode == eAppend )
                {
                    fFile = new fstream( (*PathIt + fDirectoryMark + *BaseIt).c_str(), ios_base::app );
                }

                iomsg + eDebug;
                iomsg < "KSTextFile::Open";
                iomsg << "key <" << fKey << "> attempting at <" << *PathIt << fDirectoryMark << *BaseIt << ">" << eom;

                if( fFile->fail() == kTRUE )
                {
                    delete fFile;
                    fFile = NULL;
                    continue;
                }

                fResolvedPath = *PathIt;
                fResolvedBase = *BaseIt;
                fResolvedName = *PathIt + fDirectoryMark + *BaseIt;

                iomsg + eNormal;
                iomsg < "KSTextFile::Open";
                iomsg << "key <" << fKey << "> successfully associated with file <" << fResolvedName << ">" << eom;

                return kTRUE;

            }
        }

        iomsg + eWarning;
        iomsg < "KSTextFile::Open";
        iomsg << "key <" << fKey << "> could not be associated with any file" << eom;

        return kFALSE;
    }
    Bool_t KSTextFile::CloseFileSubclass()
    {
        if( fFile != NULL )
        {
            fFile->close();
            delete fFile;
            fFile = NULL;

            return kTRUE;
        }
        return kFALSE;
    }

    fstream* KSTextFile::File()
    {
        return fFile;
    }

}
