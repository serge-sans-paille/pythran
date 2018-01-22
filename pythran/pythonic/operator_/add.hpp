#ifndef PYTHONIC_OPERATOR_ADD_HPP
#define PYTHONIC_OPERATOR_ADD_HPP

#include "pythonic/include/operator_/add.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/operator_/overloads.hpp"

PYTHONIC_NS_BEGIN

namespace operator_
{
  template <class A, class B>
  auto add(A const &a, B const &b) -> decltype(a + b)
  {
    return a + b;
  }

  DEFINE_ALL_OPERATOR_OVERLOADS_IMPL(add, +)

  DEFINE_FUNCTOR(pythonic::operator_, add);
}
PYTHONIC_NS_END

#endif
