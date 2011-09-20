#ifndef KSVARIABLEPROCESSOR_H_
#define KSVARIABLEPROCESSOR_H_

#include "KSProcessor.h"

#include <stack>
using std::stack;

#include <map>
using std::map;

namespace Kassiopeia
{

    class KSVariableProcessor :
        public KSProcessor
    {
        public:
            KSVariableProcessor();
            virtual ~KSVariableProcessor();

            virtual void ProcessToken( KSTokenBeginFile* aToken );
            virtual void ProcessToken( KSTokenEndFile* aToken );
            virtual void ProcessToken( KSTokenBeginElement* aToken );
            virtual void ProcessToken( KSTokenEndElement* aToken );
            virtual void ProcessToken( KSTokenAttribute* aToken );
            virtual void ProcessToken( KSTokenData* aToken );

        private:
            void Reset();
            bool Replace( string& aString );

            typedef map< string, string > VariableMap;
            typedef VariableMap::value_type VariableEntry;
            typedef VariableMap::iterator VariableIt;
            typedef VariableMap::const_iterator VariableCIt;
            VariableMap* fGlobalMap;
            VariableMap* fFileMap;
            stack< VariableMap* > fFileMapStack;

            typedef enum
            {
                eInactive, eActiveDefine, eActiveUndefine
            } State;
            State fState;
            string fName;
            string fValue;

            static const char fStartBracket = '{';
            static const char fEndBracket = '}';
    };

}

#endif
