/*!
 * @file KSBuilderPrototype.h
 * @brief contains class definition for KSBuilderPrototype
 *
 * @details
 * <b>Revision History:</b>
 * @verbatim
 * Date         Name          Brief description
 * -----------------------------------------------
 * 13 Jul 2010  D. Furse      first version
 * @endverbatim
 */

#ifndef KSBUILDERPROTOTYPE_H_
#define KSBUILDERPROTOTYPE_H_

#include "KSBuilderSystem.h"

/*!
 * @class Kassiopeia::KSPseudoXMLBuilderPrototype
 * @author Dan Furse
 *
 * @brief this class is a templated prototype for all builders
 *
 * @details
 * <b>Detailed Description:</b><br>
 *
 */
namespace Kassiopeia
{

    template< class XManagerType, class XBuilderType >
    class KSBuilderPrototype :
        public KSBuilderSystem< XManagerType >
    {
        public:
            KSBuilderPrototype();
            virtual ~KSBuilderPrototype();

            Bool_t ProcessSystemAttributes( const KSPseudoParameterToken* token );
            Bool_t ProcessSystemAttributes( const KSTokenAttribute* token );

            virtual const string& GetSystemName() const;
            static const string& GetStaticSystemName();
        
            virtual const string& GetTypeName() const;
            static const string& GetStaticTypeName();
        
            virtual const string& GetInstanceName() const;
        
            // temporary
            virtual Bool_t GetAddObjectToToolboxFlag() const;
            virtual void SetAddObjectToToolboxFlag(Bool_t aFlag);

        protected:
            static const string fSystemName;
            static const string fTypeName;
            string fInstanceName;
        
            // temporary
            Bool_t fAddObjectToToolboxFlag;

    };

    template< class XManagerType, class XBuilderType >
    KSBuilderPrototype< XManagerType, XBuilderType >::KSBuilderPrototype() :
    fInstanceName("NONE"),
    fAddObjectToToolboxFlag(kFALSE)
    {
    }

    template< class XManagerType, class XBuilderType >
    KSBuilderPrototype< XManagerType, XBuilderType >::~KSBuilderPrototype()
    {
    }

    template< class XManagerType, class XBuilderType >
    Bool_t KSBuilderPrototype< XManagerType, XBuilderType >::ProcessSystemAttributes( const KSPseudoParameterToken* token )
    {
        if (token->GetName() == string("Name"))
        {
            fInstanceName = token->GetValue();
            fAddObjectToToolboxFlag = kTRUE;
            return kTRUE;
        }
        return kFALSE;
    }
    
    template< class XManagerType, class XBuilderType >
    Bool_t KSBuilderPrototype< XManagerType, XBuilderType >::ProcessSystemAttributes( const KSTokenAttribute* token )
    {
        if (token->GetAttributeName() == string("Name"))
        {
            fInstanceName = token->GetAttributeValue();
            fAddObjectToToolboxFlag = kTRUE;
            return kTRUE;
        }
        return kFALSE;
    }
    
    template< class XManagerType, class XBuilderType >
    const string& KSBuilderPrototype< XManagerType, XBuilderType >::GetSystemName() const
    {
        return fSystemName;
    }
    
    template< class XManagerType, class XBuilderType >
    const string& KSBuilderPrototype< XManagerType, XBuilderType >::GetStaticSystemName()
    {
        return fSystemName;
    }
    
    template< class XManagerType, class XBuilderType >
    const string& KSBuilderPrototype< XManagerType, XBuilderType >::GetTypeName() const
    {
        return fTypeName;
    }

    template< class XManagerType, class XBuilderType >
    const string& KSBuilderPrototype< XManagerType, XBuilderType >::GetStaticTypeName()
    {
        return fTypeName;
    }

    template< class XManagerType, class XBuilderType >
    const string& KSBuilderPrototype< XManagerType, XBuilderType >::GetInstanceName() const
    {
        return fInstanceName;
    }
    
    template< class XManagerType, class XBuilderType >
    Bool_t KSBuilderPrototype< XManagerType, XBuilderType >::GetAddObjectToToolboxFlag() const
    {
        return fAddObjectToToolboxFlag;
    }
    
