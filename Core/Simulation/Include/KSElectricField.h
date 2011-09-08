#ifndef KSELECTRICFIELD_H_
#define KSELECTRICFIELD_H_

#include "Rtypes.h"

#include "TVector3.h"
#include "TMatrixT.h"

#include <string>
using std::string;

namespace Kassiopeia
{

    class KSElectricField
    {
            //*****************************
            //constructor, destructor, name
            //*****************************

        public:
            KSElectricField();
            virtual ~KSElectricField();

            void SetName( const string& aName );
            const string& GetName() const;

        protected:
            string fName;

            //***********************
            //field request interface
            //***********************

        public:
            virtual Bool_t GetPhi( Double_t& aTarget, const TVector3& aSamplePoint, const Double_t& aSampleTime ) = 0;
            virtual Bool_t GetField( TVector3& aTarget, const TVector3& aSamplePoint, const Double_t& aSampleTime ) = 0;
            virtual Bool_t GetGradient( TMatrixT< Double_t >& aTarget, const TVector3& aSamplePoint, const Double_t& aSampleTime ) = 0;
    };

    inline void KSElectricField::SetName( const string& aName )
    {
        fName = aName;
        return;
    }
    inline const string& KSElectricField::GetName() const
    {
        return fName;
    }

}

#endif
