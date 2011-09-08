#ifndef KSGEOMETRYTOOLBOX_H_
#define KSGEOMETRYTOOLBOX_H_

#include "KSGeometry.h"

#include <string>
using std::string;

#include <stack>
using std::stack;

#include <vector>
using std::vector;

#include <set>
using std::set;

#include <map>
using std::map;

namespace Kassiopeia
{

    class KSShape;
    class KSSurface;
    class KSVolume;
    class KSAbstractSurface;
    class KSAbstractVolume;
    class KSAssembly;

    class KSGeometryToolbox
    {
        public:
            KSGeometryToolbox();
            virtual ~KSGeometryToolbox();

            //********************
            //standard toolboxness
            //********************

            void SetupManager();
            void PrepareManager();
            void ShutdownManager();

            virtual const string& GetTypeName() const;
            static const string& GetStaticTypeName();

        private:
            static const string fTypeName;

            //**************************************************
            //abstract surfaces, abstract volumes and assemblies
            //**************************************************
        private:
            typedef map< string, const KSAbstractSurface* > ASMap;
            typedef ASMap::value_type ASEntry;
            typedef ASMap::iterator ASIt;
            typedef ASMap::const_iterator ASCIt;

            typedef map< string, const KSAbstractVolume* > AVMap;
            typedef AVMap::value_type AVEntry;
            typedef AVMap::iterator AVIt;
            typedef AVMap::const_iterator AVCIt;

            typedef map< string, const KSAssembly* > AMap;
            typedef AMap::value_type AEntry;
            typedef AMap::iterator AIt;
            typedef AMap::const_iterator ACIt;

        public:
            void AddAbstractSurface( const KSAbstractSurface* aSurface );
            const KSAbstractSurface* GetAbstractSurface( const string& aName ) const;

            void AddAbstractVolume( const KSAbstractVolume* aVolume );
            const KSAbstractVolume* GetAbstractVolume( const string& aName ) const;

            void AddAssembly( const KSAssembly* anAssembly );
            const KSAssembly* GetAssembly( const string& aName ) const;

        private:
            ASMap fASMap;
            AVMap fAVMap;
            AMap fAMap;

            //**************
            //tagging system
            //**************

        private:
            typedef vector< KSShape* > TagGroup;
            typedef TagGroup::iterator TagGroupIt;
            typedef TagGroup::iterator TagGroupCIt;

            typedef map< KSGeometry::Tag, TagGroup* > TagGroupMap;
            typedef TagGroupMap::value_type TagGroupMapEntry;
            typedef TagGroupMap::iterator TagGroupMapIt;
            typedef TagGroupMap::const_iterator TagGroupMapCIt;

        public:
            const TagGroup* GetTag( const string& aTag ) const;

        private:
            TagGroupMap fTagGroupMap;

            //***************************************
            //surfaces, volumes, and the world volume
            //***************************************

        public:
            void SetWorldVolume( KSVolume* aWorldVolume );
            KSSurface* GetSurface( const string& aFullName ) const;
            KSVolume* GetVolume( const string& aFullName ) const;
            KSVolume* GetWorldVolume() const;

        private:
            KSVolume* fWorldVolume;

            void AddShape( KSShape* aShape );
            void AddSurface( KSSurface* aSurface );
            void AddVolume( KSVolume* aVolume );
            KSSurface* FindSurface( KSVolume* aCurrentVolume, const string& aFullName ) const;
            KSVolume* FindVolume( KSVolume* aCurrentVolume, const string& aFullName ) const;

    };

}

#endif
