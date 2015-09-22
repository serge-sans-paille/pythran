#ifndef PYTHONIC_INCLUDE_NUMPY_FLIPLR_HPP
#define PYTHONIC_INCLUDE_NUMPY_FLIPLR_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E>
    auto fliplr(E &&expr) -> decltype(std::forward<E>(expr)(
        types::contiguous_slice{__builtin__::None, __builtin__::None},
        types::slice{__builtin__::None, __builtin__::None, -1}));

    PROXY_DECL(pythonic::numpy, fliplr);
  }
}

#endif
