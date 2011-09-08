// $Id$

/*
 Class: KSLog
 Author: N. Oblath

 For full class documentation: KSLog.h

 Revision History
 Date         Name          Brief description
 -----------------------------------------------
 25/03/2010   N. Oblath     First version
 07/04/2010   N. Oblath     Added error files

 */

#include "KSLog.h"

#include "TTimeStamp.h"

#include <sstream>
using std::stringstream;

using std::endl;

namespace Kassiopeia
{

    KSLog::KSLog()
    {
    }

    KSLog::~KSLog()
    {
    }

    KSLog* KSLog::GetInstance()
    {
        if( !fKSLogInstance ) CreateNewInstance();
        return fKSLogInstance;
    }

    //***************

    void KSLog::CreateNewInstance()
    {
        fKSLogInstance = new KSLog();
        return;
    }

    void KSLog::DeleteInstance()
    {
        if( fLogFileIsOpen ) EndLog();
        if( fErrorFileIsOpen ) EndError();
        if( fKSLogInstance != NULL )
        {
            delete fKSLogInstance;
            fKSLogInstance = NULL;
        }
    }

    // Initialize the static members
    KSLog* KSLog::fKSLogInstance = NULL;

    std::ofstream KSLog::fLogFile;
    std::string KSLog::fLogFileName( "Kassiopeia.log" );
    Bool_t KSLog::fLogFileIsOpen = kFALSE;
    Bool_t KSLog::fUseAutomaticLogFileName = kTRUE;

    std::ofstream KSLog::fErrorFile;
    std::string KSLog::fErrorFileName( "Kassiopeia.err" );
    Bool_t KSLog::fErrorFileIsOpen = kFALSE;
    Bool_t KSLog::fUseAutomaticErrorFileName = kTRUE;

    //***************

    void KSLog::StartLog()
    {

        if( fLogFileIsOpen )
        {
            std::cout << "MESSAGE (KSLog::StartLog): Log file is already open" << endl;
            return;
        }

        TTimeStamp *tTimeStamper = new TTimeStamp();
        UInt_t tDate = tTimeStamper->GetDate();
        UInt_t tTime = tTimeStamper->GetTime();
        delete tTimeStamper;

        if( fUseAutomaticLogFileName )
        {
            stringstream tNameStream( stringstream::out );
            tNameStream << "Kassiopeia_" << tDate << "_" << tTime << ".log";
            fLogFileName = tNameStream.str();
        }

        fLogFile.open( fLogFileName.c_str() );
        fLogFileIsOpen = kTRUE;

        fLogFile << "Log file started: " << tDate << ", " << tTime << " UTC" << endl;

        return;

    }

    void KSLog::EndLog()
    {

        if( !fLogFileIsOpen )
        {
            std::cout << "MESSAGE (KSLog::EndLog): No log file is open" << endl;
            return;
        }

        TTimeStamp *tTimeStamper = new TTimeStamp();
        UInt_t tDate = tTimeStamper->GetDate();
        UInt_t tTime = tTimeStamper->GetTime();
        delete tTimeStamper;

        fLogFile << "Log file ended: " << tDate << ", " << tTime << " UTC" << endl;

        fLogFile.close();
        fLogFileIsOpen = kFALSE;

        return;

    }

    const string& KSLog::GetLogFileName() const
    {
        return fLogFileName;
    }

    void KSLog::SetLogFileName( const Char_t* aNewName )
    {

        if( fLogFileIsOpen )
        {
            std::cout << "MESSAGE (KSLog::SetLogFileName): New log file name set; will only be used if a new log is started" << endl;
        }

        if( aNewName == NULL )
        {
            fUseAutomaticLogFileName = kTRUE;
            return;
        }

        fLogFileName.assign( aNewName );
        fUseAutomaticLogFileName = kFALSE;

        return;

    }

    //***************

    void KSLog::StartError()
    {

        if( fErrorFileIsOpen )
        {
            std::cout << "MESSAGE (KSLog::StartError): Error file is already open" << endl;
            return;
        }

        TTimeStamp *tTimeStamper = new TTimeStamp();
        UInt_t tDate = tTimeStamper->GetDate();
        UInt_t tTime = tTimeStamper->GetTime();
        delete tTimeStamper;

        if( fUseAutomaticLogFileName )
        {
            stringstream tNameStream( stringstream::out );
            tNameStream << "Kassiopeia_" << tDate << "_" << tTime << ".err";
            fErrorFileName = tNameStream.str();
        }

        fErrorFile.open( fErrorFileName.c_str() );
        fErrorFileIsOpen = kTRUE;

        fErrorFile << "Error file started: " << tDate << ", " << tTime << " UTC" << endl;

        return;

    }

    void KSLog::EndError()
    {
        if( !fErrorFileIsOpen )
        {
            std::cout << "MESSAGE (KSLog::EndError): Error file is not open" << endl;
            return;
        }

        TTimeStamp *tTimeStamper = new TTimeStamp();
        UInt_t tDate = tTimeStamper->GetDate();
        UInt_t tTime = tTimeStamper->GetTime();
        delete tTimeStamper;

        fErrorFile << "Error file ended: " << tDate << ", " << tTime << " UTC" << endl;

        fErrorFile.close();
        fErrorFileIsOpen = kFALSE;

        return;
    }

    const string& KSLog::GetErrorFileName() const
    {
        return fErrorFileName;
    }

    void KSLog::SetErrorFileName( const Char_t* aNewName )
    {

        if( fErrorFileIsOpen )
        {
            std::cout << "MESSAGE (KSLog::SetErrorFileName): New file name set; will only be used when a new error file is started" << endl;
        }

        if( aNewName == NULL )
        {
            fUseAutomaticErrorFileName = kTRUE;
            return;
        }

        fErrorFileName.assign( aNewName );
        fUseAutomaticErrorFileName = kFALSE;

        return;

    }

} // end Kassiopeia namespace
