#ifndef KSTOKENIZER_H_
#define KSTOKENIZER_H_

#include "KSProcessor.h"

#include <stack>
using std::stack;

namespace Kassiopeia
{

    class KSTextFile;

    class KSTokenizer :
        public KSProcessor
    {
        public:
            KSTokenizer();
            KSTokenizer( KSTokenizer* anActiveTokenizer );
            virtual ~KSTokenizer();
        private:
            KSTokenizer* fOldTokenizer;

            //**********
            //processing
            //**********

        public:
            void ProcessFile( KSTextFile* aFile );
            void IncludeFile( KSTextFile* aFile );

            const string& GetFilePath();
            const string& GetFileName();
            const Int_t& GetFileLine();
            const Int_t& GetFileColumn();

            //*******
            //queuing
            //*******

        private:
            void ToNext();
            Bool_t AtEnd();
            Bool_t AtOneOf( const string& chars );

            KSTextFile* fFile;
            string fPath;
            string fName;
            Int_t fLine;
            Int_t fColumn;
            char fChar;

            //*******
            //parsing
            //*******

        private:
            void ParseBegin();
            void ParseBeginFile();
            void ParseBody();
            void ParseStartElementPre();
            void ParseStartElementName(); // actual start element tokens get sent in transitions from this state, end elements may get sent in transitions from this state via "/>" shorthand.
            void ParseStartElementPost(); // end element tokens may get sent in transitions from this state via "/>" shorthand.
            void ParseAttributeName();
            void ParseAttributeAssignmentPre();
            void ParseAttributeAssignmentPost();
            void ParseAttributeValue(); // actual attribute tokens get sent in transitions from this state.
            void ParseEndElementPre();
            void ParseEndElementName(); // actual end element tokens get sent in transitions from this state.
            void ParseEndElementPost();
            void ParseDataValue(); // actual data tokens get sent in transitions from this state.
            void ParseCompleteFile();
            void ParseComplete();
            void ParseComment();
            void ParseError();

            void (KSTokenizer::*fState)();
            void (KSTokenizer::*fInitialState)();
            void (KSTokenizer::*fFinalState)();

            stack< string > fElementNames;

            //********
            //shipping
            //********

        private:
            string fNameBuffer;
            string fValueBuffer;
            string fErrorBuffer;
            KSTokenBeginParsing* fBeginParsing;
            KSTokenEndParsing* fEndParsing;
            KSTokenBeginFile* fBeginFile;
            KSTokenEndFile* fEndFile;
            KSTokenBeginElement* fBeginElement;
            KSTokenEndElement* fEndElement;
            KSTokenAttribute* fAttribute;
            KSTokenData* fData;
            KSTokenError* fError;

            //**************
            //character sets
            //**************

            static const string fSpace;
            static const string fTab;
            static const string fNewLine;
            static const string fCarriageReturn;

            static const string fLowerCase;
            static const string fUpperCase;
            static const string fNumerals;

            static const string fLeftBraces;
            static const string fOperators;
            static const string fRightBraces;

            static const string fLeftAngle;
            static const string fRightAngle;
            static const string fEqual;
            static const string fSlash;
            static const string fQuote;

            static const string fParameterLeftBrace;
            static const string fParameterRightBrace;

            static const string fWhiteSpaceChars;
            static const string fNameStartChars;
            static const string fNameChars;
            static const string fValueChars;

    };

}

#endif /* KSXMLTOKENIZER_H_ */
