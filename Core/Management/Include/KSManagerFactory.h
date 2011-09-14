#ifndef KSMANAGERFACTORY_H_
#define KSMANAGERFACTORY_H_

#include <string>
using std::string;

namespace Kassiopeia
{

    class KSManager;

    class KSManagerFactory
    {
        public:
            KSManagerFactory();
            virtual ~KSManagerFactory();

            virtual KSManager* Build() const = 0;
            virtual const string& GetTypeName() const = 0;
    };

    template< class XManagerType >
    class KSManagerFactoryPrototype
    {
        public:
            KSManagerFactoryPrototype()
            {
            }
            virtual ~KSManagerFactoryPrototype()
            {
            }

            virtual KSManager* Build() const
            {
                return new XManagerType();
            }

            virtual const string& GetTypeName() const
            {
                return XManagerType::fTypeName;
            }
    };

}

#endif
