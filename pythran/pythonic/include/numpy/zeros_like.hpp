#ifndef PYTHONIC_INCLUDE_NUMPY_ZEROSLIKE_HPP
#define PYTHONIC_INCLUDE_NUMPY_ZEROSLIKE_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/numpy/zeros.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{

  template <class E, class dtype>
  auto zeros_like(E const &expr, dtype d = dtype())
      -> decltype(zeros(expr.shape(), d));

  template <class E>
  auto zeros_like(E const &expr, types::none_type d = __builtin__::None)
      -> decltype(zeros(expr.shape(), types::dtype_t<typename E::dtype>()));

  DECLARE_FUNCTOR(pythonic::numpy, zeros_like)
}
PYTHONIC_NS_END

#endif
