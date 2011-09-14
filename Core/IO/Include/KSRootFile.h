#ifndef KSROOTFILE_H_
#define KSROOTFILE_H_

#include "KSFile.h"

#include "TFile.h"

namespace Kassiopeia
{

    class KSRootFile :
        public KSFile
    {
        public:
            KSRootFile();
            virtual ~KSRootFile();

        public:
            TFile* File();

        protected:
            virtual Bool_t OpenFileSubclass( Mode aMode );
            virtual Bool_t CloseFileSubclass();

        private:
            TFile* fFile;
    };

}

#endif
