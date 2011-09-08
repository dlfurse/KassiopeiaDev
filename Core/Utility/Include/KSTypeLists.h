#ifndef KSTYPELIST_H_
#define KSTYPELIST_H_

#include "KSTypeNull.h"

namespace Kassiopeia
{

    //KSTypeList type

    //basic definition
    template< class XThisType, class XNext >
    class KSTypeList
    {
        public:
            typedef XNext Next;
            typedef XThisType ThisType;
            typedef typename XNext::ThisType NextType;
    };

    //terminal definiton (contained type is KSTypeNull)
    template< class XThisType >
    class KSTypeList< XThisType, KSTypeNull >
    {
        public:
            typedef KSTypeNull Next;
            typedef XThisType ThisType;
            typedef KSTypeNull NextType;
    };


    //KSTypeList construction macros
#define KSTYPELIST1(one) ::Kassiopeia::KSTypeList< one, KSTypeNull >
#define KSTYPELIST2(one,two) ::Kassiopeia::KSTypeList< one, KSTYPELIST1(two) >
#define KSTYPELIST3(one,two,three) ::Kassiopeia::KSTypeList< one, KSTYPELIST2(two,three) >
#define KSTYPELIST4(one,two,three,four) ::Kassiopeia::KSTypeList< one, KSTYPELIST3(two,three,four) >
#define KSTYPELIST5(one,two,three,four,five) ::Kassiopeia::KSTypeList< one, KSTYPELIST4(two,three,four,five) >
#define KSTYPELIST6(one,two,three,four,five,six) ::Kassiopeia::KSTypeList< one, KSTYPELIST5(two,three,four,five,six) >
#define KSTYPELIST7(one,two,three,four,five,six,seven) ::Kassiopeia::KSTypeList< one, KSTYPELIST6(two,three,four,five,six,seven) >
#define KSTYPELIST8(one,two,three,four,five,six,seven,eight) ::Kassiopeia::KSTypeList< one, KSTYPELIST7(two,three,four,five,six,seven,eight) >
#define KSTYPELIST9(one,two,three,four,five,six,seven,eight,nine) ::Kassiopeia::KSTypeList< one, KSTYPELIST8(two,three,four,five,six,seven,eight,nine) >
#define KSTYPELIST10(one,two,three,four,five,six,seven,eight,nine,ten) ::Kassiopeia::KSTypeList< one, KSTYPELIST9(two,three,four,five,six,seven,eight,nine,ten) >

}

#endif
