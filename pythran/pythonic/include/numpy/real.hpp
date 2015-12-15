#ifndef PYTHONIC_INCLUDE_NUMPY_REAL_HPP
#define PYTHONIC_INCLUDE_NUMPY_REAL_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/numpy/asarray.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/list.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E>
    auto real(E &&expr) -> decltype(
        __builtin__::getattr<types::attr::REAL>(std::forward<E>(expr)));
    template <class T>
    auto real(types::list<T> const &expr)
        -> decltype(real(numpy::functor::asarray{}(expr)));

    DECLARE_FUNCTOR(pythonic::numpy, real);
  }
}

#endif
