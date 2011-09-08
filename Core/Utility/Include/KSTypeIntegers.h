#ifndef KSINTEGERTYPE_H_
#define KSINTEGERTYPE_H_

namespace Kassiopeia
{

    template< int XValue >
    class KSTypeInteger
    {
        public:
            enum { Value = XValue };
    };


    template< class XLeft, class XRight >
    class KSPlus;

    template< int XLeftValue, int XRightValue >
    class KSPlus< KSTypeInteger< XLeftValue >, KSTypeInteger< XRightValue > >
    {
        public:
            typedef KSTypeInteger< XLeftValue + XRightValue > Type;
    };


    template< class XLeft, class XRight >
    class KSMinus;

    template< int XLeftValue, int XRightValue >
    class KSMinus< KSTypeInteger< XLeftValue >, KSTypeInteger< XRightValue > >
    {
        public:
            typedef KSTypeInteger< XLeftValue - XRightValue > Type;
    };


}


#endif
