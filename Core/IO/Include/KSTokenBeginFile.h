#ifndef KSTOKENBEGINFILE_H_
#define KSTOKENBEGINFILE_H_

#include "KSToken.h"

namespace Kassiopeia
{

    class KSTokenBeginFile :
        public KSToken
    {
        public:
            KSTokenBeginFile();
            KSTokenBeginFile( const KSTokenBeginFile& aCopy );
            virtual ~KSTokenBeginFile();

            void SetFilename( const string& message );
            const string& GetFilename() const;

            virtual const string& GetTypeName() const;

        private:
            string fFilename;
            static const string fTypeName;
    };

}

#endif
