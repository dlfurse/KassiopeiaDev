#ifndef KSUNITS_H_
#define KSUNITS_H_

#include "KSDimensions.h"

namespace Kassiopeia
{

    //***************
    //unit definition
    //***************

    template< class XDimensionType >
    class KSUnit;

    template< int XMassPowerValue, int XLengthPowerValue, int XTimePowerValue, int XChargePowerValue, int XTemperaturePowerValue, int XIntensityPowerValue, int XAnglePowerValue >
    class KSUnit< KSDimension< KSTYPELIST7( KSTypeInteger< XMassPowerValue >, KSTypeInteger< XLengthPowerValue >, KSTypeInteger< XTimePowerValue >, KSTypeInteger< XChargePowerValue >, KSTypeInteger< XTemperaturePowerValue >, KSTypeInteger< XIntensityPowerValue >, KSTypeInteger< XAnglePowerValue > ) > >
    {
        public:
            typedef KSDimension< KSTYPELIST7( KSTypeInteger< XMassPowerValue >, KSTypeInteger< XLengthPowerValue >, KSTypeInteger< XTimePowerValue >, KSTypeInteger< XChargePowerValue >, KSTypeInteger< XTemperaturePowerValue >, KSTypeInteger< XIntensityPowerValue >, KSTypeInteger< XAnglePowerValue > ) > Dimension;

