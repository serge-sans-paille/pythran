#ifndef PYTHONIC_OPERATOR_EQ_HPP
#define PYTHONIC_OPERATOR_EQ_HPP

#include "pythonic/include/operator_/eq.hpp"

#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace operator_
{
  template <class A, class B>
  auto eq(A const &a, B const &b) -> decltype(a == b)
  {
    return a == b;
  }

  bool eq(char const *a, char const *b)
  {
    return strcmp(a, b) == 0;
  }
}
PYTHONIC_NS_END

#endif
