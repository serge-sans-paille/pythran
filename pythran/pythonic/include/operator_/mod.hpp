#ifndef PYTHONIC_INCLUDE_OPERATOR_MOD_HPP
#define PYTHONIC_INCLUDE_OPERATOR_MOD_HPP

#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace operator_
{

  template <class A, class B>
  auto mod(A const &a, B const &b) ->
      typename std::enable_if<std::is_fundamental<A>::value &&
                                  std::is_fundamental<B>::value,
                              decltype(a % b)>::type;

  inline double mod(double a, long b);

  inline double mod(double a, double b);

  template <class A, class B>
  auto mod(A const &a, B const &b) // for ndarrays
      -> typename std::enable_if<!std::is_fundamental<A>::value ||
                                     !std::is_fundamental<B>::value,
                                 decltype(a % b)>::type;

  DECLARE_FUNCTOR(pythonic::operator_, mod);
}
PYTHONIC_NS_END

#endif
