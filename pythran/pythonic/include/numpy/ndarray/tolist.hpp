#ifndef PYTHONIC_INCLUDE_NUMPY_NDARRAY_TOLIST_HPP
#define PYTHONIC_INCLUDE_NUMPY_NDARRAY_TOLIST_HPP

#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {

    namespace ndarray
    {
      template <class T, size_t N>
      struct tolist_type {
        using type = types::list<typename tolist_type<T, N - 1>::type>;
      };

      template <class T>
      struct tolist_type<T, 1> {
        using type = types::list<T>;
      };

      template <class T>
      types::list<T> tolist(types::ndarray<T, 1> const &expr);

      template <class T, size_t N>
      typename tolist_type<T, N>::type tolist(types::ndarray<T, N> const &expr);

      NUMPY_EXPR_TO_NDARRAY0_DECL(tolist);
      DECLARE_FUNCTOR(pythonic::numpy::ndarray, tolist);
    }
  }
}

#endif
