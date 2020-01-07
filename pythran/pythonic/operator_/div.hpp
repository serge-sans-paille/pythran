#ifndef PYTHONIC_OPERATOR_DIV_HPP
#define PYTHONIC_OPERATOR_DIV_HPP

#include "pythonic/include/operator_/div.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/operator_/overloads.hpp"

PYTHONIC_NS_BEGIN

namespace operator_
{

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
}
PYTHONIC_NS_END

#endif
