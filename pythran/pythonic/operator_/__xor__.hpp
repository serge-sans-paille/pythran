#ifndef PYTHONIC_OPERATOR_XOR__HPP
#define PYTHONIC_OPERATOR_XOR__HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {
        template <class A, class B>
            auto __xor__(A const& a, B const& b) -> decltype(a^b) {
                return a^b;
            }
        PROXY(pythonic::operator_, __xor__);

    }

}

#endif

