#ifndef KSROOTMAGNETICFIELD_H_
#define KSROOTMAGNETICFIELD_H_

#include "KSMagneticField.h"

namespace Kassiopeia
{

    class KSRootMagneticField :
            public KSMagneticField
        {
                //*********
                //singleton
                //*********

            public:
                static KSRootMagneticField* GetInstance();
                virtual ~KSRootMagneticField();

            private:
                KSRootMagneticField();
                static KSRootMagneticField* fInstance;

                //**************
                //field requests
                //**************

            public:
                virtual Bool_t GetA( TVector3& aTarget, const TVector3& aSamplePoint, const Double_t& aSampleTime );
                virtual Bool_t GetField( TVector3& aTarget, const TVector3& aSamplePoint, const Double_t& aSampleTime );
                virtual Bool_t GetFieldGradient( TMatrixT< Double_t >& aTarget, const TVector3& aSamplePoint, const Double_t& aSampleTime );

                //***********
                //composition
                //***********

            public:
                Bool_t AddMagneticField( KSMagneticField* aField );
                Bool_t RemoveMagneticField( KSMagneticField* aField );

            private:
                TVector3 fCurrentA;
                TVector3 fCurrentField;
                TMatrixT< Double_t > fCurrentGradient;

                enum
                {
                    eMaxCalculators = 32
                };
                KSMagneticField* fCalculators[eMaxCalculators];
                size_t fCurrentCalculator;
                size_t fEndCalculator;
        };

        inline Bool_t KSRootMagneticField::GetA( TVector3& aTarget, const TVector3& aSamplePoint, const Double_t& aSampleTime )
        {
            aTarget.SetXYZ(0.,0.,0.);
            for( fCurrentCalculator = 0; fCurrentCalculator < fEndCalculator; fCurrentCalculator++ )
            {
                if( fCalculators[fCurrentCalculator]->GetA( fCurrentA, aSamplePoint, aSampleTime ) == kFALSE )
                {
                    aTarget.SetXYZ(0.,0.,0.);
                    return kFALSE;
                }
                else
                {
                    aTarget += fCurrentA;
                }
            }
            return kTRUE;
        }
        inline Bool_t KSRootMagneticField::GetField( TVector3& aTarget, const TVector3& aSamplePoint, const Double_t& aSampleTime )
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
        inline Bool_t KSRootMagneticField::GetFieldGradient( TMatrixT< Double_t >& aTarget, const TVector3& aSamplePoint, const Double_t& aSampleTime )
        {
            aTarget.Zero();
            for( fCurrentCalculator = 0; fCurrentCalculator < fEndCalculator; fCurrentCalculator++ )
            {
                if( fCalculators[fCurrentCalculator]->GetFieldGradient( fCurrentGradient, aSamplePoint, aSampleTime ) == kFALSE )
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

        inline Bool_t KSRootMagneticField::AddMagneticField( KSMagneticField* aField )
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
        inline Bool_t KSRootMagneticField::RemoveMagneticField( KSMagneticField* aField )
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

#endif /* KSROOTMAGNETICFIELD_H_ */
