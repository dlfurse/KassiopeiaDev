#ifndef KSTOOLBOXBUILDER_H_
#define KSTOOLBOXBUILDER_H_

#include "KSBuilder.h"

namespace Kassiopeia
{

    template< class XToolboxType >
    class KSToolboxBuilder :
        public KSBuilder
    {
        public:
            KSToolboxBuilder();
            virtual ~KSToolboxBuilder();

        public:
            static void SetToolbox( XToolboxType* aToolbox );

        protected:
            static XToolboxType* fToolbox;
    };

    template< class XToolboxType >
    KSToolboxBuilder< XToolboxType >::KSToolboxBuilder() :
        KSBuilder()
    {
    }
    template< class XToolboxType >
    KSToolboxBuilder< XToolboxType >::~KSToolboxBuilder()
    {
    }

    template< class XToolboxType >
    void KSToolboxBuilder< XToolboxType >::SetToolbox( XToolboxType* aToolbox )
    {
        fToolbox = aToolbox;
        return;
    }
    template< class XToolboxType >
    XToolboxType* KSToolboxBuilder< XToolboxType >::fToolbox = NULL;

}

#endif
