#include "KSGeometry.h"

namespace Kassiopeia
{

    const string KSGeometry::fNameSeparator = string(":");

    KSGeometry::KSGeometry() :
        fName( "(anonymous)" ),
        fTagSet( new TagSet() )
    {
    }
    KSGeometry::~KSGeometry()
    {
        ClearTags();
    }

    void KSGeometry::SetName( const string& aName )
    {
        fName = aName;
        return;
    }
    const string& KSGeometry::GetName() const
    {
        return fName;
    }

    void KSGeometry::AddTag( const Tag& aTag )
    {
        fTagSet->insert( aTag );
        return;
    }
    void KSGeometry::AddTagSet( const TagSet* aTagSet )
    {
        TagSetCIt It;
        for( It = aTagSet->begin(); It != aTagSet->end(); It++ )
        {
            fTagSet->insert( *It );
        }
        return;
    }
    const KSGeometry::TagSet* KSGeometry::GetTagSet() const
    {
        return fTagSet;
    }

    void KSGeometry::ClearTags()
    {
        if( fTagSet != NULL )
        {
            delete fTagSet;
            fTagSet = NULL;
        }
        return;
    }

} /* namespace Kassiopeia */
