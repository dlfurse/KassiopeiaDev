#ifndef KSMANAGER_H_
#define KSMANAGER_H_

#include "Rtypes.h"

#include <string>
using std::string;

#include <map>
using std::map;

namespace Kassiopeia
{

    class KSManager
    {

        public:
            KSManager();
            virtual ~KSManager();

            //**************
            //identification
            //**************

        public:
            virtual const string& GetTypeName() const = 0;

            //*****
            //state
            //*****

        public:
            Bool_t IsSetup() const;
            Bool_t IsPrepared() const;
            Bool_t IsShutdown() const;

        protected:
            typedef enum
            {
                eInstantiated, eSetup, ePrepared, eShutdown
            } State;
            State fState;

            //*******
            //control
            //*******

        public:
            void Setup();
            void Prepare();
            void Shutdown();
            void Abort();

            //******************
            //dependency control
            //******************

        protected:
            void SetupManagerDependencies();
            void PrepareManagerDependencies();
            void ShutdownManagerDependencies();
            void AbortManagerDependencies();

            void AddDependency( const string& aManagerType );
            Bool_t IsDependentOn( const string& aManagerType );

            typedef map< string, KSManager* > DependencyMap;
            typedef DependencyMap::value_type DependencyEntry;
            typedef DependencyMap::iterator DependencyIt;
            typedef DependencyMap::const_iterator DependencyCIt;
            DependencyMap fMap;

            //****************
            //subclass control
            //****************

        protected:
            virtual void SetupManagerSubclass() = 0;
            virtual void PrepareManagerSubclass() = 0;
            virtual void ShutdownManagerSubclass() = 0;
            virtual void AbortManagerSubclass() = 0;
    };

    inline Bool_t KSManager::IsSetup() const
    {
        if( fState == eSetup )
        {
            return kTRUE;
        }
        return kFALSE;
    }

    inline Bool_t KSManager::IsPrepared() const
    {
        if( fState == ePrepared )
        {
            return kTRUE;
        }
        return kFALSE;
    }

    inline Bool_t KSManager::IsShutdown() const
    {
        if( fState == eShutdown )
        {
            return kTRUE;
        }
        return kFALSE;
    }

} // end Kassiopeia namespace

#endif // KSManager_h
