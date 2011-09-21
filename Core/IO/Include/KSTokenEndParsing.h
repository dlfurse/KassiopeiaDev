#ifndef KSTOKENENDPARSING_H_
#define KSTOKENENDPARSING_H_

#include "KSToken.h"

namespace Kassiopeia
{

    class KSTokenEndParsing :
        public KSToken
    {
        public:
            KSTokenEndParsing();
            KSTokenEndParsing( const KSTokenEndParsing& aCopy );
            virtual ~KSTokenEndParsing();

            virtual const string& GetTypeName() const;

        private:
            static const string fTypeName;
    };

}

#endif
