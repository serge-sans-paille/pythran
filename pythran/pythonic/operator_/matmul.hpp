#ifndef PYTHONIC_OPERATOR_MATMUL_HPP
#define PYTHONIC_OPERATOR_MATMUL_HPP

#include "pythonic/include/operator_/matmul.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/numpy/dot.hpp"

PYTHONIC_NS_BEGIN

namespace operator_
{

  template <class A, class B>
  auto matmul(A const &a, B const &b) -> decltype(numpy::functor::dot{}(a, b))
  {
    return numpy::functor::dot{}(a, b);
  }

  DEFINE_FUNCTOR(pythonic::operator_, matmul);
}
PYTHONIC_NS_END

#endif
