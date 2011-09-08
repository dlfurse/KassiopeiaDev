#ifndef KSCONST_H_
#define KSCONST_H_

#include "Rtypes.h"
/**
 @file
 @brief contains KSConst
 @details
 *<b>Revision History:</b>
 *  \verbatim
 *  Date       Name          Brief description
 *  -----------------------------------------------
 *   09/12/12  W. Kaefer      First version
 *   19/03/10  N. Oblath      Changed from namespace to class with static methods
 *  \endverbatim
 *
 */

/**
 * \class KSConst
 * \author W. Kaefer
 * \brief  this class contains various fundamental constants.
 *  \details Values are taken from PDG edition 2006, unless pointed out otherwise. The naming conventions are: normal name for SI units, a suffix _unit for something else.
 * For example, masses are usually give in both kg and eV with no suffix in the former case and suffix _eV in the latter.
 * Masses will probably be moved to some sort of particle table at some point.
 **/

class KSConst
{
    public:
        KSConst();
        virtual ~KSConst();

        //mathematical numbers
        static inline Double_t Pi()
        {
            return 3.14159265358979311599796346854;
        } //!< pi

        static inline Double_t C()
        {
            return 299792458.;
        } //!< c im m/s

        static inline Double_t Q()
        {
            return 1.60217653E-19;
        } //!< elementary charge  in C(>0)

        static inline Double_t Alpha()
        {
            return 7.297352568E-3;
        } //!< fine structure constant alpha

        static inline Double_t Hbar()
        {
            return 1.05457168E-34;
        }//!< hbar in J s-1

        static inline Double_t HbarC_eV()
        {
            return 197.326968E-9;
        }//!<hbar c in m eV.

        static inline Double_t kB()
        {
            return 1.3806505E-23;
        }//!< Boltzmann constant J/K

        static inline Double_t kB_eV()
        {
            return 8.617343E-5;
        }//!< Boltzmann constant eV/K

        //atomic properties
        static inline Double_t AtomicMassUnit()
        {
            return 1.66053886E-27;
        } //!< unified atomic mass unit in kg

        static inline Double_t AtomicMassUnit_eV()
        {
            return 931.49404E6;
        } //!< unified atomic mass unit in eV/c^2

        static inline Double_t BohrRadius()
        {
            return 0.5291772108E-10;
        } //!<Bohr radius (M_prot -> infinity)

        static inline Double_t BohrRadiusSquared()
        {
            return 2.8002852043e-21;
        } //!<squared Bohr radius

        static inline Double_t ERyd_eV()
        {
            return 13.6056923;
        } //!< Rydberg energy (ionization energy of atomic hydrogen for m_prot -> infinity)

        //EM coupling constants
        static inline Double_t FourPiEps()
        {
            return 4. * Pi() * 8.854187817E012;
        } //!< 4  pi  epsilon0, Constant of Newtons force.

        static inline Double_t MuNull()
        {
            return 4.E-7 * Pi();
        }//!< permeability of free space

        //masses
        static inline Double_t M_el()
        {
            return 9.1093826E-31;
        } //!< electron mass in kg

        static inline Double_t M_el_eV()
        {
            return 510998.918;
        } //!< electron mass in ev

        static inline Double_t M_prot()
        {
            return 1.67262171E-27;
        } //!< proton mass in kg

        static inline Double_t M_prot_eV()
        {
            return 938.272029E6;
        } //!< proton mass in ev

        static inline Double_t M_deut()
        {
            return 3.34358334e-27;
        } //!< deuteron mass in kg
        static inline Double_t M_deut_eV()
        {
            return 1875.61282E6;
        } //!< deuteron mass in eV.

        //Tritium properties
        static inline Double_t M_T2()
        {
            return 6 * AtomicMassUnit();
        } //!< tritium molecule mass in kg (estimation. needs a literature search)

        static inline Double_t M_T2_eV()
        {
            return 6 * AtomicMassUnit_eV();
        } //!< tritium molecule mass in eV/c^2

        static inline Double_t Viscosity()
        {
            return 2.425E-6;
        } //!< tritium viscosity coefficient at T=30K [Pa s] (cite? Sharipov?)

        static inline Double_t FermiConstant_eV()
        {
            return 1.16637E-5 * 1E-18 * KSConst::HbarC_eV() * KSConst::HbarC_eV() * KSConst::HbarC_eV();
        } //!< Fermi coupling constant [eVm^3]

        //some SSC specific stuff
        static inline Double_t costhetaC()
        {
            return 0.9750; //!< cos(Cabibbo angle). Reference?
        }

        static inline Double_t MatrixM()
        {
            return 2.348; //!< nuclear matrix element. Reference?
        }

        static inline Double_t gV()
        {
            return 1.0; //!< alternative to nuclear matrix element: use (g_V^2 + 3 * g_A^2) Reference?
        }

        static inline Double_t gA()
        {
            return 1.247; //!< alternative to nuclear matrix element: use (g_V^2 + 3 * g_A^2) Reference?
        }
};

#endif //KACONST_H
