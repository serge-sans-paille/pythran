#ifndef PYTHONIC_INCLUDE_NUMPY_TAKE_HPP
#define PYTHONIC_INCLUDE_NUMPY_TAKE_HPP

#include "pythonic/include/types/numpy_fexpr.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class F, class T>
  auto take(T &&expr, F &&indices)
      -> decltype(types::numpy_fexpr<T, F>(std::forward<T>(expr),
                                           std::forward<F>(indices)));

  DECLARE_FUNCTOR(pythonic::numpy, take);
}
PYTHONIC_NS_END

#endif
