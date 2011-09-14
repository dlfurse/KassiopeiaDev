#ifndef KSINCLUDEPROCESSOR_H_
#define KSINCLUDEPROCESSOR_H_

#include "KSProcessor.h"

#include <vector>
using std::vector;
using std::string;

namespace Kassiopeia
{

    class KSTextFile;

    class KSIncludeProcessor :
        public KSProcessor
    {
        public:
            KSIncludeProcessor();
            virtual ~KSIncludeProcessor();

            virtual void ProcessToken( const KSTokenBeginElement* aToken );
            virtual void ProcessToken( const KSTokenEndElement* aToken );
            virtual void ProcessToken( const KSTokenAttribute* aToken );

        private:
            void Reset();

            typedef enum
            {
                eInactive, eActive, eUseNames, eUseKeys
            } State;
            State fState;
            vector< string > fNames;
            vector< string > fPaths;
            vector< string > fBases;
            string fKey;
    };

}

#endif
