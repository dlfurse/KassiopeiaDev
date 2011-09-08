#ifndef KSROOTELECTRICFIELD_H_
#define KSROOTELECTRICFIELD_H_

#include "KSElectricField.h"

namespace Kassiopeia
{

    class KSRootElectricField :
        public KSElectricField
    {
            //*********
            //singleton
            //*********

        public:
            static KSRootElectricField* GetInstance();
            virtual ~KSRootElectricField();

        private:
            KSRootElectricField();
            static KSRootElectricField* fInstance;

            //**************
            //field requests
            //**************

        public:
            virtual Bool_t GetPhi( Double_t& aTarget, const TVector3& aSamplePoint, const Double_t& aSampleTime );
            virtual Bool_t GetField( TVector3& aTarget, const TVector3& aSamplePoint, const Double_t& aSampleTime );
            virtual Bool_t GetGradient( TMatrixT< Double_t >& aTarget, const TVector3& aSamplePoint, const Double_t& aSampleTime );

            //***********
            //composition
            //***********

        public:
            Bool_t AddElectricField( KSElectricField* aField );
            Bool_t RemoveElectricField( KSElectricField* aField );

        private:
            Double_t fCurrentPhi;
            TVector3 fCurrentField;
            TMatrixT< Double_t > fCurrentGradient;

            enum
            {
                eMaxCalculators = 32
            };
            KSElectricField* fCalculators[eMaxCalculators];
            size_t fCurrentCalculator;
            size_t fEndCalculator;
    };

    inline Bool_t KSRootElectricField::GetPhi( Double_t& aTarget, const TVector3& aSamplePoint, const Double_t& aSampleTime )
    {
        aTarget = 0.;
        for( fCurrentCalculator = 0; fCurrentCalculator < fEndCalculator; fCurrentCalculator++ )
        {
            if( fCalculators[fCurrentCalculator]->GetPhi( fCurrentPhi, aSamplePoint, aSampleTime ) == kFALSE )
            {
                aTarget = 0.;
                return kFALSE;
            }
            else
            {
                aTarget += fCurrentPhi;
            }
        }
        return kTRUE;
    }
    inline Bool_t KSRootElectricField::GetField( TVector3& aTarget, const TVector3& aSamplePoint, const Double_t& aSampleTime )
    {
        aTarget.SetXYZ( 0., 0., 0. );
        for( fCurrentCalculator = 0; fCurrentCalculator < fEndCalculator; fCurrentCalculator++ )
        {
            if( fCalculators[fCurrentCalculator]->GetField( fCurrentField, aSamplePoint, aSampleTime ) == kFALSE )
            {
                aTarget.SetXYZ( 0., 0., 0. );
                return kFALSE;
            }
            else
            {
                aTarget += fCurrentField;
            }
        }
        return kTRUE;
    }
    inline Bool_t KSRootElectricField::GetGradient( TMatrixT< Double_t >& aTarget, const TVector3& aSamplePoint, const Double_t& aSampleTime )
    {
        aTarget.Zero();
        for( fCurrentCalculator = 0; fCurrentCalculator < fEndCalculator; fCurrentCalculator++ )
        {
            if( fCalculators[fCurrentCalculator]->GetGradient( fCurrentGradient, aSamplePoint, aSampleTime ) == kFALSE )
            {
                aTarget.Zero();
                return kFALSE;
            }
            else
            {
                aTarget += fCurrentGradient;
            }
        }
        return kTRUE;
    }

    inline Bool_t KSRootElectricField::AddElectricField( KSElectricField* aField )
    {
        if( fEndCalculator == eMaxCalculators )
        {
            return kFALSE;
        }
        fCurrentCalculator = fEndCalculator;
        fCalculators[fCurrentCalculator] = aField;
        fEndCalculator++;
        return kTRUE;
    }
    inline Bool_t KSRootElectricField::RemoveElectricField( KSElectricField* aField )
    {
        Bool_t CalculatorFound = kFALSE;
        for( fCurrentCalculator = 0; fCurrentCalculator < fEndCalculator; fCurrentCalculator++ )
        {
            if( CalculatorFound == kFALSE )
            {
                if( fCalculators[fCurrentCalculator] == aField )
                {
                    fCalculators[fCurrentCalculator] = NULL;
                    CalculatorFound = kTRUE;
                }
                continue;
            }
            fCalculators[fCurrentCalculator - 1] = fCalculators[fCurrentCalculator];
        }

        if( CalculatorFound == kTRUE )
        {
            fEndCalculator--;
            fCalculators[fEndCalculator] = NULL;
            return kTRUE;
        }

        return kFALSE;
    }

} /* namespace Kassiopeia */
#endif /* KSROOTELECTRICFIELD_H_ */
