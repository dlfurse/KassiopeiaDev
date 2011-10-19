#ifndef KSIOTOOLBOX_H_
#define KSIOTOOLBOX_H_

#include "KSSingleton.h"
#include "KSManager.h"
#include "KSManagerFactory.h"

#include <vector>
using std::vector;

#include <map>
using std::map;

namespace Kassiopeia
{

    class KSTextFile;
    class KSRootFile;
    class KSMessage;

    class KSTokenizer;
    class KSIncludeProcessor;
    class KSVariableProcessor;
    class KSLoopProcessor;
    class KSBuilderProcessor;

    class KSIOToolbox :
        public KSManager
    {
            //*********
            //singleton
            //*********

        public:
            static KSIOToolbox* GetInstance();

        private:
            KSIOToolbox();
            virtual ~KSIOToolbox();
            static KSIOToolbox* fInstance;

            //****************
            //subclass control
            //****************

        protected:
            virtual void SetupManagerSubclass();
            virtual void PrepareManagerSubclass();
            virtual void ShutdownManagerSubclass();
            virtual void AbortManagerSubclass();

            //************
            //map typedefs
            //************

        private:
            typedef vector< string > DirList;
            typedef DirList::iterator DirListIt;
            typedef DirList::const_iterator DirListCIt;

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

            typedef map< string, string > VariableMap;
            typedef VariableMap::value_type VariableEntry;
            typedef VariableMap::iterator VariableIt;
            typedef VariableMap::const_iterator VariableCIt;

            //*******************
            //configuration files
            //*******************

        public:
            void AddConfigTextFile( KSTextFile* aConfigFile );
            KSTextFile* GetConfigTextFile( const string& aKey );
            KSTextFile* DemandConfigTextFile( const string& aKey );
            void RemoveConfigTextFile( KSTextFile* aConfigFile );

            void AddConfigUserDirectory( const string& aDirectory );

        private:
            TextFileMap fConfigTextFileMap;

            DirList fConfigUserDirs;
            string fConfigDefaultDir;
            static const string fConfigTextExtension;

            //**********
            //data files
            //**********

        public:
            void AddDataTextFile( KSTextFile* aDataFile );
            KSTextFile* GetDataTextFile( const string& aKey );
            KSTextFile* DemandDataTextFile( const string& aKey );
            void RemoveDataTextFile( KSTextFile* aDataFile );

            void AddDataRootFile( KSRootFile* aDataFile );
            KSRootFile* GetDataRootFile( const string& aKey );
            KSRootFile* DemandDataRootFile( const string& aKey );
            void RemoveDataRootFile( KSRootFile* aDataFile );

            void AddDataUserDirectory( const string& aDirectory );

        private:
            TextFileMap fDataTextFileMap;
            RootFileMap fDataRootFileMap;

            DirList fDataUserDirs;
            string fDataDefaultDir;
            static const string fDataTextExtension;
            static const string fDataRootExtension;

            //*************
            //scratch files
            //*************

        public:
            void AddScratchTextFile( KSTextFile* aScratchFile );
            KSTextFile* GetScratchTextFile( const string& aKey );
            KSTextFile* DemandScratchTextFile( const string& aKey );
            void RemoveScratchTextFile( KSTextFile* aScratchFile );

            void AddScratchRootFile( KSRootFile* aScratchFile );
            KSRootFile* GetScratchRootFile( const string& aKey );
            KSRootFile* DemandScratchRootFile( const string& aKey );
            void RemoveScratchRootFile( KSRootFile* aScratchFile );

            void AddScratchUserDirectory( const string& aDirectory );

        private:
            TextFileMap fScratchTextFileMap;
            RootFileMap fScratchRootFileMap;

            DirList fScratchUserDirs;
            string fScratchDefaultDir;
            static const string fScratchTextExtension;
            static const string fScratchRootExtension;

            //********
            //messages
            //********

        public:
            void AddMessage( KSMessage* aMessage );
            KSMessage* GetMessage( const string& aMessage );
            KSMessage* DemandMessage( const string& aMessage );
            void RemoveMessage( KSMessage* aMessage );

            void SetTerminalVerbosity( const UInt_t& aVerbosity );
            void SetLogVerbosity( const UInt_t& aVerbosity );

        private:
            MessageMap fMessageMap;
            UInt_t fTerminalVerbosity;
            UInt_t fLogVerbosity;

            //***********
            //output file
            //***********

        public:
            KSRootFile* GetOutputRootFile();

            void SetOutputUserBase( const string& aName );
            void SetOutputUserDirectory( const string& aDirectory );

        private:
            KSRootFile* fOutputRootFile;

            string fOutputUserBase;
            string fOutputDefaultBase;
            string fOutputUserDir;
            string fOutputDefaultDir;

            //********
            //log file
            //********

        public:
            KSTextFile* GetLogTextFile();

            void SetLogUserBase( const string& aName );
            void SetLogUserDirectory( const string& aDirectory );

        private:
            KSTextFile* fLogTextFile;

            string fLogUserBase;
            string fLogDefaultBase;
            string fLogUserDir;
            string fLogDefaultDir;

            //*********
            //variables
            //*********

        public:
            void AddVariable( const string& aName, const string& aValue );
            VariableMap* GetVariables();

        private:
            VariableMap fVariableMap;

            //*******************
            //config file reading
            //*******************

        public:
            void ProcessConfigFile( const string& aKey );

        private:
            KSTokenizer* fTokenizer;
            KSVariableProcessor* fVariableProcessor;
            KSIncludeProcessor* fIncludeProcessor;
            KSLoopProcessor* fLoopProcessor;
            KSBuilderProcessor* fBuilderProcessor;
    };

}

#endif
