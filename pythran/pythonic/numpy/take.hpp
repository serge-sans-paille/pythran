#ifndef PYTHONIC_NUMPY_TAKE_HPP
#define PYTHONIC_NUMPY_TAKE_HPP

#include "pythonic/include/numpy/take.hpp"

#include "pythonic/types/numpy_fexpr.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class F, class T>
    auto take(T &&expr, F &&indices)
        -> decltype(types::numpy_fexpr<T, F>(std::forward<T>(expr),
                                             std::forward<F>(indices)))
    {
      return types::numpy_fexpr<T, F>(std::forward<T>(expr),
                                      std::forward<F>(indices));
    }

    DEFINE_FUNCTOR(pythonic::numpy, take);
  }
}

#endif
