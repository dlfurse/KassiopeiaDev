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
            virtual Bool_t Open( Mode aMode );
            virtual Bool_t Close();

            TFile* File();

        private:
            TFile* fFile;
    };

}

#endif
