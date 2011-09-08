#ifndef KSTYPECOMPARISON_H_
#define KSTYPECOMPARISON_H_

namespace Kassiopeia
{

    template< class XLeft, class XRight >
    class KSTypeEqual
    {
        public:
            enum
            {
                Value = 0
            };
    };

    template< class XMatch >
    class KSTypeEqual< XMatch, XMatch >
    {
        public:
            enum
            {
                Value = 1
            };
    };

    template< int XCondition, class XConditionMet, class XConditionNotMet >
    class KSTypeConditional;

    template< class XConditionMet, class XConditionNotMet >
    class KSTypeConditional< 1, XConditionMet, XConditionNotMet >
    {
        public:
            typedef XConditionMet Type;
    };

    template< class XConditionMet, class XConditionNotMet >
    class KSTypeConditional< 0, XConditionMet, XConditionNotMet >
    {
        public:
            typedef XConditionNotMet Type;
    };
}

#endif
