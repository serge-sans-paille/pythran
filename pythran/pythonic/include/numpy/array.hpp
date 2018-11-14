#ifndef PYTHONIC_INCLUDE_NUMPY_ARRAY_HPP
#define PYTHONIC_INCLUDE_NUMPY_ARRAY_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/utils/nested_container.hpp"
#include "pythonic/include/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class T,
            class dtype = types::dtype_t<typename std::decay<T>::type::dtype>>
  types::ndarray<typename dtype::type,
                 types::array<long, std::decay<T>::type::value>>
  array(T &&iterable, dtype d = dtype());

  template <class T, class pS>
  types::ndarray<T, pS> array(types::ndarray<T, pS> const &arr);

  template <class T, size_t N, class dtype = types::dtype_t<T>>
  types::ndarray<typename dtype::type,
                 types::pshape<std::integral_constant<long, N>>>
  array(types::array<T, N> const &, dtype d = dtype());

  DEFINE_FUNCTOR(pythonic::numpy, array);
}
PYTHONIC_NS_END

#endif
