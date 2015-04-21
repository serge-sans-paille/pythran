#ifndef PYTHONIC_OPERATOR_XOR__HPP
#define PYTHONIC_OPERATOR_XOR__HPP

#include "pythran/pythonic/include/operator_/__xor__.hpp"

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {
        template <class A, class B>
            auto __xor__(A const& a, B const& b) -> decltype(a^b)
            {
                return a^b;
            }

        PROXY_IMPL(pythonic::operator_, __xor__);

    }

}

#endif
