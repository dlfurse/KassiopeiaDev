#ifndef KScatteringCalculatorInelastic_h
#define KScatteringCalculatorInelastic_h

/** @file
 @brief contains KScatterBasicInelasticCalculatorFerenc
 @details
 <b>Revision History:</b>
 \verbatim
 Date       Name        Brief description
 -----------------------------------------------------
 2009-06-29 S. Mertens  first version
 \endverbatim
 */

/*!
  \class Kassiopeia::KScatterBasicInelasticCalculatorFerenc

  \author F. Glueck. Put into this class by S.Mertens

  \brief  class to calculate inelastic electron  - hydrogen Scattering

 @details
 <b>Detailed Description:</b>
  This class contains methods to calculate:
  public:
  - electronic excitation cross section in m^2
  - energy loss and scattering angle for electronic excitation scattering
  - ionization cross section in  m^2
  - energy loss and scattering angle for ionization scattering
  
  protected:
  - differential cross section  of  inelastic electron scattering
  - total inelastic cross section
  - sigmaexc electronic excitation cross section to the B and C states
  - sigmadiss10 electronic dissociative excitation cross section
  - sigmadiss15 electronic dissociative excitation cross section
  - secondary electron energy


   The value for the inelastic cross section at 18.6 is 3.416E-22 m-2, in good agreement with the measured value of 3.40E-22 cm-2,
   (Assev et al) and calculated values (3.456E-22 m-2)
 */




#include <iostream>
#include <cmath>
#include <vector>

#include "Rtypes.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TMath.h"
#include "KSTextFile.h"


//////////////////////////////////////////////////////////////////////////////////


namespace Kassiopeia{
class KScatteringCalculatorInelastic
{
    public:

	// constructor
	KScatteringCalculatorInelastic();

	//!destructor.
	virtual ~KScatteringCalculatorInelastic();
	
	/*!
	\brief set the molecule type for which calculations will be performed
	
	\param aMolecule string name of a registered molecule type
	*/
	virtual void setmolecule(const std::string& aMolecule);

	/*!
	\brief returns the Ionization Energy of a secondary electron (a dice is thrown (weighted with the cross sections) to determine the shell from which the secondary electron is emmitted)
	 Ionization Energy computed in function: sigmaion
	*/
	virtual Double_t GetIonizationEnergy();

	/*!
    \brief electronic excitation cross section in m^2

    This function computes the electronic excitation cross section of
    electron scatt. on molecular hydrogen in m^2 .
    \param anE incident electron energy in eV,
    \return  electronic excitation cross section in m^2
	 */
	virtual Double_t sigmaexc(Double_t anE);

	/*!
    \brief energy loss and scattering angle for electronic excitation scattering

    This subroutine generates  energy loss and polar scatt. angle according to
    electron excitation scattering in molecular hydrogen.

    \param   anE incident electron energy in eV.
    \param   Eloss returns energy loss in eV
    \param   Theta returns change of polar angle in degrees
	 */
	virtual void randomexc(Double_t anE,Double_t& Eloss,Double_t& Theta);

	/*!
    \brief ionization cross section in  m^2

    This function computes the total ionization cross section of
    electron scatt. on molecular hydrogen of
    e+H2 --> e+e+H2^+  or  e+e+H^+ +H
    anE<250 eV: Eq. 5 of J. Chem. Phys. 104 (1996) 2956
    anE>250: sigma_i formula on page 107 in
    Phys. Rev. A7 (1973) 103.
    Good agreement with measured results of
    PR A 54 (1996) 2146, and
    Physica 31 (1965) 94.

    \param anE incident electron energy in eV,
    \return  ionization cross section
	 */
	virtual Double_t sigmaion(Double_t anE);

	/*!
    \brief energy loss and scattering angle for ionization scattering

    This subroutine generates  energy loss and polar scatt. angle according to
    electron ionization scattering in molecular hydrogen.
    The kinetic energy of the secondary electron is: Eloss-15.4 eV

    \param  anE incident electron energy in eV.
    \param  Eloss returns energy loss in eV
    \param  Theta returns change of polar angle in degrees


	 */
	virtual void randomion(Double_t anE,Double_t& Eloss,Double_t& Theta);






protected:


	/*!
    \brief  total inelastic cross section


    This function computes the total inelastic cross section of  electron scatt. on molecular hydrogen,
    in the first Born approximation in m^2 .
    See: Liu, Phys. Rev. A35 (1987) 591.

    \param anE incident electron energy in eV,
	 */
	Double_t sigmainel(Double_t anE);



	/*!
    \brief differential cross section of excitation electron scattering

    This subroutine computes the differential cross section
    Del= d sigma/d Omega  of excitation electron scattering
    on molecular hydrogen in m^2/steradian

    \param  anE electron kinetic energy in eV
    \param  cosTheta cos(Theta), where Theta is the polar scatt. angle

    \return  differential cross section of excitation electron scattering in m^2/steradian
	 */
	Double_t DiffXSecExc(Double_t anE,Double_t cosTheta);


	/*!
    \brief differential cross section  of  inelastic electron scattering


    This subroutine computes the differential cross section
    Dinel= d sigma/d Omega  of  inelastic electron scattering
    on molecular hydrogen,

    within the first Born approximation in m^2/steradian.

    \param anE electron kinetic energy in eV
    \param cosTheta cos(Theta), where Theta is the polar scatt. angle
	 */
	Double_t DiffXSecInel(Double_t anE,Double_t cosTheta);



	Double_t sumexc(Double_t K);
	
	

	/*!
    \brief sigmaexc electronic excitation cross section to the B and C states

    This function computes the sigmaexc electronic excitation
    cross section to the B and C states, with energy loss
    about 12.5 eV in m^2

    \param anE incident electron energy in eV,

	 */
	Double_t sigmaBC(Double_t anE);

	/*!
    \brief sigmadiss10 electronic
    dissociative excitation

    This function computes the sigmadiss10 electronic
    dissociative excitation
    cross section, with energy loss
    about 10 eV in m^2
    \param anE  incident electron energy in eV,

	 */
	Double_t sigmadiss10(Double_t anE);


	/*!
    \brief sigmadiss15 electronic dissociative excitation
    cross section

    This function computes the sigmadiss15 electronic dissociative excitation
    cross section, with energy loss about 15 eV  in m^2

    \param anE incident electron energy in eV
	 */
	Double_t sigmadiss15(Double_t anE);

	/*!
    \brief secondary electron energy W

    This subroutine generates secondary electron energy W
    from ionization of incident electron energy E, by using
    the Lorentzian of Aseev  et al. (Eq. 8).
    E and W in eV.
    \param E  incident electron energy in eV
    \param W  returns secondary electron energy
	 */
	void gensecelen(Double_t E,Double_t& W);

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// the following functions and methods are intended for generalizing the cross sections.
	Bool_t ReadData();
	Bool_t FindMinimum(); //determines fminimum;

	KSTextFile fDataFile;

	std::vector< Double_t> fBindingEnergy;// binding energy
	std::vector <Double_t> fOrbitalEnergy; // orbital kinetic energy;
	std::vector <Int_t> fNOccupation; //orbital occupation number

	Double_t fIonizationEnergy;
	std::string fMoleculeType;
	Int_t fMinimum; //position of orbital with minimal energy.
};
}
#endif //KScatteringCalculatorInelastic_h
