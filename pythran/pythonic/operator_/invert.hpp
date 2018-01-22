#ifndef PYTHONIC_OPERATOR_INVERT_HPP
#define PYTHONIC_OPERATOR_INVERT_HPP

#include "pythonic/include/operator_/invert.hpp"

#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace operator_
{

  template <class A>
  decltype(~std::declval<A const &>()) invert(A const &a)
  {
    return ~a;
  }

  DEFINE_FUNCTOR(pythonic::operator_, invert);
}
PYTHONIC_NS_END

#endif
