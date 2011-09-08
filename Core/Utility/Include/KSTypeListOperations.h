#ifndef KSTYPELISTOPERATIONS_H_
#define KSTYPELISTOPERATIONS_H_

#include "KSTypeLists.h"

namespace Kassiopeia
{

    //KSLength function for typelists

    //degenerate definition
    template< class XType >
    class KSLength;

    //basic definition
    template< class XTypeAtIndex, class XNext >
    class KSLength< KSTypeList< XTypeAtIndex, XNext > >
    {
        public:
            enum { Value = KSLength< XNext >::Value + 1 };
    };

    //terminal definition
    template< class XTypeAtIndex >
    class KSLength< KSTypeList< XTypeAtIndex, KSTypeNull > >
    {
        public:
            enum { Value = 1 };
    };


    //AtFront function for typelists

    //degenerate definition
    template< class XType >
    class KSAtFront;

    //basic definition
    template< class XTypeAtIndex, class XNext >
    class KSAtFront< KSTypeList< XTypeAtIndex, XNext > >
    {
        public:
            typedef XTypeAtIndex Type;
    };


    //KSAtBack function for typelists

    //degenerate definition
    template< class XType >
    class KSAtBack;

    //basic definition
    template< class XTypeAtIndex, class XNext >
    class KSAtBack< KSTypeList< XTypeAtIndex, XNext > >
    {
        public:
            typedef typename KSAtBack< XNext >::Type Type;
    };

    //terminal definiton (end of typelist reached)
    template< class XTypeAtIndex >
    class KSAtBack< KSTypeList< XTypeAtIndex, KSTypeNull > >
    {
        public:
            typedef XTypeAtIndex Type;
    };


    //KSAt function for typelists

    //degenerate definition
    template< class XType, int XIndex >
    class KSAt;

    //basic definition
    template< class XTypeAtIndex, class XNext, int XIndex >
    class KSAt< KSTypeList< XTypeAtIndex, XNext >, XIndex >
    {
        public:
            typedef typename KSAt< XNext, XIndex - 1 >::Type Type;
    };

    //terminal definition (index is reached)
    template< class XTypeAtIndex, class XNext >
    class KSAt< KSTypeList< XTypeAtIndex, XNext >, 0 >
    {
        public:
            typedef XTypeAtIndex Type;
    };

    //terminal definition (end of typelist reached)
    template< int XIndex >
    class KSAt< KSTypeNull, XIndex >
    {
        public:
            typedef KSTypeNull Type;
    };


    //KSPushBack function for typelists

    //degenerate definition
    template< class XInserted, class XTarget >
    class KSPushBack;

    //basic definition (inserted is an undifferentiated type)
    template< class XInserted, class XTypeAtIndex, class XNext >
    class KSPushBack< XInserted, KSTypeList< XTypeAtIndex, XNext > >
    {
        public:
            typedef KSTypeList< XTypeAtIndex, typename KSPushBack< XInserted, XNext >::Type > Type;
    };

    //basic definition (inserted is a typelist)
    template< class XFirstInserted, class XNextInserted, class XTypeAtIndex, class XNext >
    class KSPushBack< KSTypeList< XFirstInserted, XNextInserted >, KSTypeList< XTypeAtIndex, XNext > >
    {
        public:
            typedef KSTypeList< XTypeAtIndex, typename KSPushBack< KSTypeList< XFirstInserted, XNextInserted >, XNext >::Type > Type;
    };

    //terminal definition (inserted is an undifferentiated type, end of typelist reached)
    template< class XInserted, class XTypeAtIndex >
    class KSPushBack< XInserted, KSTypeList< XTypeAtIndex, KSTypeNull > >
    {
        public:
            typedef KSTypeList< XTypeAtIndex, KSTypeList< XInserted, KSTypeNull > > Type;
    };

    //terminal definition (inserted is a typelist, end of typelist reached)
    template< class XFirstInserted, class XNextInserted, class XTypeAtIndex >
    class KSPushBack< KSTypeList< XFirstInserted, XNextInserted >, KSTypeList< XTypeAtIndex, KSTypeNull > >
    {
        public:
            typedef KSTypeList< XTypeAtIndex, KSTypeList< XFirstInserted, XNextInserted > > Type;
    };


    //PushFront function for typelists

    //degenerate definition
    template< class XInserted, class XTarget >
    class KSPushFront;

    //basic definition (inserted is an undifferentiated type)
    template< class XInserted, class XTypeAtIndex, class XNext >
    class KSPushFront< XInserted, KSTypeList< XTypeAtIndex, XNext > >
    {
        public:
            typedef KSTypeList< XInserted, KSTypeList< XTypeAtIndex, XNext > > Type;
    };

    //basic definition (inserted is a typelist)
    template< class XFirstInserted, class XNextInserted, class XTypeAtIndex, class XNext >
    class KSPushFront< KSTypeList< XFirstInserted, XNextInserted >, KSTypeList< XTypeAtIndex, XNext > >
    {
        public:
            typedef KSPushBack< KSTypeList< XTypeAtIndex, XNext >, KSTypeList< XFirstInserted, XNextInserted > > Type;
    };


    //KSInsert function for typelists

    //degenerate definition
    template< class XInserted, class XTarget, int XIndex >
    class KSInsert;

    //basic definition (inserted is an undifferentiated type, target is a typelist)
    template< class XInserted, class XTypeAtIndex, class XNext, int XIndex >
    class KSInsert< XInserted, KSTypeList< XTypeAtIndex, XNext >, XIndex >
    {
        public:
            typedef KSTypeList< XTypeAtIndex, typename KSInsert< XInserted, XNext, XIndex - 1 >::Type > Type;
    };

    //basic definition (inserted is a typelist, target is a typelist)
    template< class XFirstInserted, class XNextInserted, class XTypeAtIndex, class XNext, int XIndex >
    class KSInsert< KSTypeList< XFirstInserted, XNextInserted >, KSTypeList< XTypeAtIndex, XNext >, XIndex >
    {
        public:
            typedef KSTypeList< XTypeAtIndex, typename KSInsert< KSTypeList< XFirstInserted, XNextInserted >, XNext, XIndex - 1 >::Type > Type;
    };

    //terminal definition (inserted is an undifferentiated type, target is a typelist, index is reached)
    template< class XInserted, class XTypeAtIndex, class XNext >
    class KSInsert< XInserted, KSTypeList< XTypeAtIndex, XNext >, 0 >
    {
        public:
            typedef KSTypeList< XInserted, KSTypeList< XTypeAtIndex, XNext > > Type;
    };

    //terminal definition (inserted is a typelist, target is a typelist, index is reached)
    template< class XFirstInserted, class XNextInserted, class XTypeAtIndex, class XNext >
    class KSInsert< KSTypeList< XFirstInserted, XNextInserted >, KSTypeList< XTypeAtIndex, XNext >, 0 >
    {
        public:
            typedef typename KSPushBack< KSTypeList< XTypeAtIndex, XNext >, KSTypeList< XFirstInserted, XNextInserted > >::Type Type;
    };
}

#endif
