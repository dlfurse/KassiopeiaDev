#ifndef KSPARTICLEFACTORY_H_
#define KSPARTICLEFACTORY_H_

#include "Rtypes.h"

#include "KSParticle.h"

namespace Kassiopeia
{

    class KSParticleFactory
    {
        public:
            KSParticleFactory( const Long_t pid, const Double_t mass, const Double_t charge, const Double_t totalspin, const Double_t lifetime );
            virtual ~KSParticleFactory();

            Long_t GetPID() const;

            KSParticle* Build() const;

        private:
            Long_t fPID;
            Double_t fMass;
            Double_t fCharge;
            Double_t fTotalSpin;
            Double_t fLifetime;
    };

}

#endif
