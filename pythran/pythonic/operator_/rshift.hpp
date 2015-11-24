#ifndef PYTHONIC_OPERATOR_RSHIFT_HPP
#define PYTHONIC_OPERATOR_RSHIFT_HPP

#include "pythonic/include/operator_/rshift.hpp"

#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace operator_
  {
    template <class A, class B>
    auto rshift(A const &a, B const &b) -> decltype(a >> b)
    {
      return a >> b;
    }

    DEFINE_FUNCTOR(pythonic::operator_, rshift);
  }
}

#endif
