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
            const string& GetKey() const;

        protected:
            string fKey;

        public:
            void AddToPaths( const string& aPath );
            void AddToBases( const string& aBase );
            void AddToNames( const string& aName );
            const string& GetPath() const;
            const string& GetBase() const;
            const string& GetName() const;

        protected:
            vector< string > fPaths;
            vector< string > fBases;
            vector< string > fNames;
            string fResolvedPath;
            string fResolvedBase;
            string fResolvedName;

        public:
            typedef enum
            {
                eRead, eWrite, eAppend
            } Mode;

            typedef enum
            {
                eOpen, eClosed
            } State;

            Bool_t Open( Mode aMode );
            Bool_t IsOpen();

            Bool_t Close();
            Bool_t IsClosed();

        protected:
            virtual Bool_t OpenFileSubclass( Mode aMode ) = 0;
            virtual Bool_t CloseFileSubclass() = 0;
            State fState;

        protected:
            static const string fDirectoryMark;
            static const string fExtensionMark;
    };

}

#endif
