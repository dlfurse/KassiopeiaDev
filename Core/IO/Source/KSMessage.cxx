/*
 * KSMessage.cxx
 *
 * created on: Jul 20, 2011
 * author: dlfurse
 */

#include "KSMessage.h"

#include "KSIOToolbox.h"
#include "KSTextFile.h"

#include <iostream>
using std::cout;
using std::endl;

namespace Kassiopeia
{

    const KSMessageSeverity eError = 0;
    const KSMessageSeverity eWarning = 1;
    const KSMessageSeverity eNormal = 2;
    const KSMessageSeverity eDebug = 3;
    const KSMessageNewline ret = KSMessageNewline();
    const KSMessageEnd eom = KSMessageEnd();

    KSMessage::KSMessage( const string& aKey ) :
        fKey( aKey ),
        fSystemDescription( "GENERIC" ),
        fSystemPrefix( "" ),
        fSystemSuffix( "" ),

        fTopSeparator( "**********" ),
        fBottomSeparator( "**********" ),

        fErrorColorPrefix( "\33[31;1m" ),
        fErrorColorSuffix( "\33[0m" ),
        fErrorDescription( "ERROR" ),

        fWarningColorPrefix( "\33[33;1m" ),
        fWarningColorSuffix( "\33[0m" ),
        fWarningDescription( "WARNING" ),

        fNormalColorPrefix( "\33[32;1m" ),
        fNormalColorSuffix( "\33[0m" ),
        fNormalDescription( "NORMAL" ),

        fDebugColorPrefix( "\33[36;1m" ),
        fDebugColorSuffix( "\33[0m" ),
        fDebugDescription( "DEBUG" ),

        fDefaultColorPrefix( "\33[37;1m" ),
        fDefaultColorSuffix( "\33[0m" ),
        fDefaultDescription( "UNKNOWN" ),

        fSeverity( eNormal ),
        fPrefix( fNormalColorPrefix + fSystemPrefix ),
        fSuffix( fSystemSuffix + fNormalColorSuffix ),

        fDescriptionBuffer(),
        fDescription( "" ),

        fOriginLine(),
        fOriginLines(),

        fMessageLine(),
        fMessageLines(),

        fTerminalVerbosity( eNormal ),
        fLogVerbosity( eNormal ),
        fLogFile( NULL )
    {
        KSIOToolbox::GetInstance()->AddMessage( this );
    }
    KSMessage::~KSMessage()
    {
        KSIOToolbox::GetInstance()->RemoveMessage( this );
    }

    const string& KSMessage::GetKey()
    {
        return fKey;
    }

    KSMessage& KSMessage::operator+( const KSMessageSeverity& aSeverity )
    {
        fDescriptionBuffer.clear();
        fDescriptionBuffer.str( "" );

        switch( aSeverity )
        {

            case eError:
                fPrefix = fErrorColorPrefix + fSystemPrefix;
                fSuffix = fSystemSuffix + fErrorColorSuffix;
                fDescriptionBuffer << fSystemDescription << " " << fErrorDescription << " MESSAGE";
                break;

            case eWarning:
                fPrefix = fWarningColorPrefix + fSystemPrefix;
                fSuffix = fSystemSuffix + fWarningColorSuffix;
                fDescriptionBuffer << fSystemDescription << " " << fWarningDescription << " MESSAGE";
                break;

            case eNormal:
                fPrefix = fNormalColorPrefix + fSystemPrefix;
                fSuffix = fSystemSuffix + fNormalColorSuffix;
                fDescriptionBuffer << fSystemDescription << " " << fNormalDescription << " MESSAGE";
                break;

            case eDebug:
                fPrefix = fDebugColorPrefix + fSystemPrefix;
                fSuffix = fSystemSuffix + fDebugColorSuffix;
                fDescriptionBuffer << fSystemDescription << " " << fDebugDescription << " MESSAGE";
                break;

            default:
                fPrefix = fDefaultColorPrefix + fSystemPrefix;
                fSuffix = fSystemSuffix + fDefaultColorSuffix;
                fDescriptionBuffer << fSystemDescription << " " << fDefaultDescription << " MESSAGE";
                break;
        }

        fSeverity = aSeverity;
        fDescription = fDescriptionBuffer.str();

        return *this;
    }

