#ifndef PYTHONIC_OPERATOR_LSHIFT_HPP
#define PYTHONIC_OPERATOR_LSHIFT_HPP

#include "pythonic/include/operator_/lshift.hpp"
#include "pythonic/operator_/overloads.hpp"

#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace operator_
{

  template <class A, class B>
  auto lshift(A &&a, B &&b)
      -> decltype(std::forward<A>(a) << std::forward<B>(b))
  {
    return std::forward<A>(a) << std::forward<B>(b);
  }

  DEFINE_ALL_OPERATOR_OVERLOADS_IMPL(
      lshift, <<, (a <= (std::numeric_limits<decltype(b)>::max() >> b)))
}
PYTHONIC_NS_END

#endif
