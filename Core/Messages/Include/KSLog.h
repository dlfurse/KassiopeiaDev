// $Id$

#ifndef KSLOG_H
#define KSLOG_H

/**
 @file
 @brief contains KSLog
 @details
 <b>Revision History:</b>
 \verbatim
 Date         Name          Brief description
 -----------------------------------------------
 25/03/2010   N. Oblath     First version
 07/04/2010   N. Oblath     Added error file

 \endverbatim

 */

/*!
 @class Kassiopeia::KSLog
 @author N. Oblath

 @brief Singleton logging class for Kassiopeia

 @details
 <b>Detailed Description:</b><br>
 This class is responsible for outputing text to the log file and error file

 */

#include "Rtypes.h"

#include <fstream>
#include <iostream>
using std::ofstream;

#include <string>
using std::string;

namespace Kassiopeia
{

    class KSLog
    {

        public:
            //! Returns the singleton instance of KSLog
            static KSLog* GetInstance();

            //! Starts a new log file
            static void StartLog();
            //! Closes the log file
            static void EndLog();

            //! Starts a new error file
            static void StartError();
            //! Closes the error file
            static void EndError();

            inline ofstream& LogStream();
            inline ofstream& ErrorStream();

            const string& GetLogFileName() const;
            const string& GetErrorFileName() const;

            //! Set a new log file name (only applies when a new log is started)
            //! Entering no parameters will set the use of an automatic timestamped file name
            void SetLogFileName( const Char_t* = NULL );
            //! Set a new error file name (only applies when a new error log is started)
            //! Entering no parameters will set the use of an automatic timestamped file name
            void SetErrorFileName( const Char_t* = NULL );

            friend class KLMessageManager;

        private:
            //! Private default constructor
            KSLog();
            //! Prevent copy-construction
            KSLog( const KSLog& );
            //! Prevent assignment
            KSLog& operator=( const KSLog& );
            //! Private destructor
            ~KSLog();

            //! Private static safe (closes the log) deletion method
            static void DeleteInstance();

            //! Private method for making a new instance
            static void CreateNewInstance();

            static KSLog* fKSLogInstance; //! Pointer to the KSLog instance

            static ofstream fLogFile; //! File stream for the log
            static Bool_t fLogFileIsOpen; //! Flag to indicate state of the log
            static string fLogFileName; //! File name used for new log files
            static Bool_t fUseAutomaticLogFileName; //! Flat to indicate if a timestamped file name should be used

            static ofstream fErrorFile; //! File stream for the error log
            static Bool_t fErrorFileIsOpen; //! Flag to indicate state of the error log
            static string fErrorFileName; //! File name used for new error files
            static Bool_t fUseAutomaticErrorFileName; //! Flag to indicate if a timestamped file name should be used

    };
    inline ofstream& KSLog::LogStream()
    {
        if( !fLogFile.is_open() ) std::cerr << "WARNING (KSLog::LogStream): No open log stream" << std::endl;
        return fLogFile;
    }
    inline ofstream& KSLog::ErrorStream()
    {
        if( !fErrorFile.is_open() ) std::cerr << "WARNING (KSLog::ErrorStream): No open error stream" << std::endl;
        return fErrorFile;

    }

} // end Kassiopeia namespace


#endif // KSLOG_H
