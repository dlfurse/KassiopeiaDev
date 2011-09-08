#ifndef KSRANDOM_H
#define KSRANDOM_H 1

#include "TRandom3.h"
/**
 @file
 @brief contains KSRandom
 @details
 <b>Revision History:</b>
 \verbatim
 Date       Name          Brief description
 -----------------------------------------------
 08/12/09   N. Oblath     First version
 25/03/10   N. Oblath     Implement Kassiopeia namespaces; made DeleteInstance static
 01/07/10   N. Oblath     Renamed to KSRandom; typdefed to KRandom for backwards compatibility
 18/08/10   N. Oblath     Added gKSRandom pointer
 \endverbatim

 */

/**
 *
 * @class Kassiopeia::KSRandom
 @author N. Oblath

 @brief Singleton random number generator for Kassiopeia

 @details
 <b>Detailed Description:</b><br>
 This is the standard random number generator for Kassiopeia.
 It is implemented as a singleton class, as there should only be one RNG running at a time.

 The class uses a RNG that inherits from ROOT's TRandom class, and includes inline methods
 duplicating all of TRandom's functionality.

 The specific RNG currently implemented is ROOT's TRandom3 class,
 which uses the Mersenne Twister algorithm.  Nobody knows what this is.

 See http://root.cern.ch/ for more information on TRandom and TRandom3.
 */

namespace Kassiopeia
{

    class KSRandom
    {
        public:
            //! Returns the singleton instance of KSRandom
            /*! Returns the static instance of KSRandom.
             Creates a new KSRandom if the instance doesn't yet exist.
             The seed value, aSeed, is only used if a new KSRandom is being created.
             See SetSeed(Int_t) for information about the seed value used.
             */
            static KSRandom* GetInstance( Int_t aSeed = 65539 );

            //! Destructor
            virtual ~KSRandom();
        private:
            //! Constructor
            KSRandom();
            //! Prevent copy-construction
            KSRandom( const KSRandom& );
            //! Prevent assignment
            KSRandom& operator=( const KSRandom& );

            //! Pointer to the KSRandom instance
            static KSRandom* fInstance;

            //! TRandom-derived RNG
            static TRandom *fRandom;

        public:
            /*!
             Returns a random number drawn from a binomial distribution between 0 and aNTot, inclusive
             The probability should be between 0 and 1.
             */
            Int_t Binomial( Int_t aNTot, Double_t aProb )
            {
                return fRandom->Binomial( aNTot, aProb );
            }

            /*!
             Returns a number distributed following a Breit-Wigner function with aMean and aGamma.
             */
            Double_t BreitWigner( Double_t aMean = 0., Double_t aGamma = 1. )
            {
                return fRandom->BreitWigner( aMean, aGamma );
            }

            /*!
             Returns a number distributed according to exp(-t/aTau)
             */
            Double_t Exp( Double_t aTau )
            {
                return fRandom->Exp( aTau );
            }

            /*!
             Returns a number distributed according to a normal distribution with aMean and aSigma.
             */
            Double_t Gaus( Double_t aMean = 0., Double_t aSigma = 1. )
            {
                return fRandom->Gaus( aMean, aSigma );
            }

            /*!
             Returns a integer on [0, aIMax-1]
             */
            Int_t Integer( Int_t aIMax )
            {
                return fRandom->Integer( aIMax );
            }

            /*!
             Returns a number according to a Landau distribution with aMean and aSigma
             */
            Double_t Landau( Double_t aMean = 0., Double_t aSigma = 1. )
            {
                return fRandom->Landau( aMean, aSigma );
            }

            /*!
             Returns a random integer according to a Poisson distribution with aMean.
             */
            Int_t Poisson( Double_t aMean )
            {
                return fRandom->Poisson( aMean );
            }

            /*!
             Returns a random double according to a Poisson distribution with aMean.
             */
            Double_t PoissonD( Double_t aMean )
            {
                return fRandom->PoissonD( aMean );
            }

            /*!
             Returns a random number according to a flat distribution in the interval (0,1].
             */
            Double_t Rndm( Int_t i = 0 )
            {
                return fRandom->Rndm( i );
            }

            /*!
             Returns a random number according to a flat distribution in the interval (0, aX2].
             */
            Double_t Uniform( Double_t aX2 )
            {
                return fRandom->Uniform( aX2 );
            }

            /*!
             Returns a random number according to a flat distribution in the interval (aX1, aX2].
             */
            Double_t Uniform( Double_t aX1, Double_t aX2 )
            {
                return fRandom->Uniform( aX1, aX2 );
            }

            /*!
             Generates a random vector, drawn from a uniform distribution of vectors in a circle.
             Input: radius aR
             Output: 2-D vector (aX, aY)
             */
            void Circle( Double_t& aX, Double_t& aY, Double_t aR )
            {
                fRandom->Circle( aX, aY, aR );
            }

            /*!
             Return 2 numbers distributed following a Gaussian with mean=0 and sigma=1.
             */
            void Rannor( Float_t& aA, Float_t& aB )
            {
                fRandom->Rannor( aA, aB );
            }

            /*!
             Return 2 numbers distributed following a Gaussian with mean=0 and sigma=1.
             */
            void Rannor( Double_t& aA, Double_t& aB )
            {
                fRandom->Rannor( aA, aB );
            }

            /*!
             Returns an array of n random numbers uniformly distributed in (0,1]
             */
            void RndmArray( Int_t aN, Float_t* aArray )
            {
                fRandom->RndmArray( aN, aArray );
            }

            /*!
             Returns an array of n random numbers uniformly distributed in (0,1]
             */
            void RndmArray( Int_t aN, Double_t* aArray )
            {
                fRandom->RndmArray( aN, aArray );
            }

            /*!
             Generates a random vector, drawn from a uniform distribution of vectors in a sphere.
             Input: radius aR
             Output: 3-D vector (aX, aY, aZ)
             */
            void Sphere( Double_t& aX, Double_t& aY, Double_t& aZ, Double_t aR )
            {
                fRandom->Sphere( aX, aY, aZ, aR );
            }

            //! Get the seed value
            UInt_t GetSeed() const
            {
                return fRandom->GetSeed();
            }

            //! Set the seed value
            /*!
             Set the random generator seed.
             If seed is zero, the seed is set to the current machine clock.
             Note that the machine clock is returned with a precision of 1 second.
             If one calls SetSeed(0) within a loop and the loop time is less than 1s,
             all generated numbers will be identical!
             */
            void SetSeed( UInt_t aSeed = 65539 )
            {
                fRandom->SetSeed( aSeed );
                return;
            }
    };

    typedef KSRandom KRandom;

} // end Kassiopeia namespace

#endif // KSRANDOM_H
