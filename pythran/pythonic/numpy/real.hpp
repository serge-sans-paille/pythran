#ifndef PYTHONIC_NUMPY_REAL_HPP
#define PYTHONIC_NUMPY_REAL_HPP

#include "pythonic/include/numpy/real.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/numpy/asarray.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/list.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E>
    auto real(E &&expr) -> decltype(
        __builtin__::getattr<types::attr::REAL>(std::forward<E>(expr)))
    {
      return __builtin__::getattr<types::attr::REAL>(std::forward<E>(expr));
    }

    template <class T>
    auto real(types::list<T> const &expr)
        -> decltype(real(numpy::functor::asarray{}(expr)))
    {
      return real(numpy::functor::asarray{}(expr));
    }

    DEFINE_FUNCTOR(pythonic::numpy, real);
  }
}

#endif
