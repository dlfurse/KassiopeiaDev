#ifndef KSFILE_H_
#define KSFILE_H_

#include "Rtypes.h"

#include <vector>
using std::vector;

#include <string>
using std::string;

namespace Kassiopeia
{

    class KSFile
    {
        public:
            KSFile();
            virtual ~KSFile();

        public:
            void SetKey( const string& aKey );
            const string& GetKey();

            void AddToPaths( const string& aPath );
            void AddToBases( const string& aBase );
            const string& GetPath() const;
            const string& GetBase() const;
            const string& GetName() const;

        protected:
            string fKey;
            vector< string > fPaths;
            vector< string > fBases;
            string fResolvedPath;
            string fResolvedBase;
            string fResolvedName;

        public:
            typedef enum
            {
                eRead, eWrite, eAppend
            } Mode;
            virtual Bool_t Open( Mode aMode ) = 0;
            virtual Bool_t Close() = 0;

        protected:
            static const string fDirectoryMark;
            static const string fExtensionMark;
    };

}

#endif
