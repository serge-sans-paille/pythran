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
  types::ndarray<typename dtype::type, std::decay<T>::type::value>
  array(T &&iterable, dtype d = dtype());

  DECLARE_FUNCTOR(pythonic::numpy, array);
}
PYTHONIC_NS_END

#endif
