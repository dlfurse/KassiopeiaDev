#ifndef KSEXPRESSION_H_
#define KSEXPRESSION_H_

#include "Rtypes.h"

namespace Kassiopeia
{

    template< class XLeft, class XRight >
    class KSAddExpression
    {
        public:
            KSAddExpression( const XLeft& aLeftOperand, const XRight& aRightOperand ) :
                fLeft( aLeftOperand ),
                fRight( aRightOperand )
            {
            }
            virtual ~KSAddExpression()
            {
            }

            Double_t operator[]( const size_t& anIndex ) const
            {
                return (fLeft[anIndex] + fRight[anIndex]);
            }

        private:
            const XLeft& fLeft;
            const XRight& fRight;
    };
    template< class XLeft, class XRight >
    KSAddExpression< XLeft, XRight > operator+( const XLeft& aLeftOperand, const XRight& aRightOperand )
    {
        return KSAddExpression< XLeft, XRight >( aLeftOperand, aRightOperand );
    }

    template< class XLeft, class XRight >
    class KSSubtractExpression
    {
        public:
            KSSubtractExpression( const XLeft& aLeftOperand, const XRight& aRightOperand ) :
                fLeft( aLeftOperand ),
                fRight( aRightOperand )
            {
            }
            virtual ~KSSubtractExpression()
            {
            }

            Double_t operator[]( const size_t& anIndex ) const
            {
                return (fLeft[anIndex] - fRight[anIndex]);
            }

        private:
            const XLeft& fLeft;
            const XRight& fRight;
    };
    template< class XLeft, class XRight >
    KSSubtractExpression< XLeft, XRight > operator-( const XLeft& aLeftOperand, const XRight& aRightOperand )
    {
        return KSSubtractExpression< XLeft, XRight >( aLeftOperand, aRightOperand );
    }

    template< class XType >
    class KSMultiplyExpression
    {
        public:
            KSMultiplyExpression( const XType& anOperand, const Double_t& aFactor ) :
                fOperand( anOperand ),
                fFactor( aFactor )
            {
            }
            virtual ~KSMultiplyExpression()
            {
            }

            Double_t operator[]( const size_t& anIndex ) const
            {
                return fOperand[anIndex] * fFactor;
            }

        private:
            const XType& fOperand;
            const Double_t& fFactor;
    };
    template< class XType >
    KSMultiplyExpression< XType > operator*( const XType& anOperand, const Double_t& aFactor )
    {
        return KSMultiplyExpression< XType >( anOperand, aFactor );
    }
    template< class XType >
    KSMultiplyExpression< XType > operator*( const Double_t& aFactor, const XType& anOperand )
    {
        return KSMultiplyExpression< XType >( anOperand, aFactor );
    }

    template< class XType >
    class KSDivideExpression
    {
        public:
            KSDivideExpression( const XType& anOperand, const Double_t& aFactor ) :
                fOperand( anOperand ),
                fFactor( aFactor )
            {
            }
            virtual ~KSDivideExpression()
            {
            }

            Double_t operator[]( const size_t& anIndex ) const
            {
                return fOperand.CopyValueAt( anIndex ) / fFactor;
            }

        private:
            const XType& fOperand;
            const Double_t& fFactor;

    };
    template< class XType >
    KSDivideExpression< XType > operator/( const XType& anOperand, const Double_t& aFactor )
    {
        return KSDivideExpression< XType >( anOperand, aFactor );
    }

}

#endif /* KSEXPRESSION_H_ */
