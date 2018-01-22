#ifndef PYTHONIC_OPERATOR_GT_HPP
#define PYTHONIC_OPERATOR_GT_HPP

#include "pythonic/include/operator_/gt.hpp"

#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace operator_
{
  template <class A, class B>
  auto gt(A const &a, B const &b) -> decltype(a > b)
  {
    return a > b;
  }

  DEFINE_FUNCTOR(pythonic::operator_, gt);
}
PYTHONIC_NS_END

#endif
