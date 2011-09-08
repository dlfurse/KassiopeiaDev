#include "KSTypeLists.h"
#include "KSTypeListOperations.h"

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::endl;

namespace Kassiopeia
{

    class First
    {
        public:
            First()
            {}
            ~First()
            {}

            static const string& GetTypeName()
            {
                return fTypeName;
            }

        private:
            static const string fTypeName;
    };
    const string First::fTypeName = string("First");

    class Second
    {
        public:
            Second()
            {}
            ~Second()
            {}

            static const string& GetTypeName()
            {
                return fTypeName;
            }

        private:
            static const string fTypeName;
    };
    const string Second::fTypeName = string("Second");

    class Third
    {
        public:
            Third()
            {}
            ~Third()
            {}

            static const string& GetTypeName()
            {
                return fTypeName;
            }

        private:
            static const string fTypeName;
    };
    const string Third::fTypeName = string("Third");

    class Fourth
    {
        public:
            Fourth()
            {}
            ~Fourth()
            {}

            static const string& GetTypeName()
            {
                return fTypeName;
            }

        private:
            static const string fTypeName;
    };
    const string Fourth::fTypeName = string("Fourth");

}


using namespace Kassiopeia;

int main()
{
    typedef KSTypeList< First, KSTypeList< Second, KSTypeList< Third, KSTypeNull > > > MyTypeList;
    cout << "KSTypeList created: KSTypeList< First, KSTypeList< Second, KSTypeList< Third, KSTypeNull > > >" << endl;

    cout << "name at position 0: " << endl;
    cout << KSAt< MyTypeList, 0 >::Type::GetTypeName() << endl;
    cout << endl;

    cout << "name at position 1: " << endl;
    cout << KSAt< MyTypeList, 1 >::Type::GetTypeName() << endl;
    cout << endl;

    cout << "name at position 2: " << endl;
    cout << KSAt< MyTypeList, 2 >::Type::GetTypeName() << endl;
    cout << endl;

    typedef KSInsert< Fourth, MyTypeList, 1 >::Type MyExtendedTypeList;
    cout << "KSTypeList created: KSInsert< Fourth, MyTypeList, 1 >::Type" << endl;

    cout << "name at position 0: " << endl;
    cout << KSAt< MyExtendedTypeList, 0 >::Type::GetTypeName() << endl;
    cout << endl;

    cout << "name at position 1: " << endl;
    cout << KSAt< MyExtendedTypeList, 1 >::Type::GetTypeName() << endl;
    cout << endl;

    cout << "name at position 2: " << endl;
    cout << KSAt< MyExtendedTypeList, 2 >::Type::GetTypeName() << endl;
    cout << endl;

    cout << "name at position 3: " << endl;
    cout << KSAt< MyExtendedTypeList, 3 >::Type::GetTypeName() << endl;
    cout << endl;

    typedef KSTYPELIST2( Fourth, First ) MyInsertedTypeList;
    typedef KSInsert< MyInsertedTypeList, MyTypeList, 1 >::Type MyOtherExtendedTypeList;
    cout << "KSTypeList created: KSInsert< TypeList2(Fourth,First), MyTypeList, 1 >::Type" << endl;

    cout << "name at position 0: " << endl;
    cout << KSAt< MyOtherExtendedTypeList, 0 >::Type::GetTypeName() << endl;
    cout << endl;

    cout << "name at position 1: " << endl;
    cout << KSAt< MyOtherExtendedTypeList, 1 >::Type::GetTypeName() << endl;
    cout << endl;

    cout << "name at position 2: " << endl;
    cout << KSAt< MyOtherExtendedTypeList, 2 >::Type::GetTypeName() << endl;
    cout << endl;

    cout << "name at position 3: " << endl;
    cout << KSAt< MyOtherExtendedTypeList, 3 >::Type::GetTypeName() << endl;
    cout << endl;

    cout << "name at position 4: " << endl;
    cout << KSAt< MyOtherExtendedTypeList, 4 >::Type::GetTypeName() << endl;
    cout << endl;

    return 0;
}




