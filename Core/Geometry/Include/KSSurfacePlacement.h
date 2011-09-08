/*
 *  KSSurfacePlacement.h
 *  Kassiopeia
 *
 *  Created by Noah Oblath on 6/22/11.
 *
 */

#ifndef KSSURFACEPLACEMENT_H_
#define KSSURFACEPLACEMENT_H_

#include "KSPlacement.h"

//#include "KSBuilderPrototype.h"

/*!
 * @class Kassiopeia::KSSurfacePlacement
 * @author N Oblath
 *
 * @brief this is the base class for surface placements
 */

namespace Kassiopeia
{
    class KSAbstractSurface;
    class KSSurface;

    class KSSurfacePlacement :
        public KSPlacement
    {
        public:
            KSSurfacePlacement();
            virtual ~KSSurfacePlacement();

            virtual void MakeSurface( KSSurface** surface ) const;

            void SetAbstractSurface( const KSAbstractSurface* surface );
            const KSAbstractSurface* GetAbstractSurface() const;

        protected:
            const KSAbstractSurface* fAbstractSurface;
    };

}

/*!
 * @class Kassiopeia::KSSurfacePlacementBuilder
 * @author N Oblath
 *
 * @brief this class builds a surface placement
 */

/*
namespace Kassiopeia
{
    class KSGeometryToolbox;
    class KSAssembly;
    class KSAbstractSurface;
    class KSGeometryContainer;
    class KSGeometryContainerBuilder;

    class KSSurfacePlacementBuilder :
        public KSBuilderPrototype< KSGeometryToolbox, KSSurfacePlacementBuilder >
    {
        public:
            KSSurfacePlacementBuilder();
            virtual ~KSSurfacePlacementBuilder();

        protected:
            virtual Bool_t ProcessToken( const KSPseudoParameterToken* token );
            virtual Bool_t ProcessToken( const KSPseudoEndToken* token );

            virtual Bool_t ProcessToken( const KSXMLAttributeToken* token );
            virtual Bool_t ProcessToken( const KSXMLEndElementToken* token );

            virtual const KSGeometryContainerBuilder* GetParentGeometryContainerBuilder() const;
            virtual void AssignOpenTags();

        private:
            KSSurfacePlacement* fPlacement;
            KSGeometryContainer* fParentContainer;
    };
}
*/

#endif /* KSSURFACEPLACEMENT_H_ */
