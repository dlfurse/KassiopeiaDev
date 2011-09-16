#ifndef DENSITYCALCULATOR_HH
#define DENSITYCALCULATOR_HH

/** @file
 * @brief contains DensityCalculator
 * @details
 * <b>Revision History:</b>
 * \verbatim
 * Date   Name  Brief description
 * 02/19/10   J. Barrett    First version
 *\endverbatim
 *
 */

/**
 *@class Kassiopeia::DensityCalculator
 * @author J. P. Barrett (barrettj@mit.edu)
 *
 * @brief
 * virtual base class that obtains the density of the scattering
 * material as a function of position for the volume in which it is defined.
 *
 * @details
 * <b>Detailed Description:</b><br>
 * */




#include "KSBasicParticle.h"
#include "TVector3.h"

namespace Kassiopeia{

	class DensityCalculator
	{
		public:

		DensityCalculator();
		virtual ~DensityCalculator();

		virtual Double_t GetDensity(TVector3 position) const = 0;
		virtual Double_t GetDensity(const KSBasicParticle* const pParticle) const = 0;

		protected:

	};

}

#endif /* end of DENSITYCALCULATOR_HH */

