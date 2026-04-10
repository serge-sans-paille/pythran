#ifndef PYTHONIC_INCLUDE_OPERATOR_DIV_HPP
#define PYTHONIC_INCLUDE_OPERATOR_DIV_HPP

#include "pythonic/include/operator_/overloads.hpp"
#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace operator_
{
  template <class A, class B>
  auto div(A &&a, B &&b) // for ndarrays
      -> std::enable_if_t<!std::is_fundamental_v<std::decay_t<A>> ||
                              !std::is_fundamental_v<std::decay_t<B>>,
                          decltype(std::forward<A>(a) / std::forward<B>(b))>;

  double div(double a, double b);

  DEFINE_FUNCTOR(pythonic::operator_, div);
} // namespace operator_
PYTHONIC_NS_END

#endif
