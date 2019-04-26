#ifndef PYTHONIC_INCLUDE_NUMPY_CORRELATE_HPP
#define PYTHONIC_INCLUDE_NUMPY_CORRELATE_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class A, class B, typename U>
  types::ndarray<typename A::dtype, types::pshape<long>>
  correlate(A const &inA, B const &inB, U renorm = types::str("valid"));

  template <class A, class B>
  types::ndarray<typename A::dtype, types::pshape<long>>
  correlate(A const &inA, B const &inB);

  NUMPY_EXPR_TO_NDARRAY0_DECL(correlate)
  DEFINE_FUNCTOR(pythonic::numpy, correlate)
}
PYTHONIC_NS_END

#endif
