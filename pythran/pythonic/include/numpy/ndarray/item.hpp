#ifndef PYTHONIC_INCLUDE_NUMPY_NDARRAY_ITEM_HPP
#define PYTHONIC_INCLUDE_NUMPY_NDARRAY_ITEM_HPP

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {

    namespace ndarray
    {

      template <class T, size_t N>
      T item(types::ndarray<T, N> const &expr, long i);

      template <class E, size_t N>
      auto item(E &&expr, types::array<long, N> const &i) -> decltype(expr[i]);

      // only for compatibility purpose, very bad impl
      template <class E>
      typename std::decay<E>::dtype item(E &&expr, long i);

      DECLARE_FUNCTOR(pythonic::numpy::ndarray, item);
    }
  }
}

#endif
