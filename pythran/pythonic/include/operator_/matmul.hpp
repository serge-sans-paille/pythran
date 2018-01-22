#ifndef PYTHONIC_INCLUDE_OPERATOR_MATMUL_HPP
#define PYTHONIC_INCLUDE_OPERATOR_MATMUL_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/numpy/dot.hpp"

PYTHONIC_NS_BEGIN

namespace operator_
{

  template <class A, class B>
  auto matmul(A const &a, B const &b) -> decltype(numpy::functor::dot(a, b));

  DECLARE_FUNCTOR(pythonic::operator_, matmul);
}
PYTHONIC_NS_END

#endif
