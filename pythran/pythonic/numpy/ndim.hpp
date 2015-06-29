#ifndef PYTHONIC_NUMPY_NDIM_HPP
#define PYTHONIC_NUMPY_NDIM_HPP

#include "pythonic/include/numpy/ndim.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <class E>
    auto ndim(E const &e) -> decltype(builtins::getattr<types::attr::NDIM>(e))
    {
      return builtins::getattr<types::attr::NDIM>(e);
    }

    PROXY_IMPL(pythonic::numpy, ndim)
  }
}

#endif
