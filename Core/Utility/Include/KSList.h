#ifndef KSLIST_H_
#define KSLIST_H_

#include "Rtypes.h"

namespace Kassiopeia
{

    template< class XType, size_t XMaxSize = 64 >
    class KSList
    {
        public:
            KSList();
            ~KSList();

            Int_t AddElement( XType* anElement );
            XType* ElementAt( size_t& anIndex );
            Int_t RemoveElement( XType* anElement );

            void ForEach( void(XType::*aMember)() );
            template< class XArgumentType >
            void ForEach( void(XType::*aMember)( XArgumentType ), XArgumentType anArgument );

            Bool_t ForEachUntilTrue( Bool_t(XType::*aMember)() );
            template< class XArgumentType >
            Bool_t ForEachUntilTrue( Bool_t(XType::*aMember)( XArgumentType ), XArgumentType anArgument );

            Bool_t ForEachUntilFalse( Bool_t(XType::*aMember)() );
            template< class XArgumentType >
            Bool_t ForEachUntilFalse( Bool_t(XType::*aMember)( XArgumentType ), XArgumentType anArgument );

            template< class XReturnType >
            XReturnType LargestOfAll( XReturnType(XType::*aMember)() );

            template< class XReturnType >
            XReturnType SmallestOfAll( XReturnType(XType::*aMember)() );

        private:
            XType* fElements[XMaxSize];
            size_t fCurrentElement;
            size_t fEndElement;
    };

    template< class XType, size_t XMaxSize >
    KSList< XType, XMaxSize >::KSList() :
        fCurrentElement( 0 ),
        fEndElement( 0 )
    {
        for( fCurrentElement = 0; fCurrentElement < XMaxSize; fCurrentElement++ )
        {
            fElements[fCurrentElement] = NULL;
        }
    }

    template< class XType, size_t XMaxSize >
    KSList< XType, XMaxSize >::~KSList()
    {
    }

    template< class XType, size_t XMaxSize >
    Int_t KSList< XType, XMaxSize >::AddElement( XType* anElement )
    {
        if( fEndElement == XMaxSize )
        {
            return -1;
        }
        fCurrentElement = fEndElement;
        fElements[fCurrentElement] = anElement;
        fEndElement++;
        return fCurrentElement;
    }
    template< class XType, size_t XMaxSize >
    XType* KSList< XType, XMaxSize >::ElementAt( size_t& anIndex )
    {
        fCurrentElement = anIndex;
        if( fCurrentElement >= fEndElement )
        {
            return NULL;
        }
        return fElements[fCurrentElement];
    }

    template< class XType, size_t XMaxSize >
    Int_t KSList< XType, XMaxSize >::RemoveElement( XType* anElement )
    {
        Int_t Index = -1;
        for( fCurrentElement = 0; fCurrentElement < fEndElement; fCurrentElement++ )
        {
            if( Index == -1 )
            {
                if( fElements[fCurrentElement] == anElement )
                {
                    fElements[fCurrentElement] = NULL;
                    Index = fCurrentElement;
                }
                continue;
            }
            fElements[fCurrentElement - 1] = fElements[fCurrentElement];
        }

        if( Index != -1 )
        {
            fEndElement--;
            fElements[fEndElement] = NULL;
        }
        return Index;
    }

    template< class XType, size_t XMaxSize >
    void KSList< XType, XMaxSize >::ForEach( void(XType::*aMember)() )
    {
        for( fCurrentElement = 0; fCurrentElement < fEndElement; fCurrentElement++ )
        {
            (fElements[fCurrentElement]->*aMember)();
        }
        return;
    }

    template< class XType, size_t XMaxSize >
    template< class XArgumentType >
    void KSList< XType, XMaxSize >::ForEach( void(XType::*aMember)( XArgumentType ), XArgumentType anArgument )
    {
        for( fCurrentElement = 0; fCurrentElement < fEndElement; fCurrentElement++ )
        {
            (fElements[fCurrentElement]->*aMember)( anArgument );
        }
        return;
    }

    template< class XType, size_t XMaxSize >
    Bool_t KSList< XType, XMaxSize >::ForEachUntilTrue( Bool_t(XType::*aMember)() )
    {
        for( fCurrentElement = 0; fCurrentElement < fEndElement; fCurrentElement++ )
        {
            if( (fElements[fCurrentElement]->*aMember)() == kTRUE )
            {
                return kTRUE;
            }
        }
        return kFALSE;
    }

    template< class XType, size_t XMaxSize >
    template< class XArgumentType >
    Bool_t KSList< XType, XMaxSize >::ForEachUntilTrue( Bool_t(XType::*aMember)( XArgumentType ), XArgumentType anArgument )
    {
        for( fCurrentElement = 0; fCurrentElement < fEndElement; fCurrentElement++ )
        {
            if( (fElements[fCurrentElement]->*aMember)( anArgument ) == kTRUE )
            {
                return kTRUE;
            }
        }
        return kFALSE;
    }

    template< class XType, size_t XMaxSize >
    Bool_t KSList< XType, XMaxSize >::ForEachUntilFalse( Bool_t(XType::*aMember)() )
    {
        for( fCurrentElement = 0; fCurrentElement < fEndElement; fCurrentElement++ )
        {
            if( (fElements[fCurrentElement]->*aMember)() == kFALSE )
            {
                return kFALSE;
            }
        }
        return kTRUE;
    }

    template< class XType, size_t XMaxSize >
    template< class XArgumentType >
    Bool_t KSList< XType, XMaxSize >::ForEachUntilFalse( Bool_t(XType::*aMember)( XArgumentType ), XArgumentType anArgument )
    {
        for( fCurrentElement = 0; fCurrentElement < fEndElement; fCurrentElement++ )
        {
            if( (fElements[fCurrentElement]->*aMember)( anArgument ) == kFALSE )
            {
                return kFALSE;
            }
        }
        return kTRUE;
    }

    template< class XType, size_t XMaxSize >
    template< class XReturnType >
    XReturnType KSList< XType, XMaxSize >::LargestOfAll( XReturnType(XType::*aMember)() )
    {
        XReturnType Largest = -1.e300;
        XReturnType CurrentValue;
        for( fCurrentElement = 0; fCurrentElement < fEndElement; fCurrentElement++ )
        {
            CurrentValue = (fElements[fCurrentElement]->*aMember)();
            if( CurrentValue > Largest )
            {
                Largest = CurrentValue;
            }
        }
        return Largest;
    }

    template< class XType, size_t XMaxSize >
    template< class XReturnType >
    XReturnType KSList< XType, XMaxSize >::SmallestOfAll( XReturnType(XType::*aMember)() )
    {
        XReturnType Smallest = 1.e300;
        XReturnType CurrentValue;
        for( fCurrentElement = 0; fCurrentElement < fEndElement; fCurrentElement++ )
        {
            CurrentValue = (fElements[fCurrentElement]->*aMember)();
            if( CurrentValue < Smallest )
            {
                Smallest = CurrentValue;
            }
        }
        return Smallest;
    }

}

#endif /* KSLIST_H_ */
