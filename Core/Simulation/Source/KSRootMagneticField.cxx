/*
 * KSRootMagneticField.cxx
 *
 * created on: 04.08.2011
 * author: furse
 */

#include "KSRootMagneticField.h"

namespace Kassiopeia
{

    KSRootMagneticField* KSRootMagneticField::fInstance = NULL;
    KSRootMagneticField* KSRootMagneticField::GetInstance()
    {
        if( fInstance == NULL )
        {
            fInstance = new KSRootMagneticField();
        }
        return fInstance;
    }

    KSRootMagneticField::KSRootMagneticField() :
        fCurrentA( 0., 0., 0. ),
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
    KSRootMagneticField::~KSRootMagneticField()
    {
    }

} /* namespace Kassiopeia */
