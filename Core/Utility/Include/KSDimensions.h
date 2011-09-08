#ifndef KSDIMENSIONS_H_
#define KSDIMENSIONS_H_

#include "KSAssert.h"

#include "KSTypeLists.h"
#include "KSTypeIntegers.h"
#include "KSTypeLogic.h"

#include <string>
using std::string;

#include <sstream>
using std::stringstream;

namespace Kassiopeia
{

    //********************
    //dimension definition
    //********************

    template< class XDimensionList >
    class KSDimension;

    template< int XMassPowerValue, int XLengthPowerValue, int XTimePowerValue, int XChargePowerValue, int XTemperaturePowerValue, int XIntensityPowerValue, int XAnglePowerValue >
    class KSDimension< KSTYPELIST7( KSTypeInteger< XMassPowerValue >, KSTypeInteger< XLengthPowerValue >, KSTypeInteger< XTimePowerValue >, KSTypeInteger< XChargePowerValue >, KSTypeInteger< XTemperaturePowerValue >, KSTypeInteger< XIntensityPowerValue >, KSTypeInteger< XAnglePowerValue > ) >
    {
        public:
            template< class XRight >
            class Multiply;

            template< int XRightMassPowerValue, int XRightLengthPowerValue, int XRightTimePowerValue, int XRightChargePowerValue, int XRightTemperaturePowerValue, int XRightIntensityPowerValue, int XRightAnglePowerValue >
            class Multiply< KSDimension< KSTYPELIST7( KSTypeInteger< XRightMassPowerValue >, KSTypeInteger< XRightLengthPowerValue >, KSTypeInteger< XRightTimePowerValue >, KSTypeInteger< XRightChargePowerValue >, KSTypeInteger< XRightTemperaturePowerValue >, KSTypeInteger< XRightIntensityPowerValue >, KSTypeInteger< XRightAnglePowerValue > ) > >
            {
                public:
                    typedef KSDimension< KSTYPELIST7( KSTypeInteger< XMassPowerValue + XRightMassPowerValue >, KSTypeInteger< XLengthPowerValue + XRightLengthPowerValue >, KSTypeInteger< XTimePowerValue + XRightTimePowerValue >, KSTypeInteger< XChargePowerValue + XRightChargePowerValue >, KSTypeInteger< XTemperaturePowerValue + XRightTemperaturePowerValue >, KSTypeInteger< XIntensityPowerValue + XRightIntensityPowerValue >, KSTypeInteger< XAnglePowerValue + XRightAnglePowerValue > ) > Type;
            };

            template< class XRight >
            class Divide;

            template< int XRightMassPowerValue, int XRightLengthPowerValue, int XRightTimePowerValue, int XRightChargePowerValue, int XRightTemperaturePowerValue, int XRightIntensityPowerValue, int XRightAnglePowerValue >
            class Divide< KSDimension< KSTYPELIST7( KSTypeInteger< XRightMassPowerValue >, KSTypeInteger< XRightLengthPowerValue >, KSTypeInteger< XRightTimePowerValue >, KSTypeInteger< XRightChargePowerValue >, KSTypeInteger< XRightTemperaturePowerValue >, KSTypeInteger< XRightIntensityPowerValue >, KSTypeInteger< XRightAnglePowerValue > ) > >
            {
                public:
                    typedef KSDimension< KSTYPELIST7( KSTypeInteger< XMassPowerValue - XRightMassPowerValue >, KSTypeInteger< XLengthPowerValue - XRightLengthPowerValue >, KSTypeInteger< XTimePowerValue - XRightTimePowerValue >, KSTypeInteger< XChargePowerValue - XRightChargePowerValue >, KSTypeInteger< XTemperaturePowerValue - XRightTemperaturePowerValue >, KSTypeInteger< XIntensityPowerValue - XRightIntensityPowerValue >, KSTypeInteger< XAnglePowerValue - XRightAnglePowerValue > ) > Type;
            };

            template< class XRight >
            class Equal;

            template< int XRightMassPowerValue, int XRightLengthPowerValue, int XRightTimePowerValue, int XRightChargePowerValue, int XRightTemperaturePowerValue, int XRightIntensityPowerValue, int XRightAnglePowerValue >
            class Equal< KSDimension< KSTYPELIST7( KSTypeInteger< XRightMassPowerValue >, KSTypeInteger< XRightLengthPowerValue >, KSTypeInteger< XRightTimePowerValue >, KSTypeInteger< XRightChargePowerValue >, KSTypeInteger< XRightTemperaturePowerValue >, KSTypeInteger< XRightIntensityPowerValue >, KSTypeInteger< XRightAnglePowerValue > ) > >
            {
                public:
                    enum
                    {
                        Value = KSTypeEqual< KSDimension< KSTYPELIST7( KSTypeInteger< XMassPowerValue >, KSTypeInteger< XLengthPowerValue >, KSTypeInteger< XTimePowerValue >, KSTypeInteger< XChargePowerValue >, KSTypeInteger< XTemperaturePowerValue >, KSTypeInteger< XIntensityPowerValue >, KSTypeInteger< XAnglePowerValue > ) >, KSDimension< KSTYPELIST7( KSTypeInteger< XRightMassPowerValue >, KSTypeInteger< XRightLengthPowerValue >, KSTypeInteger< XRightTimePowerValue >, KSTypeInteger< XRightChargePowerValue >, KSTypeInteger< XRightTemperaturePowerValue >, KSTypeInteger< XRightIntensityPowerValue >, KSTypeInteger< XRightAnglePowerValue > ) > >::Value
                    };
            };

