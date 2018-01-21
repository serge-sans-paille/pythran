#ifndef PYTHONIC_INCLUDE_OPERATOR_INVERT_HPP
#define PYTHONIC_INCLUDE_OPERATOR_INVERT_HPP

#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace operator_
{

  template <class A>
  decltype(~std::declval<A const &>()) invert(A const &a);

  DECLARE_FUNCTOR(pythonic::operator_, invert);
}
PYTHONIC_NS_END

#endif
