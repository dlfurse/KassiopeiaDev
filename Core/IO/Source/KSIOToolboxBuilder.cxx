#include "KSIOToolboxBuilder.h"
#include "KSBuilderProcessor.h"
#include "KSElement.h"

namespace Kassiopeia
{

    KSIOToolboxBuilder::KSIOToolboxBuilder()
    {
    }

    KSIOToolboxBuilder::~KSIOToolboxBuilder()
    {
    }

    KSElement< KSBuilderProcessor, KSIOToolboxBuilder > sIOElement("io");

}
