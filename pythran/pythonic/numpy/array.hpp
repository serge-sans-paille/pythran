#ifndef PYTHONIC_NUMPY_ARRAY_HPP
#define PYTHONIC_NUMPY_ARRAY_HPP

#include "pythonic/include/numpy/array.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/nested_container.hpp"
#include "pythonic/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class T, class dtype>
  types::ndarray<typename dtype::type,
                 types::array<long, std::decay<T>::type::value>>
  array(T &&iterable, dtype d)
  {
    return {std::forward<T>(iterable)};
  }

  template <class T, class pS>
  types::ndarray<T, pS> array(types::ndarray<T, pS> const &arr)
  {
    return arr.copy();
  }

  template <class T, size_t N, class dtype>
  types::ndarray<typename dtype::type,
                 types::pshape<std::integral_constant<long, N>>>
  array(types::array<T, N> const &a, dtype)
  {
    return {a};
  }
}
PYTHONIC_NS_END

#endif
