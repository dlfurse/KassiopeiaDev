#ifndef KSSINGLE_H_
#define KSSINGLE_H_

namespace Kassiopeia
{

    template< class XType >
    class KSSingle
    {
        public:
            KSSingle();
            ~KSSingle();

            static XType* fAddress;
    };

    template< class XType >
    XType* KSSingle< XType >::fAddress = NULL;

    template< class XType >
    KSSingle< XType >::KSSingle()
    {
        if( fAddress == NULL )
        {
            fAddress = new XType();
        }
    }
    template< class XType >
    KSSingle< XType >::~KSSingle()
    {
    }

}

#endif
