#ifndef PYTHONIC_OPERATOR_LT_HPP
#define PYTHONIC_OPERATOR_LT_HPP

#include "pythonic/include/operator_/lt.hpp"

#include "pythonic/utils/functor.hpp"
#include <cstring>

PYTHONIC_NS_BEGIN

namespace operator_
{

  template <class A, class B>
  auto lt(A const &a, B const &b) -> decltype(a < b)
  {
    return a < b;
  }
  bool lt(char const *self, char const *other)
  {
    return strcmp(self, other) < 0;
  }
}
PYTHONIC_NS_END

#endif
