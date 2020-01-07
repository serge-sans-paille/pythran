#ifndef PYTHONIC_NUMPY_FLIPLR_HPP
#define PYTHONIC_NUMPY_FLIPLR_HPP

#include "pythonic/include/numpy/fliplr.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

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
}
PYTHONIC_NS_END

#endif
