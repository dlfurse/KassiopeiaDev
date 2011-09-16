/** @file 
 *
 * @author J. P. Barrett (barrettj@mit.edu)
 *
 * @brief
 *
 * @section Class
 *
 *
 * @section Detailed Description
 * class that returns a constant density of the scattering
 * material everywhere
 *
 *
 *
 * @section Revision History
 * Date   Name  Brief description
 * 02/19/10   J. Barrett    First version
 *
 *
 */

#include "ConstantDensityCalculator.h"
#include "KSConst.h"

namespace Kassiopeia{


	Double_t ConstantDensityCalculator::GetDensity(TVector3 /*position*/) const
	{
		if(bHaveCachedValue)
		{
			return fDensity;
		}
		else
		{
//			#ifdef DEBUG_VERBOSE
//
//			E = KSException::eScatteringDebug;
//			E < "ConstantDensityCalculator::GetDensity";
//			CatchException(E);
//			#endif



			ComputeDensity();

//			#ifdef DEBUG_VERBOSE
//			E << "Pressure (mbar) = " << fPressure/100. << ", Temperature (K) = " << fTemperature << " , Density (1/m^3) = " << fDensity;
//			CatchException(E);
//			#endif
			return fDensity;
		}

	};

	Double_t ConstantDensityCalculator::GetDensity(const Kassiopeia::KSBasicParticle* const /*pParticle*/) const
	{
		if(bHaveCachedValue)
		{
			return fDensity;
		}
		else
		{
			ComputeDensity();
			return fDensity;
		}
	};

	void ConstantDensityCalculator::ComputeDensity() const
	{
		fDensity = (fPressure)/(KSConst::kB()*fTemperature);
		bHaveCachedValue = true;
	};
}