    template< class XManagerType, class XBuilderType >
    void KSBuilderPrototype< XManagerType, XBuilderType >::SetAddObjectToToolboxFlag(Bool_t aFlag)
    {
        fAddObjectToToolboxFlag = aFlag;
        return;
    }
 
    /*
 template< class XManagerTypeclass XBuilderType >
 class KSPseudoXMLBuilderPrototype< XManagerType, KSPseudoXMLToken, XBuilderType > :
 public KSBuilderBase
 {
 public:
 KSPseudoXMLBuilderPrototype();
 virtual ~KSPseudoXMLBuilderPrototype();
=======
    
    template< class XManagerType, class XBuilderType >
    void KSBuilderPrototype< XManagerType, XBuilderType >::SetDirectSettingMap(DirectSettingMap* aMap)
    {
        fDirectSettingMap = aMap;
        return;
    }
    
    template< class XManagerType, class XBuilderType >
    std::map< string, string >* KSBuilderPrototype< XManagerType, XBuilderType >::GetDirectSettingMap() const
    {
        return fDirectSettingMap;
    }
    
    template< class XManagerType, class XBuilderType >
    void KSBuilderPrototype< XManagerType, XBuilderType >::CatchProcessBuilderError( KSBuilderBase* const oldbuild, KSException::Severity severity ) const{
        
        this->E = severity;
        this->E < fName + "Builder::ProcessBuilder";
        this->E << "unknown subnode <" << oldbuild->GetName()
        << "> in file <" << KSBuilderSystemPrototype<XManagerType>::fInitializer->GetCurrentFileName()
        << "> at line <" << KSBuilderSystemPrototype<XManagerType>::fInitializer->GetCurrentLineNumber()
        << ">, column <" << KSBuilderSystemPrototype<XManagerType>::fInitializer->GetCurrentColumnNumber()
        << ">!";
        KSBuilderBase::CatchException(this->E);
    }
    
    template< class XManagerType, class XBuilderType >
    void KSBuilderPrototype< XManagerType, XBuilderType >::CatchProcessBeginTokenError( const KSBeginToken* const begin, KSException::Severity severity) const{
        
        this->E = severity;
        this->E < fName + "Builder::ProcessBeginToken";
        this->E << "description ending with <" << begin->GetType()
        << "> in file <" << KSBuilderSystemPrototype<XManagerType>::fInitializer->GetCurrentFileName()
        << "> at line <" << KSBuilderSystemPrototype<XManagerType>::fInitializer->GetCurrentLineNumber()
        << ">, column <" << KSBuilderSystemPrototype<XManagerType>::fInitializer->GetCurrentColumnNumber()
        << ">!";
        KSBuilderBase::CatchException(this->E);
    }
>>>>>>> .merge-right.r10222

<<<<<<< .working
 const string& GetTypeName() const;
 static const string& GetStaticTypeName();

 protected:
 virtual void ProcessToken( const KSToken* token );
 Bool_t ProcessBuilder( KSBuilderBase* const oldbuild );

 virtual void ProcessBegin( const KSPseudoBeginToken* begin ) = 0;
 virtual void ProcessParameter( const KSPseudoParameterToken* const param ) = 0;
 virtual void ProcessEnd( const KSPseudoEndToken* end ) = 0;
 virtual void ProcessKeyword( const KSPseudoKeywordToken* keyword ) = 0;
 virtual void ProcessError( const KSPseudoErrorToken* error ) = 0;

 private:
 static const string fSystemName;
 };

 template< class XManagerType, class XBuilderType >
 KSPseudoXMLBuilderPrototype< XManagerType, KSPseudoXMLToken, XBuilderType >::KSPseudoXMLBuilderPrototype() :
 KSBuilderSystemPrototype< XManagerType > ()
 {
 }

 template< class XManagerType, class XBuilderType >
 KSPseudoXMLBuilderPrototype< XManagerType, XBuilderType >::~KSPseudoXMLBuilderPrototype()
 {
 }

 template< class XManagerType, class XBuilderType >
 const string& KSPseudoXMLBuilderPrototype< XManagerType, XBuilderType >::GetName() const
 {
 return fName;
 }
 template< class XManagerType, class XBuilderType >
 const string& KSPseudoXMLBuilderPrototype< XManagerType, XBuilderType >::GetStaticName()
 {
 return fName;
 }

 template< class XManagerType, class XBuilderType >
 const string& KSPseudoXMLBuilderPrototype< XManagerType, XBuilderType >::GetSystemName() const
 {
 return fSystemName;
 }
 template< class XManagerType, class XBuilderType >
 const string& KSPseudoXMLBuilderPrototype< XManagerType, XBuilderType >::GetStaticSystemName()
 {
 return fSystemName;
 }

 template< class XManagerType, class XBuilderType >
 const string& KSPseudoXMLBuilderPrototype< XManagerType, XBuilderType >::GetInstanceName() const
 {
 return fInstanceName;
 }

 template< class XManagerType, class XBuilderType >
 string* KSPseudoXMLBuilderPrototype< XManagerType, XBuilderType >::GetCompleteAddress() const
 {
 string* tCompleteAddress = new string( "" );
 BuildRecursiveAddress( tCompleteAddress );
 return tCompleteAddress;
 }

 template< class XManagerType, class XBuilderType >
 void KSPseudoXMLBuilderPrototype< XManagerType, XBuilderType >::BuildRecursiveAddress( string* aCompleteAddress ) const
 {
 if( *aCompleteAddress != string( "" ) ) *aCompleteAddress = fAddressDelimeter + *aCompleteAddress;
 if( fInstanceName == fGenericInstanceName )
 {
 *aCompleteAddress = fName + *aCompleteAddress;
 }
 else
 {
 *aCompleteAddress = fName + fLeftInstanceNameIndicator + fInstanceName + fRightInstanceNameIndicator + *aCompleteAddress;
 }
 if( !this->BuilderIsAlsoInitializer() ) this->GetParent()->BuildRecursiveAddress( aCompleteAddress );
 return;
 }

 template< class XManagerType, class XBuilderType >
 void KSPseudoXMLBuilderPrototype< XManagerType, XBuilderType >::InitialProcessParameterToken( KSParameterToken* const param )
 {
 this->E < "KSPseudoXMLBuilderPrototype(" + GetName() + ")::InitialProcessParameterToken";

 if( param->GetName() == string( "Name" ) )
 {
 if( this->GetNParameterTokensDropped() != 1 )
 {
 this->E = KSException::eFatalError;
 this->E << "You must set the Name first in a named configuration element. You are attempting to set it after the first parameter.\n";
 KSBuilderBase::CatchException( this->E );
 return;
 }
 if( !SetInstanceName( param ) )
 {
 this->E = KSException::eFatalError;
 this->E << "This error shouldn't happen";
 KSBuilderBase::CatchException( this->E );
 return;
 }
 return;
 }

 // If this instance isn't named, set the default name
 if( this->GetNParameterTokensDropped() == 1 )
 {
 this->SetDefaultInstanceName();
 }

 this->ProcessParameterToken( param );
 return;
 }

 template< class XManagerType, class XBuilderType >
 void KSPseudoXMLBuilderPrototype< XManagerType, XBuilderType >::CatchProcessBuilderError( KSBuilderBase* const oldbuild ) const
 {

 this->E = KSException::eError;
 this->E < fName + "Builder::ProcessBuilder";
 this->E << "unknown subnode <" << oldbuild->GetName() << "> in file <" << KSBuilderSystemPrototype< XManagerType >::fInitializer->GetCurrentFileName() << "> at line <" << KSBuilderSystemPrototype< XManagerType >::fInitializer->GetCurrentLineNumber() << ">, column <" << KSBuilderSystemPrototype< XManagerType >::fInitializer->GetCurrentColumnNumber() << ">!";
 KSBuilderBase::CatchException( this->E );
 }

 template< class XManagerType, class XBuilderType >
 void KSPseudoXMLBuilderPrototype< XManagerType, XBuilderType >::CatchProcessBeginTokenError( const KSPseudoBeginToken* const begin ) const
 {

 this->E = KSException::eError;
 this->E < fName + "Builder::ProcessBeginToken";
 this->E << "description ending with <" << begin->GetType() << "> in file <" << KSBuilderSystemPrototype< XManagerType >::fInitializer->GetCurrentFileName() << "> at line <" << KSBuilderSystemPrototype< XManagerType >::fInitializer->GetCurrentLineNumber() << ">, column <" << KSBuilderSystemPrototype< XManagerType >::fInitializer->GetCurrentColumnNumber() << ">!";
 KSBuilderBase::CatchException( this->E );
 }

 template< class XManagerType, class XBuilderType >
 void KSPseudoXMLBuilderPrototype< XManagerType, XBuilderType >::CatchProcessParameterTokenError( const KSParameterToken* const param ) const
 {

 this->E = KSException::eError;
 this->E < fName + "Builder::ProcessParameterToken";
 this->E << "unknown parameter <" << param->GetName() << "> in file <" << KSBuilderSystemPrototype< XManagerType >::fInitializer->GetCurrentFileName() << "> at line <" << KSBuilderSystemPrototype< XManagerType >::fInitializer->GetCurrentLineNumber() << ">, column <" << KSBuilderSystemPrototype< XManagerType >::fInitializer->GetCurrentColumnNumber() << ">!";
 KSBuilderBase::CatchException( this->E );
 }

 template< class XManagerType, class XBuilderType >
 void KSPseudoXMLBuilderPrototype< XManagerType, XBuilderType >::CatchProcessEndTokenError( const KSEndToken* const end ) const
 {

 this->E = KSException::eError;
 this->E < fName + "Builder::ProcessEndToken";
 this->E << "description ending with <" << end->GetTypeName() << "> in file <" << KSBuilderSystemPrototype< XManagerType >::fInitializer->GetCurrentFileName() << "> at line <" << KSBuilderSystemPrototype< XManagerType >::fInitializer->GetCurrentLineNumber() << ">, column <" << KSBuilderSystemPrototype< XManagerType >::fInitializer->GetCurrentColumnNumber() << ">!";
 KSBuilderBase::CatchException( this->E );
 }

 template< class XManagerType, class XBuilderType >
 void KSPseudoXMLBuilderPrototype< XManagerType, XBuilderType >::CatchCustomException( const string& aMessage, KSException::Severity severity ) const
 {

 this->E = severity;
 this->E < fName + "Builder";
 this->E << aMessage << " in file <" << KSBuilderSystemPrototype< XManagerType >::fInitializer->GetCurrentFileName() << "> at line <" << KSBuilderSystemPrototype< XManagerType >::fInitializer->GetCurrentLineNumber() << ">, column <" << KSBuilderSystemPrototype< XManagerType >::fInitializer->GetCurrentColumnNumber() << ">!";
 KSBuilderBase::CatchException( this->E );
 }

 template< class XManagerType, class XBuilderType >
 void KSPseudoXMLBuilderPrototype< XManagerType, XBuilderType >::ProcessBuilder( KSBuilderBase* const oldbuild )
 {
 CatchProcessBuilderError( oldbuild );
 }

 template< class XManagerType, class XBuilderType >
 void KSPseudoXMLBuilderPrototype< XManagerType, XBuilderType >::ProcessParameterToken( const KSParameterToken* const param )
 {
 CatchProcessParameterTokenError( param );
 }

 template< class XManagerType, class XBuilderType >
 void KSPseudoXMLBuilderPrototype< XManagerType, XBuilderType >::ProcessEndToken( const KSEndToken* const end )
 {
 CatchProcessEndTokenError( end );
 }

 template< class XManagerType, class XBuilderType >
 Bool_t KSPseudoXMLBuilderPrototype< XManagerType, XBuilderType >::SetInstanceName( const KSParameterToken* const param )
 {
 fInstanceName = param->GetValue();
 return kTRUE;
 }

 template< class XManagerType, class XBuilderType >
 void KSPseudoXMLBuilderPrototype< XManagerType, XBuilderType >::SetDefaultInstanceName()
 {
 fInstanceName = string( "Generic" );
 return;
 }

 template< class XManagerType, class XBuilderType >
 Bool_t KSPseudoXMLBuilderPrototype< XManagerType, XBuilderType >::GetAddObjectToToolboxFlag() const
 {
 return kFALSE;
 }
 */

} // end namespace Kassiopeia

#endif // end ifndef KSPseudoXMLBuilderPrototype
