#ifndef PYTHONIC_OPERATOR_COUNTOF_HPP
#define PYTHONIC_OPERATOR_COUNTOF_HPP

#include "pythonic/include/operator_/countOf.hpp"

#include "pythonic/utils/functor.hpp"
#include <algorithm>

PYTHONIC_NS_BEGIN

namespace operator_
{
  template <class A, class B>
  long countOf(A const &a, B const &b)
  {
    return std::count(a.begin(), a.end(), b);
  }

  DEFINE_FUNCTOR(pythonic::operator_, countOf);
}
PYTHONIC_NS_END

#endif
