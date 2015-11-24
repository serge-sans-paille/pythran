#ifndef PYTHONIC_NUMPY_ASARRAY_HPP
#define PYTHONIC_NUMPY_ASARRAY_HPP

#include "pythonic/include/numpy/asarray.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/array.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <class E, class dtype>
    template <class... Types>
    auto _asarray<E, dtype>::operator()(Types &&... args)
        -> decltype(array(std::forward<Types>(args)...))
    {
      return array(std::forward<Types>(args)...);
    }

    template <class T, size_t N>
    template <class F, class dtype>
    F &&_asarray<types::ndarray<T, N>, T>::operator()(F &&a, dtype)
    {
      return std::forward<F>(a);
    }

    template <class E>
    auto asarray(E &&e, types::none_type d) -> decltype(
        _asarray<typename std::decay<E>::type,
                 types::dtype_t<typename utils::nested_container_value_type<
                     typename std::decay<E>::type>::type>>{}(
            std::forward<E>(e),
            types::dtype_t<typename utils::nested_container_value_type<
                typename std::decay<E>::type>::type>{}))
    {
      return _asarray<
          typename std::decay<E>::type,
          types::dtype_t<typename utils::nested_container_value_type<
              typename std::decay<E>::type>::type>>{}(
          std::forward<E>(e),
          types::dtype_t<typename utils::nested_container_value_type<
              typename std::decay<E>::type>::type>{});
    }

    template <class E, class dtype>
    auto asarray(E &&e, dtype d) -> decltype(
        _asarray<typename std::decay<E>::type, dtype>{}(std::forward<E>(e), d))
    {
      return _asarray<typename std::decay<E>::type, dtype>{}(std::forward<E>(e),
                                                             d);
    }

    DEFINE_FUNCTOR(pythonic::numpy, asarray);
  }
}

#endif
