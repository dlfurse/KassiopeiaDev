#ifndef KSCONFIGDIRECTORYBUILDER_H_
#define KSCONFIGDIRECTORYBUILDER_H_

#include "KSToolboxModuleBuilder.h"
#include "KSIOToolbox.h"

#include <vector>
using std::vector;

namespace Kassiopeia
{

    class KSConfigDirectoryBuilder :
        public KSToolboxModuleBuilder< KSIOToolbox, KSConfigDirectoryBuilder >
    {
        public:
            KSConfigDirectoryBuilder();
            virtual ~KSConfigDirectoryBuilder();

            virtual Bool_t Start();
            virtual Bool_t AddAttribute( KSTokenAttribute* anAttribute );
            virtual Bool_t End();

        private:
            vector< string > fDirectories;
    };

}

#endif
