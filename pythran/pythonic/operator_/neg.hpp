#ifndef PYTHONIC_OPERATOR_NEG_HPP
#define PYTHONIC_OPERATOR_NEG_HPP

#include "pythonic/include/operator_/neg.hpp"

#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace operator_
{

  template <class A>
  auto neg(A const &a) -> decltype(-a)
  {
    return -a;
  }

  DEFINE_FUNCTOR(pythonic::operator_, neg);
}
PYTHONIC_NS_END

#endif