        public:
            static const string fSymbol;
            static const string ConstructDimensionSymbol()
            {

                stringstream Symbol;
                Symbol.clear();
                Symbol.str( "" );

                Symbol << "[ ";

                if( XMassPowerValue != 0 )
                {
                    Symbol << "M";
                    if( XMassPowerValue != 1 )
                    {
                        Symbol << "^" << XMassPowerValue;
                    }
                    Symbol << " ";
                }

                if( XLengthPowerValue != 0 )
                {
                    Symbol << "L";
                    if( XLengthPowerValue != 1 )
                    {
                        Symbol << "^" << XLengthPowerValue;
                    }
                    Symbol << " ";
                }

                if( XTimePowerValue != 0 )
                {
                    Symbol << "T";
                    if( XTimePowerValue != 1 )
                    {
                        Symbol << "^" << XTimePowerValue;
                    }
                    Symbol << " ";
                }

                if( XChargePowerValue != 0 )
                {
                    Symbol << "Q";
                    if( XChargePowerValue != 1 )
                    {
                        Symbol << "^" << XChargePowerValue;
                    }
                    Symbol << " ";
                }

                if( XTemperaturePowerValue != 0 )
                {
                    Symbol << "Th";
                    if( XTemperaturePowerValue != 1 )
                    {
                        Symbol << "^" << XTemperaturePowerValue;
                    }
                    Symbol << " ";
                }

                if( XIntensityPowerValue != 0 )
                {
                    Symbol << "I";
                    if( XIntensityPowerValue != 1 )
                    {
                        Symbol << "^" << XIntensityPowerValue;
                    }
                    Symbol << " ";
                }

                if( XAnglePowerValue != 0 )
                {
                    Symbol << "A";
                    if( XAnglePowerValue != 1 )
                    {
                        Symbol << "^" << XAnglePowerValue;
                    }
                    Symbol << " ";
                }

                Symbol << "]";

                return Symbol.str();
            }

    };

    //eclipse cannot understand this line, but it is nonetheless correct.
    template< int XMassPowerValue, int XLengthPowerValue, int XTimePowerValue, int XChargePowerValue, int XTemperaturePowerValue, int XIntensityPowerValue, int XAnglePowerValue >
    const string KSDimension< KSTypeList< KSTypeInteger< XMassPowerValue >, KSTypeList< KSTypeInteger< XLengthPowerValue >, KSTypeList< KSTypeInteger< XTimePowerValue >, KSTypeList< KSTypeInteger< XChargePowerValue >, KSTypeList< KSTypeInteger< XTemperaturePowerValue >, KSTypeList< KSTypeInteger< XIntensityPowerValue >, KSTypeList< KSTypeInteger< XAnglePowerValue >, KSTypeNull > > > > > > > >::fSymbol = KSDimension< KSTypeList< KSTypeInteger< XMassPowerValue >, KSTypeList< KSTypeInteger< XLengthPowerValue >, KSTypeList< KSTypeInteger< XTimePowerValue >, KSTypeList< KSTypeInteger< XChargePowerValue >, KSTypeList< KSTypeInteger< XTemperaturePowerValue >, KSTypeList< KSTypeInteger< XIntensityPowerValue >, KSTypeList< KSTypeInteger< XAnglePowerValue >, KSTypeNull > > > > > > > >::ConstructDimensionSymbol();

    //******************
    //dimension typedefs
    //******************

    //dimensionless                                 //mass               //length             //time               //charge             //temperature        //intensity          //angle
    typedef KSDimension< KSTYPELIST7( KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 > ) > KSDimensionless;

    //base dimensions
    typedef KSDimension< KSTYPELIST7( KSTypeInteger< 1 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 > ) > KSMassDimension;
    typedef KSDimension< KSTYPELIST7( KSTypeInteger< 0 >, KSTypeInteger< 1 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 > ) > KSLengthDimension;
    typedef KSDimension< KSTYPELIST7( KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 1 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 > ) > KSTimeDimension;
    typedef KSDimension< KSTYPELIST7( KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 1 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 > ) > KSChargeDimension;
    typedef KSDimension< KSTYPELIST7( KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 1 >, KSTypeInteger< 0 >, KSTypeInteger< 0 > ) > KSTemperatureDimension;
    typedef KSDimension< KSTYPELIST7( KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 1 >, KSTypeInteger< 0 > ) > KSIntensityDimension;
    typedef KSDimension< KSTYPELIST7( KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 1 > ) > KSAngleDimension;

