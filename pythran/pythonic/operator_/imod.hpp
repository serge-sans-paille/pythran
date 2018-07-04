#ifndef PYTHONIC_OPERATOR_IMOD_HPP
#define PYTHONIC_OPERATOR_IMOD_HPP

#include "pythonic/include/operator_/imod.hpp"

#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace operator_
{
  template <class A, class B>
  A imod(A const &a, B const &b)
  {
    return a % b;
  }

  template <class A, class B>
  A &imod(A &a, B const &b)
  {
    return a %= b;
  }
}
PYTHONIC_NS_END

#endif
