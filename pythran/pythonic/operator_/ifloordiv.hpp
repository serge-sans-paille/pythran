#ifndef PYTHONIC_OPERATOR_IFLOORDIV_HPP
#define PYTHONIC_OPERATOR_IFLOORDIV_HPP

#include "pythonic/include/operator_/ifloordiv.hpp"
#include "pythonic/operator_/mod.hpp"

#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace operator_
{

  template <class A, class B>
  A &ifloordiv(A &a, B const &b)
  {
    a -= mod(a, b);
    a /= b;
    return a;
  }
  template <class A, class B>
  A ifloordiv(A const &a, B const &b)
  {
    return (a - mod(a, b)) / b;
  }
}
PYTHONIC_NS_END

#endif
