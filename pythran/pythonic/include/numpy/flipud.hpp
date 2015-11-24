#ifndef PYTHONIC_INCLUDE_NUMPY_FLIPUD_HPP
#define PYTHONIC_INCLUDE_NUMPY_FLIPUD_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E>
    auto flipud(E &&expr) -> decltype(std::forward<E>(
        expr)[types::slice{__builtin__::None, __builtin__::None, -1}]);

    DECLARE_FUNCTOR(pythonic::numpy, flipud);
  }
}

#endif
