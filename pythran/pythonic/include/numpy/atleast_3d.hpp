#ifndef PYTHONIC_INCLUDE_NUMPY_ATLEAST3D_HPP
#define PYTHONIC_INCLUDE_NUMPY_ATLEAST3D_HPP

#include "pythonic/include/numpy/asarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T>
    typename std::enable_if<types::is_dtype<T>::value,
                            types::ndarray<T, 3>>::type
    atleast_3d(T t);

    template <class T>
    auto atleast_3d(T const &t) ->
        typename std::enable_if<(not types::is_dtype<T>::value) and
                                    (T::value < 3),
                                types::ndarray<typename T::dtype, 3>>::type;

    template <class T>
    auto atleast_3d(T const &t) ->
        typename std::enable_if<(not types::is_dtype<T>::value) and
                                    T::value >= 3,
                                decltype(asarray(t))>::type;

    DECLARE_FUNCTOR(pythonic::numpy, atleast_3d);
  }
}

#endif
