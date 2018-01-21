#ifndef PYTHONIC_NUMPY_FLIPUD_HPP
#define PYTHONIC_NUMPY_FLIPUD_HPP

#include "pythonic/include/numpy/flipud.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class E>
  auto flipud(E &&expr) -> decltype(std::forward<E>(
      expr)[types::slice{__builtin__::None, __builtin__::None, -1}])
  {
    return std::forward<E>(
        expr)[types::slice{__builtin__::None, __builtin__::None, -1}];
  }

  DEFINE_FUNCTOR(pythonic::numpy, flipud);
}
PYTHONIC_NS_END

#endif
