#ifndef KSBuilderFactoryTable_h
#define KSBuilderFactoryTable_h

/*!
 * @class Kassiopeia::KSBuilderFactoryTable
 @author D. Furse

 @brief lookup table for all builder factories

 @details
 <b>Detailed Description:</b><br>



 <b>Revision History:</b>
 \verbatim
 Date       Name          Brief description
 -----------------------------------------------
 13 Jul 2010  D. Furse      first version
 \endverbatim

 */


#include "KSBuilderFactory.h"

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <map>
using std::map;

namespace Kassiopeia
{

    class KSBuilderFactoryTable
    {
        public:
            typedef map< string, const KSBuilderFactory* > BuilderMap;
            typedef BuilderMap::value_type BuilderEntry;

            typedef vector< const KSBuilderFactory* > BuilderList;
            typedef BuilderList::const_iterator BuilderIt;

        public:
            static KSBuilderFactoryTable* GetInstance();
            virtual ~KSBuilderFactoryTable();

            void Register( const KSBuilderFactory* const factory );
            const BuilderMap* GetMap( const string& systemname ) const;

        private:
            KSBuilderFactoryTable();

            BuilderList fBuilders;
            mutable BuilderList::const_iterator fBuildIt;

            static KSBuilderFactoryTable* fInstance;
    };

} // end namespace Kassiopeia

#endif // end ifndef KSBuilderFactoryTable_h
