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
            virtual Bool_t Open( Mode aMode );
            virtual Bool_t Close();

            fstream& File();

        private:
            fstream* fFile;
    };

}

#endif
