/*
 *  KSAssemblyPlacement.h
 *  Kassiopeia
 *
 *  Created by Noah Oblath on 6/22/11.
 *
 */

#ifndef KSASSEMBLYPLACEMENT_H_
#define KSASSEMBLYPLACEMENT_H_

#include "KSPlacement.h"

//#include "KSBuilderPrototype.h"

/*!
 * @class Kassiopeia::KSAssemblyPlacement
 * @author N Oblath
 *
 * @brief this is the class for assembly placements
 */

namespace Kassiopeia
{
    class KSAssembly;
    class KSVolume;

    class KSAssemblyPlacement :
        public KSPlacement
    {
        public:
            KSAssemblyPlacement();
            virtual ~KSAssemblyPlacement();

            //**********
            //placements
            //**********

            virtual void MakeAssembly( KSVolume** volume ) const;

            virtual void SetAssembly( const KSAssembly* assembly );
            virtual const KSAssembly* GetAssembly() const;

        protected:
            const KSAssembly* fAssembly;
    };

}

/*!
 * @class Kassiopeia::KSAssemblyPlacementBuilder
 * @author N Oblath
 *
 * @brief this class builds an assembly placement
 */

/*
namespace Kassiopeia
{
    class KSGeometryToolbox;
    //class KSGeometryContainer;

    class KSAssemblyPlacementBuilder :
        public KSBuilderPrototype< KSGeometryToolbox, KSAssemblyPlacementBuilder >
        , public KSGeometryContainerBuilder
    {
        public:
            KSAssemblyPlacementBuilder();
            virtual ~KSAssemblyPlacementBuilder();

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
            KSAssemblyPlacement* fPlacement;
            KSGeometryContainer* fParentContainer;
    };
}
*/

#endif /* KSASSEMBLYPLACEMENT_H_ */
