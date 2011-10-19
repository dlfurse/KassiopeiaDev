#ifndef KSCONFIGFILEBUILDER_H_
#define KSCONFIGFILEBUILDER_H_

#include "KSToolboxModuleBuilder.h"
#include "KSIOToolbox.h"

#include "KSTextFile.h"

namespace Kassiopeia
{

    class KSConfigFileBuilder :
        public KSToolboxModuleBuilder< KSIOToolbox, KSConfigFileBuilder >
    {
        public:
            KSConfigFileBuilder();
            virtual ~KSConfigFileBuilder();

            virtual Bool_t Start();
            virtual Bool_t AddAttribute( KSTokenAttribute* anAttribute );
            virtual Bool_t End();

        private:
            KSTextFile* fTextFile;
    };

}

#endif
