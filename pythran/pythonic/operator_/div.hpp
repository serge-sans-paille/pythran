#ifndef PYTHONIC_OPERATOR_DIV_HPP
#define PYTHONIC_OPERATOR_DIV_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/operator_/overloads.hpp"
#ifdef USE_BOOST_SIMD
#include <nt2/include/functions/divides.hpp>
#endif

namespace pythonic {

    namespace operator_ {
        template <class A, class B>
            auto div(A && a, B && b) -> decltype(std::forward<A>(a)/std::forward<B>(b)) {
                return std::forward<A>(a)/std::forward<B>(b);
            }
        DEFINE_ALL_OPERATOR_OVERLOADS(div,/)
        PROXY(pythonic::operator_, div);

    }

}

#endif

