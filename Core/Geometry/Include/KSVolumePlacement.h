/*
 *  KSVolumePlacement.h
 *  Kassiopeia
 *
 *  Created by Noah Oblath on 6/22/11.
 *
 */

#ifndef KSVOLUMEPLACEMENT_H_
#define KSVOLUMEPLACEMENT_H_

#include "KSPlacement.h"

//#include "KSBuilderPrototype.h"

/*!
 * @class Kassiopeia::KSVolumePlacement
 * @author N Oblath
 *
 * @brief this is the base class for geometry placements
 */

namespace Kassiopeia
{
    class KSAbstractVolume;
    class KSVolume;

    class KSVolumePlacement :
        public KSPlacement
    {
        public:
            KSVolumePlacement();
            virtual ~KSVolumePlacement();

            virtual void MakeVolume( KSVolume** volume ) const;

            virtual void SetAbstractVolume( const KSAbstractVolume* volume );
            virtual const KSAbstractVolume* GetAbstractVolume() const;

        protected:
            const KSAbstractVolume* fAbstractVolume;
    };

}

/*!
 * @class Kassiopeia::KSVolumePlacementBuilder
 * @author N Oblath
 *
 * @brief this class builds a volume placement
 */

/*
namespace Kassiopeia
{
    class KSGeometryToolbox;
    class KSGeometryContainer;

    class KSVolumePlacementBuilder :
        public KSBuilderPrototype< KSGeometryToolbox, KSVolumePlacementBuilder >
        , public KSGeometryContainerBuilder
    {
        public:
            KSVolumePlacementBuilder();
            virtual ~KSVolumePlacementBuilder();

            virtual KSGeometryContainer* PassDownGeometryContainer() const;

        protected:
            virtual Bool_t ProcessBuilder( const KSBuilder* token );

            virtual Bool_t ProcessToken( const KSPseudoParameterToken* token );
            virtual Bool_t ProcessToken( const KSPseudoEndToken* token );

            virtual Bool_t ProcessToken( const KSXMLAttributeToken* token );
            virtual Bool_t ProcessToken( const KSXMLEndElementToken* token );

            virtual const KSGeometryContainerBuilder* GetParentGeometryContainerBuilder() const;
            virtual void AssignOpenTags();

        private:
            KSVolumePlacement* fPlacement;
            KSGeometryContainer* fParentContainer;
    };
}
*/

#endif /* KSVOLUMEPLACEMENT_H_ */