    //derived mechanical dimensions
    typedef KSDimension< KSTYPELIST7( KSTypeInteger< 0 >, KSTypeInteger< 2 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 > ) > KSAreaDimension;
    typedef KSDimension< KSTYPELIST7( KSTypeInteger< 0 >, KSTypeInteger< 3 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 > ) > KSVolumeDimension;
    typedef KSDimension< KSTYPELIST7( KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< -1 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 > ) > KSFrequencyDimension;
    typedef KSDimension< KSTYPELIST7( KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< -1 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 1 > ) > KSAngularFrequencyDimension;
    typedef KSDimension< KSTYPELIST7( KSTypeInteger< 0 >, KSTypeInteger< 1 >, KSTypeInteger< -1 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 > ) > KSVelocityDimension;
    typedef KSDimension< KSTYPELIST7( KSTypeInteger< 0 >, KSTypeInteger< 1 >, KSTypeInteger< -2 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 > ) > KSAccelerationDimension;
    typedef KSDimension< KSTYPELIST7( KSTypeInteger< 1 >, KSTypeInteger< 1 >, KSTypeInteger< -1 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 > ) > KSMomentumDimension;
    typedef KSDimension< KSTYPELIST7( KSTypeInteger< 1 >, KSTypeInteger< 1 >, KSTypeInteger< -2 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 > ) > KSForceDimension;
    typedef KSDimension< KSTYPELIST7( KSTypeInteger< 1 >, KSTypeInteger< 2 >, KSTypeInteger< -1 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< -1 > ) > KSAngularMomentumDimension;
    typedef KSDimension< KSTYPELIST7( KSTypeInteger< 1 >, KSTypeInteger< 2 >, KSTypeInteger< -2 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< -1 > ) > KSTorqueDimension;
    typedef KSDimension< KSTYPELIST7( KSTypeInteger< 1 >, KSTypeInteger< 2 >, KSTypeInteger< -2 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 > ) > KSEnergyDimension;
    typedef KSDimension< KSTYPELIST7( KSTypeInteger< 1 >, KSTypeInteger< 2 >, KSTypeInteger< -3 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 > ) > KSPowerDimension;
    typedef KSDimension< KSTYPELIST7( KSTypeInteger< 1 >, KSTypeInteger< -1 >, KSTypeInteger< -2 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 > ) > KSPressureDimension;

    //derived electromagnetic dimensions
    typedef KSDimension< KSTYPELIST7( KSTypeInteger< 1 >, KSTypeInteger< 2 >, KSTypeInteger< -2 >, KSTypeInteger< -1 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 > ) > KSElectricPotentialDimension;
    typedef KSDimension< KSTYPELIST7( KSTypeInteger< 1 >, KSTypeInteger< 1 >, KSTypeInteger< -2 >, KSTypeInteger< -1 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 > ) > KSElectricFieldDimension;
    typedef KSDimension< KSTYPELIST7( KSTypeInteger< 1 >, KSTypeInteger< 1 >, KSTypeInteger< -1 >, KSTypeInteger< -1 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 > ) > KSMagneticPotentialDimension;
    typedef KSDimension< KSTYPELIST7( KSTypeInteger< 1 >, KSTypeInteger< 0 >, KSTypeInteger< -1 >, KSTypeInteger< -1 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 > ) > KSMagneticFieldDimension;
    typedef KSDimension< KSTYPELIST7( KSTypeInteger< -1 >, KSTypeInteger< -3 >, KSTypeInteger< 2 >, KSTypeInteger< 2 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 > ) > KSElectricPermittivityDimension;
    typedef KSDimension< KSTYPELIST7( KSTypeInteger< 1 >, KSTypeInteger< 1 >, KSTypeInteger< 0 >, KSTypeInteger< -2 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 > ) > KSMagneticPermeabilityDimension;

    typedef KSDimension< KSTYPELIST7( KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< -1 >, KSTypeInteger< 1 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 > ) > KSCurrentDimension;
    typedef KSDimension< KSTYPELIST7( KSTypeInteger< 1 >, KSTypeInteger< 2 >, KSTypeInteger< -1 >, KSTypeInteger< 2 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 > ) > KSResistanceDimension;
    typedef KSDimension< KSTYPELIST7( KSTypeInteger< 1 >, KSTypeInteger< 2 >, KSTypeInteger< 0 >, KSTypeInteger< -1 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 > ) > KSInductanceDimension;
    typedef KSDimension< KSTYPELIST7( KSTypeInteger< -1 >, KSTypeInteger< -2 >, KSTypeInteger< 2 >, KSTypeInteger< 2 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 > ) > KSCapacitanceDimension;
    typedef KSDimension< KSTYPELIST7( KSTypeInteger< 1 >, KSTypeInteger< 2 >, KSTypeInteger< -1 >, KSTypeInteger< -1 >, KSTypeInteger< 0 >, KSTypeInteger< 0 >, KSTypeInteger< 0 > ) > KSMagneticFluxDimension;

}

#endif
