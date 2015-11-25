#ifndef PYTHONIC_INCLUDE_OPERATOR_IMAX_HPP
#define PYTHONIC_INCLUDE_OPERATOR_IMAX_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/numpy/maximum.hpp"

namespace pythonic
{

  namespace operator_
  {
    template <class A, class B>
    auto imax(A const &a, B &&b)
        -> decltype(numpy::functor::maximum{}(a, std::forward<B>(b)));

    template <class A, class B>
    auto imax(A &a, B &&b)
        -> decltype(a = numpy::functor::maximum{}(a, std::forward<B>(b)));

    DECLARE_FUNCTOR(pythonic::operator_, imax);
  }
}

#endif
