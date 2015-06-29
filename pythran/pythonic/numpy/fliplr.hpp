#ifndef PYTHONIC_NUMPY_FLIPLR_HPP
#define PYTHONIC_NUMPY_FLIPLR_HPP

#include "pythonic/include/numpy/fliplr.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E>
    auto fliplr(E &&expr) -> decltype(std::forward<E>(expr)(
        types::contiguous_slice{builtins::None, builtins::None},
        types::slice{builtins::None, builtins::None, -1}))
    {
      return std::forward<E>(expr)(
          types::contiguous_slice{builtins::None, builtins::None},
          types::slice{builtins::None, builtins::None, -1});
    }

    PROXY_IMPL(pythonic::numpy, fliplr);
  }
}

#endif
