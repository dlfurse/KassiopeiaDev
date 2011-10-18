#ifndef KSTOOLBOXMODULEBUILDER_H_
#define KSTOOLBOXMODULEBUILDER_H_

#include "KSToolboxBuilder.h"

namespace Kassiopeia
{

    template< class XToolboxType, class XModuleType >
    class KSToolboxModuleBuilder :
        public KSToolboxBuilder< XToolboxType >
    {
        public:
            template< class XSubModuleType >
            friend class Element;

            template< class XSubModuleType >
            class Element
            {
                public:
                    Element( const string& aKey );
                    ~Element();

                    static KSBuilder* Create();
            };

        public:
            KSToolboxModuleBuilder();
            virtual ~KSToolboxModuleBuilder();

        public:
            static void SetElement( const string& anElement, KSBuilder* (*aConstructor)() );

        private:
            static KSBuilder::FactoryMap fStaticMap;
    };

    template< class XToolboxType, class XModuleType >
    KSToolboxModuleBuilder< XToolboxType, XModuleType >::KSToolboxModuleBuilder() :
        KSToolboxBuilder< XToolboxType >()
    {
        this->fMap = &fStaticMap;
    }
    template< class XToolboxType, class XModuleType >
    KSToolboxModuleBuilder< XToolboxType, XModuleType >::~KSToolboxModuleBuilder()
    {
        this->fMap = NULL;
    }

    template< class XToolboxType, class XModuleType >
    void KSToolboxModuleBuilder< XToolboxType, XModuleType >::SetElement( const string& anElement, KSBuilder* (*aConstructor)() )
    {
        KSBuilder::FactoryIt It = fStaticMap.find( anElement );
        if( It == fStaticMap.end() )
        {
            fStaticMap.insert( KSBuilder::FactoryEntry( anElement, aConstructor ) );
            return;
        }
        It->second = aConstructor;
        return;
    }
    template< class XToolboxType, class XModuleType >
    KSBuilder::FactoryMap KSToolboxModuleBuilder< XToolboxType, XModuleType >::fStaticMap = KSBuilder::FactoryMap();

    template< class XToolboxType, class XModuleType >
    template< class XSubModuleType >
    KSToolboxModuleBuilder< XToolboxType, XModuleType >::Element< XSubModuleType >::Element( const string& aKey )
    {
        KSToolboxModuleBuilder< XToolboxType, XModuleType >::SetElement( aKey, &Create );
    }
    template< class XToolboxType, class XModuleType >
    template< class XSubModuleType >
    KSToolboxModuleBuilder< XToolboxType, XModuleType >::Element< XSubModuleType >::~Element()
    {
    }
    template< class XToolboxType, class XModuleType >
    template< class XSubModuleType >
    KSBuilder* KSToolboxModuleBuilder< XToolboxType, XModuleType >::Element< XSubModuleType >::Create()
    {
        return new XSubModuleType();
    }
}

#endif