        public:
            static const string fSymbol;
            static const string ConstructUnitSymbol()
            {

                stringstream Symbol;
                Symbol.clear();
                Symbol.str( "" );

                Symbol << "[ ";

                if( XMassPowerValue != 0 )
                {
                    Symbol << "kg";
                    if( XMassPowerValue != 1 )
                    {
                        Symbol << "^" << XMassPowerValue;
                    }
                    Symbol << " ";
                }

                if( XLengthPowerValue != 0 )
                {
                    Symbol << "m";
                    if( XLengthPowerValue != 1 )
                    {
                        Symbol << "^" << XLengthPowerValue;
                    }
                    Symbol << " ";
                }

                if( XTimePowerValue != 0 )
                {
                    Symbol << "s";
                    if( XTimePowerValue != 1 )
                    {
                        Symbol << "^" << XTimePowerValue;
                    }
                    Symbol << " ";
                }

                if( XChargePowerValue != 0 )
                {
                    Symbol << "C";
                    if( XChargePowerValue != 1 )
                    {
                        Symbol << "^" << XChargePowerValue;
                    }
                    Symbol << " ";
                }

                if( XTemperaturePowerValue != 0 )
                {
                    Symbol << "K";
                    if( XTemperaturePowerValue != 1 )
                    {
                        Symbol << "^" << XTemperaturePowerValue;
                    }
                    Symbol << " ";
                }

                if( XIntensityPowerValue != 0 )
                {
                    Symbol << "cd";
                    if( XIntensityPowerValue != 1 )
                    {
                        Symbol << "^" << XIntensityPowerValue;
                    }
                    Symbol << " ";
                }

                if( XAnglePowerValue != 0 )
                {
                    Symbol << "rad";
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

    //can't use macros on this line because eclipse thinks it's an error
    template< int XMassPowerValue, int XLengthPowerValue, int XTimePowerValue, int XChargePowerValue, int XTemperaturePowerValue, int XIntensityPowerValue, int XAnglePowerValue >
    const string KSUnit< KSDimension< KSTypeList< KSTypeInteger< XMassPowerValue >, KSTypeList< KSTypeInteger< XLengthPowerValue >, KSTypeList< KSTypeInteger< XTimePowerValue >, KSTypeList< KSTypeInteger< XChargePowerValue >, KSTypeList< KSTypeInteger< XTemperaturePowerValue >, KSTypeList< KSTypeInteger< XIntensityPowerValue >, KSTypeList< KSTypeInteger< XAnglePowerValue >, KSTypeNull > > > > > > > > >::fSymbol = KSUnit< KSDimension< KSTypeList< KSTypeInteger< XMassPowerValue >, KSTypeList< KSTypeInteger< XLengthPowerValue >, KSTypeList< KSTypeInteger< XTimePowerValue >, KSTypeList< KSTypeInteger< XChargePowerValue >, KSTypeList< KSTypeInteger< XTemperaturePowerValue >, KSTypeList< KSTypeInteger< XIntensityPowerValue >, KSTypeList< KSTypeInteger< XAnglePowerValue >, KSTypeNull > > > > > > > > >::ConstructUnitSymbol();

    //**********************
    //scaled unit definition
    //**********************

    template< class XUnitType, class XTag >
    class KSScaledUnit;

    template< int XMassPowerValue, int XLengthPowerValue, int XTimePowerValue, int XChargePowerValue, int XTemperaturePowerValue, int XIntensityPowerValue, int XAnglePowerValue, class XTag >
    class KSScaledUnit< KSDimension< KSTYPELIST7( KSTypeInteger< XMassPowerValue >, KSTypeInteger< XLengthPowerValue >, KSTypeInteger< XTimePowerValue >, KSTypeInteger< XChargePowerValue >, KSTypeInteger< XTemperaturePowerValue >, KSTypeInteger< XIntensityPowerValue >, KSTypeInteger< XAnglePowerValue > ) >, XTag >
    {
        public:
            typedef KSDimension< KSTYPELIST7( KSTypeInteger< XMassPowerValue >, KSTypeInteger< XLengthPowerValue >, KSTypeInteger< XTimePowerValue >, KSTypeInteger< XChargePowerValue >, KSTypeInteger< XTemperaturePowerValue >, KSTypeInteger< XIntensityPowerValue >, KSTypeInteger< XAnglePowerValue > ) > Dimension;

        public:
            static const string fSymbol;
            static const double fScaleToThisUnitFromBaseUnit;
    };

    //**********************
    //offset unit definition
    //**********************

    template< class XUnitType, class XTag >
    class KSOffsetUnit;

    template< int XMassPowerValue, int XLengthPowerValue, int XTimePowerValue, int XChargePowerValue, int XTemperaturePowerValue, int XIntensityPowerValue, int XAnglePowerValue, class XTag >
    class KSOffsetUnit< KSDimension< KSTYPELIST7( KSTypeInteger< XMassPowerValue >, KSTypeInteger< XLengthPowerValue >, KSTypeInteger< XTimePowerValue >, KSTypeInteger< XChargePowerValue >, KSTypeInteger< XTemperaturePowerValue >, KSTypeInteger< XIntensityPowerValue >, KSTypeInteger< XAnglePowerValue > ) >, XTag >
    {
        public:
            typedef KSDimension< KSTYPELIST7( KSTypeInteger< XMassPowerValue >, KSTypeInteger< XLengthPowerValue >, KSTypeInteger< XTimePowerValue >, KSTypeInteger< XChargePowerValue >, KSTypeInteger< XTemperaturePowerValue >, KSTypeInteger< XIntensityPowerValue >, KSTypeInteger< XAnglePowerValue > ) > Dimension;

        public:
            static const string fSymbol;
            static const double fOffsetToThisUnitFromBaseUnit;
    };

    //**************
    //units typedefs
    //**************

    //unitless
    typedef KSUnit< KSDimensionless > KSUnitless;

    //base units
    typedef KSUnit< KSMassDimension > KSKilogram;
    typedef KSUnit< KSLengthDimension > KSMeter;
    typedef KSUnit< KSTimeDimension > KSSecond;
    typedef KSUnit< KSChargeDimension > KSCoulomb;
    typedef KSUnit< KSTemperatureDimension > KSKelvin;
    typedef KSUnit< KSIntensityDimension > KSCandela;
    typedef KSUnit< KSAngleDimension > KSRadian;

    //derived units
    typedef KSUnit< KSAreaDimension > KSSquareMeter;
    typedef KSUnit< KSVolumeDimension > KSCubicMeter;
    typedef KSUnit< KSFrequencyDimension > KSHertz;
    typedef KSUnit< KSAngularFrequencyDimension > KSRadianPerSecond;
    typedef KSUnit< KSVelocityDimension > KSMeterPerSecond;
    typedef KSUnit< KSAccelerationDimension > KSMeterPerSecondSquared;
    typedef KSUnit< KSMomentumDimension > KSKilogramMeterPerSecond;
    typedef KSUnit< KSForceDimension > KSNewton;
    typedef KSUnit< KSAngularMomentumDimension > KSKilogramMeterSquaredPerSecondPerRadian;
    typedef KSUnit< KSTorqueDimension > KSKilogramMeterSquaredPerSecondSquaredPerRadian;
    typedef KSUnit< KSEnergyDimension > KSJoule;
    typedef KSUnit< KSPowerDimension > KSJoulePerSecond;

    typedef KSUnit< KSElectricPotentialDimension > KSVolt;
    typedef KSUnit< KSElectricFieldDimension > KSVoltPerMeter;
    typedef KSUnit< KSMagneticPotentialDimension > KSTeslaMeter;
    typedef KSUnit< KSMagneticFieldDimension > KSTesla;
    typedef KSUnit< KSElectricPermittivityDimension > KSFaradPerMeter;
    typedef KSUnit< KSMagneticPermeabilityDimension > KSHenryPerMeter;

    typedef KSUnit< KSCurrentDimension > KSAmpere;
    typedef KSUnit< KSResistanceDimension > KSOhm;
    typedef KSUnit< KSInductanceDimension > KSHenry;
    typedef KSUnit< KSCapacitanceDimension > KSFarad;
    typedef KSUnit< KSMagneticFluxDimension > KSWeber;

    //scaled units
    class KSLiterTag;
    typedef KSScaledUnit< KSVolumeDimension, KSLiterTag > KSLiter;

    class KSElectronVoltTag;
    typedef KSScaledUnit< KSEnergyDimension, KSElectronVoltTag > KSElectronVolt;

    class KSGaussTag;
    typedef KSScaledUnit< KSMagneticFieldDimension, KSGaussTag > KSGauss;

    class KSDegreeTag;
    typedef KSScaledUnit< KSAngleDimension, KSDegreeTag > KSDegree;

    //offset units
    class KSCelsiusTag;
    typedef KSOffsetUnit< KSTemperatureDimension, KSCelsiusTag > KSCelsius;

}

#endif
