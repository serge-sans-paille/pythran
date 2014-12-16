#ifndef PYTHONIC_OPERATOR_IMAX_HPP
#define PYTHONIC_OPERATOR_IMAX_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/numpy/maximum.hpp"

namespace pythonic {

    namespace operator_ {
        template <class A, class B>
            auto imax(A const& a, B&& b) -> decltype(numpy::proxy::maximum{}(a, std::forward<B>(b)))
            {
              return numpy::proxy::maximum{}(a, std::forward<B>(b));
            }

        template <class A, class B>
            auto imax(A& a, B&& b) -> decltype( a = numpy::proxy::maximum{}(a, std::forward<B>(b)))
            {
                return a = numpy::proxy::maximum{}(a, std::forward<B>(b));
            }
        PROXY(pythonic::operator_, imax);
    }

}

#endif

