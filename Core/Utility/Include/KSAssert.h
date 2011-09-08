#ifndef KSSTATICASSERT_H_
#define KSSTATICASSERT_H_

namespace Kassiopeia
{

    template< bool XAssertion >
    class KSAssertion
    {
        public:
            enum{ Value = -1 };
    };

    template< >
    class KSAssertion< true >
    {
        public:
            enum{ Value = 1 };
    };

}

#define KSASSERT(anAssertion, aMessage) typedef bool ASSERTION_FAILED_##aMessage [ ::Kassiopeia::KSAssertion< ((anAssertion) == 0 ? false : true) >::Value ];

#endif
