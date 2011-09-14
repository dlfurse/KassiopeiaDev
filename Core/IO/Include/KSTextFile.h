#ifndef KSTEXTFILE_H_
#define KSTEXTFILE_H_

#include "KSFile.h"

#include <fstream>
using std::fstream;
using std::ios_base;

namespace Kassiopeia
{

    class KSTextFile :
        public KSFile
    {
        public:
            KSTextFile();
            virtual ~KSTextFile();

        public:
            fstream* File();

        protected:
            virtual Bool_t OpenFileSubclass( Mode aMode );
            virtual Bool_t CloseFileSubclass();

        private:
            fstream* fFile;
    };

}

#endif
