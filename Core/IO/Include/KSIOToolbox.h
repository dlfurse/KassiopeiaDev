#ifndef KSIOTOOLBOX_H_
#define KSIOTOOLBOX_H_

#include "KSManager.h"

#include "KSMessage.h"

#include <vector>
using std::vector;

#include <map>
using std::map;

namespace Kassiopeia
{

    class KSTextFile;
    class KSRootFile;

    class KSIOToolbox :
        public KSManager
    {
        public:
            KSIOToolbox();
            virtual ~KSIOToolbox();

            //**************
            //identification
            //**************

        public:
            virtual const string& GetTypeName() const;

        private:
            static const string fTypeName;

            //************
            //map typedefs
            //************

        private:
            typedef map< string, KSTextFile* > TextFileMap;
            typedef TextFileMap::value_type TextFileEntry;
            typedef TextFileMap::iterator TextFileIt;
            typedef TextFileMap::const_iterator TextFileCIt;

            typedef map< string, KSRootFile* > RootFileMap;
            typedef RootFileMap::value_type RootFileEntry;
            typedef RootFileMap::iterator RootFileIt;
            typedef RootFileMap::const_iterator RootFileCIt;

            typedef map< string, KSMessage* > MessageMap;
            typedef MessageMap::value_type MessageEntry;
            typedef MessageMap::iterator MessageIt;
            typedef MessageMap::const_iterator MessageCIt;

            //*******************
            //configuration files
            //*******************

        public:
            void SetConfigDirectory( const string& aDirectory );

            void AddConfigTextFile( KSTextFile* );
            KSTextFile* GetConfigTextFile( const string& aKey );

        private:
            TextFileMap fConfigTextFileMap;

            string fConfigDir;
            const string fInstallConfigDir;

            //**********
            //data files
            //**********

        public:
            void SetDataDirectory( const string& aDirectory );

            void AddDataTextFile( KSTextFile* );
            KSTextFile* GetDataTextFile( const string& aKey );

            void AddDataRootFile( KSRootFile* );
            KSRootFile* GetDataRootFile( const string& aKey );

        private:
            TextFileMap fDataTextFileMap;
            RootFileMap fDataRootFileMap;

            string fDataDir;
            const string fDataInstallDir;


            //*************
            //scratch files
            //*************

        public:
            void SetScratchDirectory( const string& aDirectory );

            void AddScratchTextFile( KSTextFile* );
            KSTextFile* GetScratchTextFile( const string& aKey );

            void AddScratchRootFile( KSRootFile* );
            KSRootFile* GetScratchRootFile( const string& aKey );

        private:
            TextFileMap fScratchTextFileMap;
            RootFileMap fScratchRootFileMap;

            string fScratchDir;
            const string fScratchInstallDir;

            //************
            //output files
            //************

        public:
            void SetOutputDirectory( const string& aDirectory );
            KSRootFile* GetOutputRootFile();

        private:
            KSRootFile* fOutputRootFile;

            string fOutputDir;
            const string fOutputInstallDir;

            //*********
            //log files
            //*********

        public:
            void SetLogDirectory( const string& aDirectory );
            KSTextFile* GetLogTextFile();

        private:
            KSTextFile* fLogTextFile;

            string fLogDir;
            const string fLogInstallDir;


            //********
            //messages
            //********

        public:
            void SetTerminalVerbosity( const KSMessageSeverity aVerbosity );
            void SetLogVerbosity( const KSMessageSeverity aVerbosity );

            void AddMessage( KSMessage* );
            KSMessage* GetMessage( const string& aKey );

        private:
            MessageMap fMessageMap;

            KSMessageSeverity fTerminalVerbosity;
            KSMessageSeverity fLogVerbosity;

    };

}

#endif
