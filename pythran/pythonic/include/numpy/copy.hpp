#ifndef PYTHONIC_INCLUDE_NUMPY_COPY_HPP
#define PYTHONIC_INCLUDE_NUMPY_COPY_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/utils/numpy_conversion.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    // list case
    template <class E>
    typename std::enable_if<!types::is_array<E>::value and
                                !types::is_dtype<E>::value,
                            types::ndarray<typename E::dtype, E::value>>::type
    copy(E const &v);

    // scalar / complex case
    template <class E>
    auto copy(E const &v) ->
        typename std::enable_if<types::is_dtype<E>::value, E>::type;

    // No copy is required for numpy_expr
    template <class E>
    auto copy(E &&v) ->
        typename std::enable_if<types::is_array<E>::value,
                                decltype(std::forward<E>(v))>::type;

    // ndarray case
    template <class T, size_t N>
    types::ndarray<T, N> copy(types::ndarray<T, N> const &a);

    DECLARE_FUNCTOR(pythonic::numpy, copy);
  }
}

#endif
