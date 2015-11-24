#ifndef PYTHONIC_INCLUDE_NUMPY_ASARRAY_HPP
#define PYTHONIC_INCLUDE_NUMPY_ASARRAY_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/numpy/array.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E, class dtype>
    struct _asarray {
      template <class... Types>
      auto operator()(Types &&... args)
          -> decltype(array(std::forward<Types>(args)...));
    };

    template <class T, size_t N>
    struct _asarray<types::ndarray<T, N>, T> {
      template <class F, class dtype>
      F &&operator()(F &&a, dtype);
    };

    template <class E>
    auto asarray(E &&e, types::none_type d = types::none_type()) -> decltype(
        _asarray<typename std::decay<E>::type,
                 types::dtype_t<typename utils::nested_container_value_type<
                     typename std::decay<E>::type>::type>>{}(
            std::forward<E>(e),
            types::dtype_t<typename utils::nested_container_value_type<
                typename std::decay<E>::type>::type>{}));

    template <class E, class dtype>
    auto asarray(E &&e, dtype d) -> decltype(
        _asarray<typename std::decay<E>::type, dtype>{}(std::forward<E>(e), d));

    DECLARE_FUNCTOR(pythonic::numpy, asarray);
  }
}

#endif
