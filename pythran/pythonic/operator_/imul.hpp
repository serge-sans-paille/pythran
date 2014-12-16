#ifndef PYTHONIC_OPERATOR_IMUL_HPP
#define PYTHONIC_OPERATOR_IMUL_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {

        template <class A, class B>
            auto imul(A const& a, B&& b) -> decltype(a * std::forward<B>(b))
            {
                return a * std::forward<B>(b);
            }
        template <class A, class B>
            auto imul(A& a, B&& b) -> decltype( a*=std::forward<B>(b))
            {
                return a *= std::forward<B>(b);
            }
        PROXY(pythonic::operator_, imul);
    }

}

#endif

