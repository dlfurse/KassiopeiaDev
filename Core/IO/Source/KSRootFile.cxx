#include "KSRootFile.h"

namespace Kassiopeia
{

    KSRootFile::KSRootFile() :
        fFile( NULL )
    {
    }
    KSRootFile::~KSRootFile()
    {
    }

    Bool_t KSRootFile::Open( Mode aMode )
    {
        vector< string >::iterator BaseIt;
        vector< string >::iterator PathIt;
        for( BaseIt = fBases.begin(); BaseIt != fBases.end(); BaseIt++ )
        {
            for( PathIt = fPaths.begin(); PathIt != fPaths.end(); PathIt++ )
            {
                if( aMode == eRead )
                {
                    fFile = new TFile( (*PathIt + fDirectoryMark + *BaseIt).c_str(), "READ" );
                }
                if( aMode == eWrite )
                {
                    fFile = new TFile( (*PathIt + fDirectoryMark + *BaseIt).c_str(), "RECREATE" );
                }
                if( aMode == eAppend )
                {
                    fFile = new TFile( (*PathIt + fDirectoryMark + *BaseIt).c_str(), "UPDATE" );
                }

                if( fFile->IsZombie() == kTRUE )
                {
                    delete fFile;
                    fFile = NULL;
                    continue;
                }

                fResolvedPath = *PathIt;
                fResolvedBase = *BaseIt;
                fResolvedName = *PathIt + fDirectoryMark + *BaseIt;

                //iomsg = eMessage;
                //iomsg < "KSRootFile::Open";
                //iomsg << "key <" << fKey << "> successfully associated with file <" << fResolvedPath << fDirectoryMark << fResolvedName << ">" << end;
                return kTRUE;

            }
        }

        //iomsg = eWarning;
        //iomsg < "KSRootFile::Open";
        //iomsg << "key <" << fKey << "> could not be associated with any file" << end;
        return kFALSE;
    }
    Bool_t KSRootFile::Close()
    {
        if( fFile != NULL )
        {
            fFile->Close();
            delete fFile;
            fFile = NULL;

            return kTRUE;
        }
        return kFALSE;
    }

    TFile* KSRootFile::File()
    {
        return fFile;
    }

}
