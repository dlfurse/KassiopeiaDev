#ifndef KSASSEMBLY_H_
#define KSASSEMBLY_H_

#include "KSGeometry.h"

#include <vector>
using std::vector;

namespace Kassiopeia
{
    class KSVolume;
    class KSAbstractVolume;

    class KSAssemblyPlacement;
    class KSVolumePlacement;
    class KSSurfacePlacement;

    class KSAssembly :
        public KSGeometry
    {
        public:
            KSAssembly();
            virtual ~KSAssembly();

            //**********
            //production
            //**********

        public:
            virtual void MakeAssembly( KSVolume** assembly ) const;

            virtual void SetAbstractVolume( const KSAbstractVolume* volume );
            virtual const KSAbstractVolume* GetAbstractVolume() const;

        protected:
            const KSAbstractVolume* fAbstractVolume;

            //**********
            //placements
            //**********

        public:
            virtual void AddChildAssemblyPlacement( KSAssemblyPlacement* placement );
            virtual void AddChildVolumePlacement( KSVolumePlacement* placement );
            virtual void AddChildSurfacePlacement( KSSurfacePlacement* placement );

            vector< KSAssemblyPlacement* > fAssemblyPlacements;
            vector< KSVolumePlacement* > fVolumePlacements;
            vector< KSSurfacePlacement* > fSurfacePlacements;
    };

}

/*!
 * @class Kassiopeia::KSAssemblyBuilder
 * @author N Oblath
 *
 * @brief this class builds an assembly
 */

/*
 namespace Kassiopeia
 {
 class KSGeometryToolbox;

 class KSAssemblyBuilder :
 public KSBuilderPrototype< KSGeometryToolbox, KSAssemblyBuilder >,
 public KSGeometryContainerBuilder
 {
 public:
 KSAssemblyBuilder();
 virtual ~KSAssemblyBuilder();

 virtual KSGeometryContainer* PassDownGeometryContainer() const;

 protected:
 virtual Bool_t ProcessBuilder( const KSBuilder* token );

 virtual Bool_t ProcessToken( const KSPseudoParameterToken* token );
 virtual Bool_t ProcessToken( const KSPseudoEndToken* token );

 virtual Bool_t ProcessToken( const KSXMLAttributeToken* token );
 virtual Bool_t ProcessToken( const KSXMLEndElementToken* token );

 virtual void AssignOpenTags();

 private:
 KSAssembly* fAssembly;
 };
 }
 */

#endif /* KSASSEMBLY_H_ */
