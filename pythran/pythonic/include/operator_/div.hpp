#ifndef PYTHONIC_INCLUDE_OPERATOR_DIV_HPP
#define PYTHONIC_INCLUDE_OPERATOR_DIV_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/operator_/overloads.hpp"

PYTHONIC_NS_BEGIN

namespace operator_
{
#if PY_MAJOR_VERSION >= 3
  template <class A, class B>
  auto div(A const &a, B const &b) // for ndarrays
      -> typename std::enable_if<!std::is_fundamental<A>::value ||
                                     !std::is_fundamental<B>::value,
                                 decltype(a / b)>::type;

  double div(double a, double b);
#else
  template <class A, class B>
  auto div(A const &a, B const &b) -> decltype(a / b);

  DEFINE_ALL_OPERATOR_OVERLOADS_DECL(div, / )
#endif

  DECLARE_FUNCTOR(pythonic::operator_, div);
}
PYTHONIC_NS_END

#endif
