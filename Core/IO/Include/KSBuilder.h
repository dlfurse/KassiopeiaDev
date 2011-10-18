#ifndef KSBUILDER_H_
#define KSBUILDER_H_

#include "KSProcessor.h"

namespace Kassiopeia
{

    class KSBuilder :
        public KSProcessor
    {
        public:
            KSBuilder();
            virtual ~KSBuilder();

        public:
            void SetBuilderSystemKey( const string& aKey );
            const string& GetBuilderSystemKey() const;

            void SetBuilderKey( const string& aKey );
            const string& GetBuilderKey() const;

        private:
            string fBuilderSystemKey;
            string fBuilderKey;
    };

}

#endif
