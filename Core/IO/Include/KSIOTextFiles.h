#ifndef KSIOTEXTFILES_H_
#define KSIOTEXTFILES_H_

#include "KSTextFile.h"

namespace Kassiopeia
{

    class KSConfigTextFile :
        public KSTextFile
    {
        public:
            KSConfigTextFile( const string& aKey );
            virtual ~KSConfigTextFile();
    };

    class KSDataTextFile :
        public KSTextFile
    {
        public:
            KSDataTextFile( const string& aKey );
            virtual ~KSDataTextFile();
    };

    class KSScratchTextFile :
        public KSTextFile
    {
        public:
            KSScratchTextFile( const string& aKey );
            virtual ~KSScratchTextFile();
    };

}

#endif
