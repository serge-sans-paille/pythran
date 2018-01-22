#ifndef PYTHONIC_INCLUDE_OPERATOR_IFLOORDIV_HPP
#define PYTHONIC_INCLUDE_OPERATOR_IFLOORDIV_HPP

#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace operator_
{

  template <class A, class B>
  A ifloordiv(A a, B const &b);

  DECLARE_FUNCTOR(pythonic::operator_, ifloordiv);
}
PYTHONIC_NS_END

#endif
