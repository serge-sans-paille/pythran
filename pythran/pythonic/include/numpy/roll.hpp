#ifndef PYTHONIC_INCLUDE_NUMPY_ROLL_HPP
#define PYTHONIC_INCLUDE_NUMPY_ROLL_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/utils/numpy_conversion.hpp"
#include "pythonic/include/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class T, class pS>
  types::ndarray<T, pS> roll(types::ndarray<T, pS> const &expr, long shift);

  template <class T, class pS>
  types::ndarray<T, pS> roll(types::ndarray<T, pS> const &expr, long shift,
                             long axis);

  NUMPY_EXPR_TO_NDARRAY0_DECL(roll);
  DECLARE_FUNCTOR(pythonic::numpy, roll);
}
PYTHONIC_NS_END

#endif
