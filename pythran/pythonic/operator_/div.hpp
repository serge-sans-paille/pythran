#ifndef PYTHONIC_OPERATOR_DIV_HPP
#define PYTHONIC_OPERATOR_DIV_HPP

#include "pythonic/include/operator_/div.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/operator_/overloads.hpp"

PYTHONIC_NS_BEGIN

namespace operator_
{

#if PY_MAJOR_VERSION >= 3
  template <class A, class B>
  auto div(A const &a, B const &b) // for ndarrays
      -> typename std::enable_if<!std::is_fundamental<A>::value ||
                                     !std::is_fundamental<B>::value,
                                 decltype(a / b)>::type
  {
    return a / b;
  }

  double div(double a, double b)
  {
    return a / b;
  }
#else
  template <class A, class B>
  auto div(A const &a, B const &b) -> decltype(a / b)
  {
    return a / b;
  }

  DEFINE_ALL_OPERATOR_OVERLOADS_IMPL(div, / )
#endif

  DEFINE_FUNCTOR(pythonic::operator_, div);
}
PYTHONIC_NS_END

#endif
