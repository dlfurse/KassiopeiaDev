/*
 *  KSPlacement.h
 *  Kassiopeia
 *
 *  Created by Noah Oblath on 6/22/11.
 *
 */

#ifndef KSPLACEMENT_H_
#define KSPLACEMENT_H_

#include "KSGeometry.h"

/*!
 * @class Kassiopeia::KSPlacement
 * @author N Oblath
 *
 * @brief this is the base class for geometry placements
 */

namespace Kassiopeia
{

    class KSTransformation;

    class KSPlacement :
        public KSGeometry
    {
        public:
            KSPlacement();
            virtual ~KSPlacement();

            virtual void SetTransformation( const KSTransformation* aTransformation );
            const KSTransformation* GetTransformation() const;

        protected:
            const KSTransformation* fTransformation;
    };

}

#endif /* KSPLACEMENT_H_ */
