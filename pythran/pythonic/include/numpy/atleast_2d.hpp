#ifndef PYTHONIC_INCLUDE_NUMPY_ATLEAST2D_HPP
#define PYTHONIC_INCLUDE_NUMPY_ATLEAST2D_HPP

#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T>
    typename std::enable_if<types::is_dtype<T>::value,
                            types::ndarray<T, 2>>::type
    atleast_2d(T t);

    template <class T>
            auto atleast_2d(T const &t) ->
            typename std::enable_if < (not types::is_dtype<T>::value) and
        T::value<2, types::ndarray<typename T::dtype, 2>>::type;

    template <class T>
    auto atleast_2d(T &&t) -> typename std::enable_if<
        (not types::is_dtype<typename std::remove_cv<
            typename std::remove_reference<T>::type>::type>::value) and
            std::decay<T>::type::value >= 2,
        decltype(std::forward<T>(t))>::type;

    DECLARE_FUNCTOR(pythonic::numpy, atleast_2d);
  }
}

#endif
