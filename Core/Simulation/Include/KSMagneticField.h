#ifndef KSMAGNETICFIELD_H_
#define KSMAGNETICFIELD_H_

#include "Rtypes.h"

#include "TVector3.h"
#include "TMatrixT.h"

#include <string>
using std::string;

namespace Kassiopeia
{

    class KSMagneticField
    {
            //*****************************
            //constructor, destructor, name
            //*****************************

        public:
            KSMagneticField();
            virtual ~KSMagneticField();

            void SetName( const string& aName );
            const string& GetName() const;

        protected:
            string fName;

            //***********************
            //field request interface
            //***********************

        public:
            virtual Bool_t GetA( TVector3& aTarget, const TVector3& aSamplePoint, const Double_t& aSampleTime ) = 0;
            virtual Bool_t GetField( TVector3& aTarget, const TVector3& aSamplePoint, const Double_t& aSampleTime ) = 0;
            virtual Bool_t GetFieldGradient( TMatrixT< Double_t >& aTarget, const TVector3& aSamplePoint, const Double_t& aSampleTime ) = 0;
    };

    inline void KSMagneticField::SetName( const string& aName )
    {
        fName = aName;
        return;
    }

    inline const string& KSMagneticField::GetName() const
    {
        return fName;
    }

}

#endif
