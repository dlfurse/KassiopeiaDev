#ifndef KSIOTOOLBOX_H_
#define KSIOTOOLBOX_H_

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

    class KSIOToolbox :
        public KSManager
    {
        public:
            static KSIOToolbox* GetInstance();
            virtual ~KSIOToolbox();

        private:
            KSIOToolbox();
            static KSIOToolbox* fInstance;

            //****************
            //subclass control
            //****************

        protected:
            virtual void SetupManagerSubclass() {}
            virtual void PrepareManagerSubclass() {}
            virtual void ShutdownManagerSubclass() {}
            virtual void AbortManagerSubclass() {}

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
            void AddConfigTextFile( KSTextFile* );
            KSTextFile* GetConfigTextFile( const string& aKey );
            KSTextFile* DemandConfigFile( const string& aKey );

            void SetConfigUserDirectory( const string& aDirectory );

        private:
            TextFileMap fConfigTextFileMap;

            string fConfigUserDir;
            string fConfigDefaultDir;

            //**********
            //data files
            //**********

        public:
            void AddDataTextFile( KSTextFile* );
            KSTextFile* GetDataTextFile( const string& aKey );
            KSTextFile* DemandDataTextFile( const string& aKey );

            void AddDataRootFile( KSRootFile* );
            KSRootFile* GetDataRootFile( const string& aKey );
            KSRootFile* DemandDataRootFile( const string& aKey );

            void SetDataUserDirectory( const string& aDirectory );

        private:
            TextFileMap fDataTextFileMap;
            RootFileMap fDataRootFileMap;

            string fDataUserDir;
            string fDataDefaultDir;

            //*************
            //scratch files
            //*************

        public:
            void AddScratchTextFile( KSTextFile* );
            KSTextFile* GetScratchTextFile( const string& aKey );
            KSTextFile* DemandScratchTextFile( const string& aKey );

            void AddScratchRootFile( KSRootFile* );
            KSRootFile* GetScratchRootFile( const string& aKey );
            KSRootFile* DemandScratchRootFile( const string& aKey );

            void SetScratchUserDirectory( const string& aDirectory );

        private:
            TextFileMap fScratchTextFileMap;
            RootFileMap fScratchRootFileMap;

            string fScratchUserDir;
            string fScratchDefaultDir;

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

            //********
            //messages
            //********

        public:
            void AddMessage( KSMessage* aMessage );
            void RemoveMessage( KSMessage* aMessage );

            void SetTerminalVerbosity( const UInt_t& aVerbosity );
            void SetLogVerbosity( const UInt_t& aVerbosity );

        private:
            MessageMap fMessageMap;
            UInt_t fTerminalVerbosity;
            UInt_t fLogVerbosity;

            //*********
            //variables
            //*********

        private:
            KSTokenizer* fTokenizer;
            KSIncludeProcessor* fIncludeProcessor;
            KSVariableProcessor* fVariableProcessor;
    };

    //typedef KSManagerFactoryPrototype< KSIOToolbox > KSIOManagerFactory;

}

#endif
