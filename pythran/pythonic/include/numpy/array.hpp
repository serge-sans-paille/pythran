#ifndef PYTHONIC_INCLUDE_NUMPY_ARRAY_HPP
#define PYTHONIC_INCLUDE_NUMPY_ARRAY_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/utils/nested_container.hpp"
#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <
        class T,
        class dtype = types::dtype_t<
            typename utils::nested_container_value_type<typename std::remove_cv<
                typename std::remove_reference<T>::type>::type>::type>>
    types::ndarray<typename dtype::type,
                   utils::nested_container_depth<typename std::remove_cv<
                       typename std::remove_reference<T>::type>::type>::value>
    array(T &&iterable, dtype d = dtype());

    DECLARE_FUNCTOR(pythonic::numpy, array);
  }
}

#endif
