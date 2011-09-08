#ifndef KSGEOMETRY_H_
#define KSGEOMETRY_H_

#include <string>
using std::string;

#include <set>
using std::set;

namespace Kassiopeia
{

    class KSGeometry
    {
        public:
            KSGeometry();
            virtual ~KSGeometry();

            //*********************
            //identification system
            //*********************

        public:
            static const string fNameSeparator;

        public:
            void SetName( const string& aName );
            const string& GetName() const;

        protected:
            string fName;


        public:
            typedef string Tag;
            typedef set< string > TagSet;
            typedef TagSet::iterator TagSetIt;
            typedef TagSet::const_iterator TagSetCIt;

        public:
            void AddTag( const Tag& aTag );
            void ClearTags();

            void AddTagSet( const TagSet* aTagSet );
            const TagSet* GetTagSet() const;

        protected:
            TagSet* fTagSet;
    };

}
#endif
