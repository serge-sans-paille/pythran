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
                 types::make_pshape_t<std::decay<T>::type::value>>
  array(T &&iterable, dtype d)
  {
    return {std::forward<T>(iterable)};
  }

  DEFINE_FUNCTOR(pythonic::numpy, array);
}
PYTHONIC_NS_END

#endif
