#ifndef PYTHONIC_NUMPY_EMPTYLIKE_HPP
#define PYTHONIC_NUMPY_EMPTYLIKE_HPP

#include "pythonic/include/numpy/empty_like.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/numpy/empty.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E, class dtype>
    auto empty_like(E const &expr, dtype d) -> decltype(empty(expr.shape(), d))
    {
      return empty(expr.shape(), d);
    }

    template <class E>
    auto empty_like(E const &expr, types::none_type)
        -> decltype(empty(expr.shape(), types::dtype_t<typename E::dtype>()))
    {
      return empty(expr.shape(), types::dtype_t<typename E::dtype>());
    }

    DEFINE_FUNCTOR(pythonic::numpy, empty_like)
  }
}

#endif
