#ifndef PYTHONIC_INCLUDE_OPERATOR_POS_HPP
#define PYTHONIC_INCLUDE_OPERATOR_POS_HPP

#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace operator_
{

  template <class A>
  auto pos(A const &a) -> decltype(+a);

  char pos(char const &a);
  signed char pos(signed char const &a);
  unsigned char pos(unsigned char const &a);

  DEFINE_FUNCTOR(pythonic::operator_, pos);
}
PYTHONIC_NS_END

#endif
