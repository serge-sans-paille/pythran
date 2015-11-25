#ifndef PYTHONIC_OPERATOR_CONTAINS_HPP
#define PYTHONIC_OPERATOR_CONTAINS_HPP

#include "pythonic/include/operator_/contains.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/__builtin__/in.hpp"

namespace pythonic
{

  namespace operator_
  {
    template <class A, class B>
    auto contains(A const &a, B const &b) -> decltype(in(a, b))
    {
      return in(a, b);
    }

    DEFINE_FUNCTOR(pythonic::operator_, contains);
  }
}

#endif
