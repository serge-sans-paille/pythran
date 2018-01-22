#ifndef PYTHONIC_OPERATOR_IPOW_HPP
#define PYTHONIC_OPERATOR_IPOW_HPP

#include "pythonic/include/operator_/ipow.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/__builtin__/pow.hpp"

PYTHONIC_NS_BEGIN

namespace operator_
{

  template <class A, class B>
  A ipow(A a, B const &b)
  {
    return a = __builtin__::pow(a, b);
  }

  DEFINE_FUNCTOR(pythonic::operator_, ipow);
}
PYTHONIC_NS_END

#endif
