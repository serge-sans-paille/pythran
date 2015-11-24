#ifndef PYTHONIC_OPERATOR_EQ_HPP
#define PYTHONIC_OPERATOR_EQ_HPP

#include "pythonic/include/operator_/eq.hpp"

#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace operator_
  {
    template <class A, class B>
    auto eq(A const &a, B const &b) -> decltype(a == b)
    {
      return a == b;
    }

    DEFINE_FUNCTOR(pythonic::operator_, eq);
  }
}

#endif
