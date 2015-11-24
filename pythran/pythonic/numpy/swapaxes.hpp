#ifndef PYTHONIC_NUMPY_SWAPAXES_HPP
#define PYTHONIC_NUMPY_SWAPAXES_HPP

#include "pythonic/include/numpy/swapaxes.hpp"

#include "pythonic/numpy/transpose.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T>
    auto swapaxes(T &&a, int axis1, int axis2) -> decltype(_transpose(
        std::forward<T>(a), std::declval<long[std::decay<T>::type::value]>()))
    {
      constexpr long N = std::decay<T>::type::value;
      long t[N];
      for (unsigned long i = 0; i < N; ++i)
        t[i] = i;
      std::swap(t[axis1], t[axis2]);
      return _transpose(std::forward<T>(a), t);
    }

    DEFINE_FUNCTOR(pythonic::numpy, swapaxes);
  }
}

#endif
