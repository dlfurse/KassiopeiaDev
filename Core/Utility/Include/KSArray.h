#ifndef KSARRAY_H_
#define KSARRAY_H_

#include "Rtypes.h"

namespace Kassiopeia
{
    template< size_t XDimension >
    class KSArray
    {
        public:
            KSArray()
            {
            }
            virtual ~KSArray()
            {
            }

            Double_t operator[]( const size_t& anIndex ) const
            {
                return fData[anIndex];
            }
            Double_t& operator[]( const size_t& anIndex )
            {
                return fData[anIndex];
            }

            KSArray< XDimension >& operator=( const Double_t& anOperand )
            {
                for( size_t Index = 0; Index < XDimension; Index++ )
                {
                    fData[Index] = anOperand;
                }
                return *this;
            }
            template< class XType >
            KSArray< XDimension >& operator=( const XType& anOperand )
            {
                for( size_t Index = 0; Index < XDimension; Index++ )
                {
                    fData[Index] = anOperand[Index];
                }
                return *this;
            }

            template< class XType >
            KSArray< XDimension >& operator+=( const XType& anOperand )
            {
                for( size_t Index = 0; Index < XDimension; Index++ )
                {
                    fData[Index] += anOperand[Index];
                }
                return *this;
            }
            template< class XType >
            KSArray< XDimension >& operator-=( const XType& anOperand )
            {
                for( size_t Index = 0; Index < XDimension; Index++ )
                {
                    fData[Index] -= anOperand[Index];
                }
                return *this;
            }
            KSArray< XDimension >& operator*=( const Double_t& aFactor )
            {
                for( size_t Index = 0; Index < XDimension; Index++ )
                {
                    fData[Index] *= aFactor;
                }
                return *this;
            }
            KSArray< XDimension >& operator/=( const Double_t& aFactor )
            {
                for( size_t Index = 0; Index < XDimension; Index++ )
                {
                    fData[Index] /= aFactor;
                }
                return *this;
            }

        private:
            Double_t fData[XDimension];
    };

}

#endif
