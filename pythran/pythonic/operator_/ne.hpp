#ifndef PYTHONIC_OPERATOR_NE_HPP
#define PYTHONIC_OPERATOR_NE_HPP

#include "pythonic/include/operator_/ne.hpp"

#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace operator_
{

  template <class A, class B>
  auto ne(A const &a, B const &b) -> decltype(a != b)
  {
    return a != b;
  }

  bool ne(char const *a, char const *b)
  {
    return strcmp(a, b) != 0;
  }
}
PYTHONIC_NS_END

#endif
