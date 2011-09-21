#ifndef KSTOKENENDFILE_H_
#define KSTOKENENDFILE_H_

#include "KSToken.h"

namespace Kassiopeia
{

    class KSTokenEndFile :
        public KSToken
    {
        public:
            KSTokenEndFile();
            KSTokenEndFile( const KSTokenEndFile& aCopy );
            virtual ~KSTokenEndFile();

            void SetFilename( const string& message );
            const string& GetFilename() const;

            virtual const string& GetTypeName() const;

        private:
            string fFilename;
            static const string fTypeName;
    };

}

#endif
