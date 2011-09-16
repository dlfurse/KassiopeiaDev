#ifndef CONSTANTDENSITYCALCULATOR_HH
#define CONSTANTDENSITYCALCULATOR_HH

/** @file
 * @brief contains ConstantDensityCalculator
 * @details
 *  <b>Revision History:</b>
 *   \verbatim
 * Date   Name  Brief description
 * 02/19/10   J. Barrett    First version
 *\endverbatim
 *
 */

/**
 *	@class Kassiopeia::ConstantDensityCalculator
 * @author J. P. Barrett (barrettj@mit.edu)
 *
 * @brief
 *returns a constant density
 *
 * @details
 * <b>Detailed Description:</b><br>
 * class that obtains the density of the scattering
 * material as a function of position for the volume in which it is defined.
 *
 *
 */





#include "DensityCalculator.h"

namespace Kassiopeia{
    class ConstantDensityCalculator: public DensityCalculator
    {
    public:

	    ConstantDensityCalculator():DensityCalculator()
	    {
		    bHaveCachedValue = false;
	    };

	    virtual ~ConstantDensityCalculator(){;};

	    //Action
	    Double_t GetDensity(TVector3 /*position*/) const;
	    Double_t GetDensity(const Kassiopeia::KSBasicParticle* const /*pParticle*/) const;

	    //Getters
	    inline Double_t GetPressure()
	    {
	    	return fPressure;
	    }
	    inline Double_t GetTemperature()
	    {
	    	return fTemperature;
	    }

	    //Setters
	    inline void SetPressure(Double_t P)
	    {
			fPressure = P*100.;  //fPressure in Pascal
			bHaveCachedValue = false;
	    } //must be set in mbar

	    inline void SetTemperature(Double_t T)
	    {
	    	fTemperature = T;
	    	bHaveCachedValue = false;
	    } //must bet set in Kelvin

	    inline void SetAll(Double_t P, Double_t T, Double_t /*F*/)
	    {
		    fPressure = P;
		    fTemperature = T;
		    bHaveCachedValue = false;
	    }

	    void SetDensity(Double_t D)
	    {
	    	fDensity = D;
	    	bHaveCachedValue = true;
	    } //set number density 1/m^3 directly;



    private:

	    void ComputeDensity() const;

	    mutable Bool_t bHaveCachedValue;

	    mutable Double_t fDensity; //returns number density in 1/m^3

	    Double_t fPressure; //Pascal
	    Double_t fTemperature; //Kelvin

    };
}


#endif /* end of CONSTANTDENSITYCALCULATOR_HH */
