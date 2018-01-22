#ifndef PYTHONIC_INCLUDE_NUMPY_EMPTYLIKE_HPP
#define PYTHONIC_INCLUDE_NUMPY_EMPTYLIKE_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/numpy/empty.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class E, class dtype>
  auto empty_like(E const &expr, dtype d = dtype())
      -> decltype(empty(expr.shape(), d));

  template <class E>
  auto empty_like(E const &expr, types::none_type d = __builtin__::None)
      -> decltype(empty(expr.shape(), types::dtype_t<typename E::dtype>()));

  DECLARE_FUNCTOR(pythonic::numpy, empty_like)
}
PYTHONIC_NS_END

#endif
