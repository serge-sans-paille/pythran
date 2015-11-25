#ifndef PYTHONIC_NUMPY_COPY_HPP
#define PYTHONIC_NUMPY_COPY_HPP

#include "pythonic/include/numpy/copy.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    // list case
    template <class E>
    typename std::enable_if<!types::is_array<E>::value and
                                !types::is_dtype<E>::value,
                            types::ndarray<typename E::dtype, E::value>>::type
    copy(E const &v)
    {
      return {v};
    }

    // scalar / complex case
    template <class E>
    auto copy(E const &v) ->
        typename std::enable_if<types::is_dtype<E>::value, E>::type
    {
      return v;
    }

    // No copy is required for numpy_expr
    template <class E>
    auto copy(E &&v) ->
        typename std::enable_if<types::is_array<E>::value,
                                decltype(std::forward<E>(v))>::type
    {
      return std::forward<E>(v);
    }

    // ndarray case
    template <class T, size_t N>
    types::ndarray<T, N> copy(types::ndarray<T, N> const &a)
    {
      return a.copy();
    }

    DEFINE_FUNCTOR(pythonic::numpy, copy);
  }
}

#endif
