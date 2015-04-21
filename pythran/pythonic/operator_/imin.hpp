#ifndef PYTHONIC_OPERATOR_IMIN_HPP
#define PYTHONIC_OPERATOR_IMIN_HPP

#include "pythran/pythonic/include/operator_/imin.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/numpy/minimum.hpp"

namespace pythonic {

    namespace operator_ {

        template <class A, class B>
            auto imin(A const& a, B&& b) -> decltype(numpy::proxy::minimum{}(a, std::forward<B>(b)))
            {
                return numpy::proxy::minimum{}(a, std::forward<B>(b));
            }

        template <class A, class B>
            auto imin(A& a, B&& b) -> decltype( a = numpy::proxy::minimum{}(a, std::forward<B>(b)))
            {
                return a = numpy::proxy::minimum{}(a, std::forward<B>(b));
            }

        PROXY_IMPL(pythonic::operator_, imin);
    }

}

#endif
