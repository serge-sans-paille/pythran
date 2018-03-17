#ifndef PYTHONIC_OPERATOR_IFLOORDIV_HPP
#define PYTHONIC_OPERATOR_IFLOORDIV_HPP

#include "pythonic/include/operator_/ifloordiv.hpp"

#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace operator_
{

  template <class A, class B>
  A &ifloordiv(A &a, B const &b)
  {
    a -= a % b;
    a /= b;
    return a;
  }
  template <class A, class B>
  A ifloordiv(A const &a, B const &b)
  {
    return (a - a % b) / b;
  }

  DEFINE_FUNCTOR(pythonic::operator_, ifloordiv);
}
PYTHONIC_NS_END

#endif
