#ifndef KSSINGLETON_H_
#define KSSINGLETON_H_

#include <cstddef>

namespace Kassiopeia
{

    template< class XType >
    class KSSingleton
    {
        public:
            static XType* GetInstance();

        private:
            static XType* fInstance;

        protected:
            KSSingleton();
            virtual ~KSSingleton();
    };

    template< class XType >
    XType* KSSingleton< XType >::fInstance = NULL;

    template< class XType >
    XType* KSSingleton< XType >::GetInstance()
    {
        if( fInstance == NULL )
        {
            fInstance = new XType();
        }
        return fInstance;
    }

    template< class XType >
    KSSingleton< XType >::KSSingleton()
    {
    }
    template< class XType >
    KSSingleton< XType >::~KSSingleton()
    {
    }

}

#endif
