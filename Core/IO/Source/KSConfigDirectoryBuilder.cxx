#include "KSConfigDirectoryBuilder.h"
#include "KSIOToolboxBuilder.h"
#include "KSElement.h"

namespace Kassiopeia
{

    KSConfigDirectoryBuilder::KSConfigDirectoryBuilder() :
        fDirectories()
    {
    }

    KSConfigDirectoryBuilder::~KSConfigDirectoryBuilder()
    {
    }

    Bool_t KSConfigDirectoryBuilder::Start()
    {
        return kTRUE;
    }
    Bool_t KSConfigDirectoryBuilder::AddAttribute( KSTokenAttribute* anAttribute )
    {
        if( anAttribute->GetAttributeName() == "path" )
        {
            fDirectories.push_back( anAttribute->GetAttributeValue() );
            return kTRUE;
        }

        return kFALSE;
    }
    Bool_t KSConfigDirectoryBuilder::End()
    {
        vector< string >::iterator It;
        for( It = fDirectories.begin(); It != fDirectories.end(); It++ )
        {
            fToolbox->AddConfigUserDirectory(*It);
        }
        return kTRUE;
    }

    static KSElement< KSIOToolboxBuilder, KSConfigDirectoryBuilder > sConfigFileElement("config_directory");

}
