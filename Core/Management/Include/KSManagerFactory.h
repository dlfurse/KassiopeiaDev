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
            KSManagerFactory( const string& aKey, KSManager* (*aConstructor)() );
            virtual ~KSManagerFactory();

        private:
            KSManagerFactory();

            //**************
            //identification
            //**************

        public:
            const string& GetManagerKey() const;

        protected:
            string fKey;

            //************
            //construction
            //************

        public:
            virtual KSManager* BuildManager() const ;

        protected:
            KSManager* (*fConstructor)();
    };

}

#endif
