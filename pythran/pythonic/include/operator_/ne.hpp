#ifndef PYTHONIC_INCLUDE_OPERATOR_NE_HPP
#define PYTHONIC_INCLUDE_OPERATOR_NE_HPP

#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace operator_
{

  template <class A, class B>
  auto ne(A const &a, B const &b) -> decltype(a != b);

  bool ne(char const *a, char const *b);

  DEFINE_FUNCTOR(pythonic::operator_, ne);
}
PYTHONIC_NS_END

#endif
