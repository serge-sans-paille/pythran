#ifndef PYTHONIC_NUMPY_ARRAY_HPP
#define PYTHONIC_NUMPY_ARRAY_HPP

#include "pythonic/include/numpy/array.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/nested_container.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T, class dtype>
    types::ndarray<typename dtype::type,
                   utils::nested_container_depth<typename std::remove_cv<
                       typename std::remove_reference<T>::type>::type>::value>
    array(T &&iterable, dtype d)
    {
      return {std::forward<T>(iterable)};
    }

    DEFINE_FUNCTOR(pythonic::numpy, array);
  }
}

#endif
