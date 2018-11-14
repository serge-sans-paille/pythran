#ifndef PYTHONIC_OPERATOR_ITRUEDIV_HPP
#define PYTHONIC_OPERATOR_ITRUEDIV_HPP

#include "pythonic/include/operator_/itruediv.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/operator_/truediv.hpp"

PYTHONIC_NS_BEGIN

namespace operator_
{
  template <class A, class B>
  auto itruediv(A const &a, B const &b) -> decltype(truediv(a, b))
  {
    return truediv(a, b);
  }
  template <class A, class B>
  auto itruediv(A &a, B const &b) ->
      typename std::enable_if<std::is_same<A, decltype(truediv(a, b))>::value,
                              A &>::type
  {
    return a = truediv(a, b);
  }
  template <class A, class B>
  auto itruediv(A &a, B const &b) ->
      typename std::enable_if<!std::is_same<A, decltype(truediv(a, b))>::value,
                              decltype(truediv(a, b))>::type
  {
    return truediv(a, b);
  }
}
PYTHONIC_NS_END

#endif
