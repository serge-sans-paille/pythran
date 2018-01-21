#ifndef PYTHONIC_OPERATOR_AND_HPP
#define PYTHONIC_OPERATOR_AND_HPP

#include "pythonic/include/operator_/and_.hpp"
#include "pythonic/operator_/overloads.hpp"

#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace operator_
{
  template <class A, class B>
  auto and_(A const &a, B const &b) -> decltype(a &b)
  {
    return a & b;
  }

  DEFINE_ALL_OPERATOR_OVERLOADS_IMPL(and_, &)

  DEFINE_FUNCTOR(pythonic::operator_, and_);
}
PYTHONIC_NS_END

#endif
