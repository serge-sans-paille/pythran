#ifndef PYTHONIC_INCLUDE_NUMPY_SWAPAXES_HPP
#define PYTHONIC_INCLUDE_NUMPY_SWAPAXES_HPP

#include "pythonic/include/numpy/transpose.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T>
    auto swapaxes(T &&a, int axis1, int axis2) -> decltype(_transpose(
        std::forward<T>(a), std::declval<long[std::decay<T>::type::value]>()));

    DECLARE_FUNCTOR(pythonic::numpy, swapaxes);
  }
}

#endif
