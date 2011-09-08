#include "KSBuilderFactoryTable.h"

#include "KLMessage.h"


namespace Kassiopeia
{

    KSBuilderFactoryTable::KSBuilderFactoryTable() :
        fBuilders( BuilderList() ), fBuildIt(fBuilders.begin())
    {
    }
    KSBuilderFactoryTable::~KSBuilderFactoryTable()
    {
    }

    void KSBuilderFactoryTable::Register( const KSBuilderFactory* const factory )
    {
        #ifdef DEBUG_VERBOSE
		klmsg < "KSBuilderFactoryTable::Register";
		klmsg(KLMessage::eInitDebug) <<  "Registering a builder factory called <" << factory->GetTypeName() << "> for system <" << factory->GetSystemName() << ">" << eom;
		#endif

		fBuilders.push_back(factory);
        return;
    }

    const KSBuilderFactoryTable::BuilderMap* KSBuilderFactoryTable::GetMap( const string& systemname ) const
    {
        BuilderMap* Map = new BuilderMap();

        for( fBuildIt = fBuilders.begin(); fBuildIt != fBuilders.end(); fBuildIt++ )
        {
            if( (*fBuildIt)->GetSystemName() == systemname )
            {
                Map->insert(BuilderEntry((*fBuildIt)->GetTypeName(),*fBuildIt));
            }
        }

        return Map;
    }

    KSBuilderFactoryTable* KSBuilderFactoryTable::fInstance = 0;
    KSBuilderFactoryTable* KSBuilderFactoryTable::GetInstance()
    {
        if( fInstance == 0 )
        {
            fInstance = new KSBuilderFactoryTable();
        }
        return fInstance;
    }

} // end namespace Kassiopeia
