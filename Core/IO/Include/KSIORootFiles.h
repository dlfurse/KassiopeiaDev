#ifndef KSIOROOTFILES_H_
#define KSIOROOTFILES_H_

#include "KSRootFile.h"

namespace Kassiopeia
{

    class KSDataRootFile :
        public KSRootFile
    {
        public:
            KSDataRootFile( const string& aKey );
            virtual ~KSDataRootFile();
    };

    class KSScratchRootFile :
        public KSRootFile
    {
        public:
            KSScratchRootFile( const string& aKey );
            virtual ~KSScratchRootFile();
    };

}

#endif