    KSMessage& KSMessage::operator<( const KSMessageNewline& )
    {
        fOriginLines.push_back( fOriginLine.str() );

        fOriginLine.clear();
        fOriginLine.str( "" );

        return *this;
    }
    KSMessage& KSMessage::operator<( const KSMessageEnd& )
    {
        Print();
        return *this;
    }

    KSMessage& KSMessage::operator<<( const KSMessageNewline& )
    {
        fMessageLines.push_back( fMessageLine.str() );

        fMessageLine.clear();
        fMessageLine.str( "" );
        return *this;
    }
    KSMessage& KSMessage::operator<<( const KSMessageEnd& )
    {
        Print();
        return *this;
    }
    void KSMessage::Print()
    {
        fOriginLines.push_back( fOriginLine.str() );
        fMessageLines.push_back( fMessageLine.str() );

        if( fSeverity <= fTerminalVerbosity )
        {
            cout << fPrefix << fTopSeparator << fSuffix << '\n';
            cout << fPrefix << fDescription << fSuffix << '\n';

            cout << fPrefix << "ORIGIN:" << fSuffix << '\n';
            for( vector< string >::iterator It = fOriginLines.begin(); It != fOriginLines.end(); It++ )
            {
                cout << fPrefix << "  " << *It << fSuffix << '\n';
            }

            cout << fPrefix << "MESSAGE:" << fSuffix << '\n';
            for( vector< string >::iterator It = fMessageLines.begin(); It != fMessageLines.end(); It++ )
            {
                cout << fPrefix << "  " << *It << fSuffix << '\n';
            }

            cout << fPrefix << fBottomSeparator << fSuffix << '\n';
        }

        if( (fSeverity <= fLogVerbosity) && (fLogFile != NULL) && (fLogFile->IsOpen() == kTRUE) )
        {
            *(fLogFile->File()) << fSystemPrefix << fTopSeparator << fSystemSuffix << '\n';
            *(fLogFile->File()) << fSystemPrefix << fDescription << fSystemSuffix << '\n';

            *(fLogFile->File()) << fSystemPrefix << "ORIGIN:" << fSystemSuffix << '\n';
            for( vector< string >::iterator It = fOriginLines.begin(); It != fOriginLines.end(); It++ )
            {
                *(fLogFile->File()) << fSystemPrefix << "  " << *It << fSystemSuffix << '\n';
            }

            *(fLogFile->File()) << fSystemPrefix << "MESSAGE:" << fSystemSuffix << '\n';
            for( vector< string >::iterator It = fMessageLines.begin(); It != fMessageLines.end(); It++ )
            {
                *(fLogFile->File()) << fSystemPrefix << "  " << *It << fSystemSuffix << '\n';
            }
            *(fLogFile->File()) << fSystemPrefix << fBottomSeparator << fSystemSuffix << '\n';
        }

        while( !fOriginLines.empty() )
        {
            fOriginLines.pop_back();
        }
        fOriginLine.clear();
        fOriginLine.str( "" );

        while( !fMessageLines.empty() )
        {
            fMessageLines.pop_back();
        }
        fMessageLine.clear();
        fMessageLine.str( "" );

        return;
    }

    void KSMessage::SetTerminalVerbosity( KSMessageSeverity aVerbosity )
    {
        fTerminalVerbosity = aVerbosity;
        return;
    }
    void KSMessage::SetLogVerbosity( KSMessageSeverity aVerbosity )
    {
        fLogVerbosity = aVerbosity;
        return;
    }
    void KSMessage::SetLogFile( KSTextFile* aLogFile )
    {
        fLogFile = aLogFile;
        return;
    }

}
