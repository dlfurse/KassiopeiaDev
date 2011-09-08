#ifndef KTRACKODE_H_
#define KTRACKODE_H_

#include "KMathODE.h"

#include "KTrackParticle.h"

namespace Kassiopeia
{

    class KTrackODE :
        public KMathODE
    {
        public:
            KTrackODE( const size_t& aDimension );
            virtual ~KTrackODE();

        private:
            KTrackODE();
            KTrackODE( const KTrackODE& );

        public:
            void SetParticle( KTrackParticle* aParticle );

        protected:
            KTrackParticle* fParticle;

        private:
            virtual void SetConditionAreaAction();
            virtual void SetDerivativeAreaAction();
    };

    inline void KTrackODE::SetParticle( KTrackParticle* aParticle )
    {
        fParticle = aParticle;
        return;
    }

    inline void KTrackODE::SetConditionAreaAction()
    {
        fParticle->SetData( fConditionArea );
        return;
    }
    inline void KTrackODE::SetDerivativeAreaAction()
    {
        return;
    }

}

#endif
