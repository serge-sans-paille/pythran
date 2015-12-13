#ifndef PYTHONIC_INCLUDE_NUMPY_IMAG_HPP
#define PYTHONIC_INCLUDE_NUMPY_IMAG_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/numpy/asarray.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/list.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E>
    auto imag(E &&expr) -> decltype(
        __builtin__::getattr<types::attr::IMAG>(std::forward<E>(expr)));

    template <class T>
    auto imag(types::list<T> const &expr)
        -> decltype(imag(numpy::functor::asarray{}(expr)));

    DECLARE_FUNCTOR(pythonic::numpy, imag);
  }
}

#endif
