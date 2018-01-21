#ifndef PYTHONIC_NUMPY_ZEROSLIKE_HPP
#define PYTHONIC_NUMPY_ZEROSLIKE_HPP

#include "pythonic/include/numpy/zeros_like.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/numpy/zeros.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{

  template <class E, class dtype>
  auto zeros_like(E const &expr, dtype d) -> decltype(zeros(expr.shape(), d))
  {
    return zeros(expr.shape(), d);
  }

  template <class E>
  auto zeros_like(E const &expr, types::none_type)
      -> decltype(zeros(expr.shape(), types::dtype_t<typename E::dtype>()))
  {
    return zeros(expr.shape(), types::dtype_t<typename E::dtype>());
  }

  DEFINE_FUNCTOR(pythonic::numpy, zeros_like)
}
PYTHONIC_NS_END

#endif
