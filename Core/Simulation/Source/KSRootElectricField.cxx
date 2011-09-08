#include "KSRootElectricField.h"

namespace Kassiopeia
{

    KSRootElectricField* KSRootElectricField::fInstance = NULL;
    KSRootElectricField* KSRootElectricField::GetInstance()
    {
        if( fInstance == NULL )
        {
            fInstance = new KSRootElectricField();
        }
        return fInstance;
    }

    KSRootElectricField::KSRootElectricField() :
        fCurrentPhi( 0. ),
        fCurrentField( 0., 0., 0. ),
        fCurrentGradient( 3, 3 ),
        fCurrentCalculator( 0 ),
        fEndCalculator( 0 )
    {
        fCurrentGradient.Zero();

        for( size_t Index = 0; Index < eMaxCalculators; Index++ )
        {
            fCalculators[Index] = NULL;
        }
    }
    KSRootElectricField::~KSRootElectricField()
    {
    }

} /* namespace Kassiopeia */
