#ifndef PYTHONIC_OPERATOR_MUL_HPP
#define PYTHONIC_OPERATOR_MUL_HPP

#include "pythonic/include/operator_/mul.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/operator_/overloads.hpp"

PYTHONIC_NS_BEGIN

namespace operator_
{

  template <class A, class B>
  auto mul(A const &a, B const &b) -> decltype(a *b)
  {
    return a * b;
  }

  DEFINE_ALL_OPERATOR_OVERLOADS_IMPL(mul, *)

  DEFINE_FUNCTOR(pythonic::operator_, mul);
}
PYTHONIC_NS_END

#endif
