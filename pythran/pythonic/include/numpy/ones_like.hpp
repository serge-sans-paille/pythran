#ifndef PYTHONIC_INCLUDE_NUMPY_ONESLIKE_HPP
#define PYTHONIC_INCLUDE_NUMPY_ONESLIKE_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/numpy/ones.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <class E, class dtype>
    auto ones_like(E const &expr, dtype d = dtype())
        -> decltype(ones(expr.shape(), d));

    template <class E>
    auto ones_like(E const &expr, types::none_type d = __builtin__::None)
        -> decltype(ones(expr.shape(), types::dtype_t<typename E::dtype>()));

    DECLARE_FUNCTOR(pythonic::numpy, ones_like)
  }
}

#endif
