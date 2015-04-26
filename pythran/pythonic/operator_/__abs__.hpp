#ifndef PYTHONIC_OPERATOR_ABS_HPP
#define PYTHONIC_OPERATOR_ABS_HPP

#include "pythonic/include/operator_/__abs__.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/__builtin__/abs.hpp"

namespace pythonic {

    namespace operator_ {

        template <class A>
            auto __abs__(A const& a) -> decltype(__builtin__::abs(a))
            {
                return __builtin__::abs(a);
            }

        PROXY_IMPL(pythonic::operator_, __abs__);

    }

}

#endif
