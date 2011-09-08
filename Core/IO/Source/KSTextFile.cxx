#include "KSTextFile.h"

namespace Kassiopeia
{

    KSTextFile::KSTextFile() :
        fFile( NULL )
    {
    }
    KSTextFile::~KSTextFile()
    {
    }

    Bool_t KSTextFile::Open( Mode aMode )
    {
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

                if( fFile->fail() == kTRUE )
                {
                    delete fFile;
                    fFile = NULL;
                    continue;
                }

                fResolvedPath = *PathIt;
                fResolvedBase = *BaseIt;
                fResolvedName = *PathIt + fDirectoryMark + *BaseIt;

                //iomsg = eMessage;
                //iomsg < "KSTextFile::Open";
                //iomsg << "key <" << fKey << "> successfully associated with file <" << fResolvedPath << fDirectoryMark << fResolvedName << ">" << end;
                return kTRUE;

            }
        }

        //iomsg = eWarning;
        //iomsg < "KSTextFile::Open";
        //iomsg << "key <" << fKey << "> could not be associated with any file" << end;
        return kFALSE;
    }
    Bool_t KSTextFile::Close()
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

    fstream& KSTextFile::File()
    {
        return *fFile;
    }

}
