#ifndef PYTHONIC_OPERATOR_LSHIFT_HPP
#define PYTHONIC_OPERATOR_LSHIFT_HPP

#include "pythonic/include/operator_/lshift.hpp"
#include "pythonic/operator_/overloads.hpp"

#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace operator_
{

  template <class A, class B>
  auto lshift(A const &a, B const &b) -> decltype(a << b)
  {
    return a << b;
  }

  DEFINE_ALL_OPERATOR_OVERLOADS_IMPL(lshift, << )

  DEFINE_FUNCTOR(pythonic::operator_, lshift);
}
PYTHONIC_NS_END

#endif
