#ifndef PYTHONIC_INCLUDE_NUMPY_FLIPUD_HPP
#define PYTHONIC_INCLUDE_NUMPY_FLIPUD_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E>
    auto flipud(E &&expr) -> decltype(std::forward<E>(
        expr)[types::slice{builtins::None, builtins::None, -1}]);

    PROXY_DECL(pythonic::numpy, flipud);
  }
}

#endif
