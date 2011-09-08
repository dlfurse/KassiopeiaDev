#ifndef KSTOKENBEGINPARSING_H_
#define KSTOKENBEGINPARSING_H_

#include "KSToken.h"

namespace Kassiopeia
{

    class KSTokenBeginParsing :
        public KSToken
    {
        public:
            KSTokenBeginParsing();
            virtual ~KSTokenBeginParsing();

            virtual const string& GetTypeName() const;

        private:
            static const string fTypeName;
    };

}

#endif
