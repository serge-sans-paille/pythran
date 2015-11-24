#ifndef PYTHONIC_OPERATOR_IMAX_HPP
#define PYTHONIC_OPERATOR_IMAX_HPP

#include "pythonic/include/operator_/imax.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/numpy/maximum.hpp"

namespace pythonic
{

  namespace operator_
  {
    template <class A, class B>
    auto imax(A const &a, B &&b)
        -> decltype(numpy::functor::maximum{}(a, std::forward<B>(b)))
    {
      return numpy::functor::maximum{}(a, std::forward<B>(b));
    }

    template <class A, class B>
    auto imax(A &a, B &&b)
        -> decltype(a = numpy::functor::maximum{}(a, std::forward<B>(b)))
    {
      return a = numpy::functor::maximum{}(a, std::forward<B>(b));
    }

    DEFINE_FUNCTOR(pythonic::operator_, imax);
  }
}

#endif
