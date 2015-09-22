#ifndef PYTHONIC_INCLUDE_OPERATOR_IMIN_HPP
#define PYTHONIC_INCLUDE_OPERATOR_IMIN_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/numpy/minimum.hpp"

namespace pythonic
{

  namespace operator_
  {

    template <class A, class B>
    auto imin(A const &a, B &&b)
        -> decltype(numpy::proxy::minimum{}(a, std::forward<B>(b)));

    template <class A, class B>
    auto imin(A &a, B &&b)
        -> decltype(a = numpy::proxy::minimum{}(a, std::forward<B>(b)));

    PROXY_DECL(pythonic::operator_, imin);
  }
}

#endif
