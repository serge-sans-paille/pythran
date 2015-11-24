#ifndef PYTHONIC_NUMPY_IMAG_HPP
#define PYTHONIC_NUMPY_IMAG_HPP

#include "pythonic/include/numpy/imag.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E>
    auto imag(E &&expr) -> decltype(
        __builtin__::getattr<types::attr::IMAG>(std::forward<E>(expr)))
    {
      return __builtin__::getattr<types::attr::IMAG>(std::forward<E>(expr));
    }

    DEFINE_FUNCTOR(pythonic::numpy, imag);
  }
}

#endif
