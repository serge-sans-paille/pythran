#ifndef PYTHONIC_NUMPY_IMAG_HPP
#define PYTHONIC_NUMPY_IMAG_HPP

#include "pythonic/include/numpy/imag.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E>
    auto imag(E &&expr)
        -> decltype(builtins::getattr<types::attr::IMAG>(std::forward<E>(expr)))

    {
      return builtins::getattr<types::attr::IMAG>(std::forward<E>(expr));
    }

    PROXY_IMPL(pythonic::numpy, imag);
  }
}

#endif
