#ifndef PYTHONIC_OPERATOR_GE_HPP
#define PYTHONIC_OPERATOR_GE_HPP

#include "pythonic/include/operator_/ge.hpp"

#include "pythonic/utils/functor.hpp"

#include <cstring>

PYTHONIC_NS_BEGIN

namespace operator_
{
  template <class A, class B>
  auto ge(A const &a, B const &b) -> decltype(a >= b)
  {
    return a >= b;
  }

  bool ge(char const *self, char const *other)
  {
    return strcmp(self, other) >= 0;
  }
}
PYTHONIC_NS_END

#endif
