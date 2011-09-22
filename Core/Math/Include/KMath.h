#ifndef KMATH_H
#define KMATH_H

/**
 * @file
 * @brief contains KMath
 * @details
 <b>Revision History:</b>
 \verbatim
 Date         Name          Brief description
 -----------------------------------------------
 06/04/2010   N. Oblath     First version
 \endverbatim

 */

/*!
 * @class Kassiopeia::KMath
 @author N. Oblath
 
 @brief Static class for general math functions
 
 @details
 <b>Detailed Description:</b>
 This class is intended to be a central location for general math functions that 
 aren't available in either ROOT, GSL, or BOOST.
 This can also be different implementations of algorithms present in those packages.
 
 */


#include <algorithm>

#include "Rtypes.h"

#include "TMath.h"
#include "TVectorT.h"

#include "KSRandom.h"


namespace Kassiopeia {
    
    class KMath {
    public:
        
        //! Randomly shuffle an array
        /*!
         This is a Fisher-Yates alrgorithm for randomly shuffling an array.
         The shuffle is done in place.
         See http://en.wikipedia.org/wiki/Fisher-Yates_shuffle for more details.
         */
        template <class T>
        static void Shuffle(T*, Int_t);
        
        //! Randomly shuffle a container with an iterator
        /*!
         This is a Fisher-Yates alrgorithm for randomly shuffling an array.
         The shuffle is done in place.
         See http://en.wikipedia.org/wiki/Fisher-Yates_shuffle for more details.
         */
        template <class Iterator>
        static void Shuffle(Iterator, Iterator);
        
        //! Randomly shuffle a TVectorT
        /*!
         This is a Fisher-Yates alrgorithm for randomly shuffling an array.
         The shuffle is done in place.
         See http://en.wikipedia.org/wiki/Fisher-Yates_shuffle for more details.
         */
        template <class T>
        static void Shuffle(TVectorT<T>&);
        
        //! Find the minimum and maximum elements of a TVectorT
        /*!
         The minimum and maximum elements of a TVectorT are found using the same algorithms
         as TVectorT::Min() and Max() (see TMath::LocMin(Long64_t, const T*) for detailed comments).
         */
        template <class T>
        static void MinMaxElements(const TVectorT<T>&, Int_t&, Int_t&);


   	 static Double_t Lagrange(Int_t n,Double_t *xn,Double_t *fn,Double_t x);
   	//lagrange interpolation. moved here from Ferenc"s EH2Scattering class
   	//xn Stuetzstellen
   	//fn Funktionswerte
   	//n < 100
        
    private:
        KMath() {};
        ~KMath() {};
        
    };
    
    
    //*********************
    // Member definitions
    //*********************
    
    template <class T>
    void KMath::Shuffle(T* anArray, Int_t aLength) {
        KSRandom *tRand = KSRandom::GetInstance();
        for (Int_t iElement=aLength-1; iElement>0; iElement--) {
            Int_t iToSwap = TMath::Nint(tRand->Uniform((Double_t)(iElement)));
            std::swap(anArray[iToSwap], anArray[iElement]);
        }
        return;
    }
    
    template <class Iterator>
    void KMath::Shuffle(Iterator anIterFirst, Iterator anIterLast) {
        KSRandom *tRand = KSRandom::GetInstance();
        Int_t tNElements = anIterLast - anIterFirst;
        for (Int_t iElement=tNElements-1; iElement>0; iElement--) {
            Int_t iToSwap = TMath::Nint(tRand->Uniform((Double_t)(iElement)));
            std::swap(anIterFirst[iToSwap], anIterFirst[iElement]);
        }
        return;
    }
    
    template <class T>
    void KMath::Shuffle(TVectorT<T>& aTVec) {
        KSRandom *tRand = KSRandom::GetInstance();
        Int_t tNElements = aTVec.GetNoElements();
        for (Int_t iElement=tNElements-1; iElement>0; iElement--) {
            Int_t iToSwap = TMath::Nint(tRand->Uniform((Double_t)(iElement)));
            std::swap(aTVec[iToSwap], aTVec[iElement]);
        }
        return;
    }
    
    template <class T>
    void KMath::MinMaxElements(const TVectorT<T>& aTVec, Int_t& iMin, Int_t& iMax) {
        T xMin = aTVec[0];
        T xMax = aTVec[0];
        iMin = 0, iMax = 0;
        for (Long64_t i=1; i<aTVec.GetNoElements(); i++) {
            if (xMin > aTVec[i]) {
                xMin = aTVec[i];
                iMin = i;
            } else if (xMax < aTVec[i]) {
                xMax = aTVec[i];
                iMax = i;
            }
        }
        return;
    }
    
    
    inline Double_t KMath::Lagrange(Int_t n,Double_t *xn,Double_t *fn,Double_t x){
    		Double_t f,a[100],b[100],aa,bb;
    		f=0.;
    		for( Int_t j=0;j<n;j++)
    		{
    			for(Int_t i=0;i<n;i++)
    			{
    				a[i]=x-xn[i];
    				b[i]=xn[j]-xn[i];
    			}
    			a[j]=b[j]=aa=bb=1.;

    			for( Int_t i=0;i<n;i++) {
    				aa=aa*a[i];
    				bb=bb*b[i];
    			}
    			f+=fn[j]*aa/bb;
    		}
    		return f;
    	}


    
} // end Kassiopeia namespace

#endif
