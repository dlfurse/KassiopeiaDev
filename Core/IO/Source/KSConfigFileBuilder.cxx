#include "KSConfigFileBuilder.h"
#include "KSIOToolboxBuilder.h"
#include "KSElement.h"

namespace Kassiopeia
{

    KSConfigFileBuilder::KSConfigFileBuilder() :
        fTextFile( NULL )
    {
    }

    KSConfigFileBuilder::~KSConfigFileBuilder()
    {
    }

    Bool_t KSConfigFileBuilder::Start()
    {
        fTextFile = new KSTextFile();
        return kTRUE;
    }
    Bool_t KSConfigFileBuilder::AddAttribute( KSTokenAttribute* anAttribute )
    {
        if( anAttribute->GetAttributeName() == "key" )
        {
            fTextFile->SetKey( anAttribute->GetAttributeValue() );
            return kTRUE;
        }

        if( anAttribute->GetAttributeName() == "base" )
        {
            fTextFile->AddToBases( anAttribute->GetAttributeValue() );
            return kTRUE;
        }

        if( anAttribute->GetAttributeName() == "path" )
        {
            fTextFile->AddToPaths( anAttribute->GetAttributeValue() );
            return kTRUE;
        }

        if( anAttribute->GetAttributeName() == "name" )
        {
            fTextFile->AddToNames( anAttribute->GetAttributeValue() );
            return kTRUE;
        }

        return kFALSE;
    }
    Bool_t KSConfigFileBuilder::End()
    {
        fToolbox->AddConfigTextFile( fTextFile );
        return kTRUE;
    }

    static KSElement< KSIOToolboxBuilder, KSConfigFileBuilder > sConfigFileElement("config_file");

}
