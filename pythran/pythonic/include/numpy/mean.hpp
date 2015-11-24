#ifndef PYTHONIC_INCLUDE_NUMPY_MEAN_HPP
#define PYTHONIC_INCLUDE_NUMPY_MEAN_HPP

#include "pythonic/include/numpy/sum.hpp"
#include "pythonic/include/numpy/float64.hpp"
#include "pythonic/include/__builtin__/None.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E, class dtype = functor::float64>
    auto mean(E const &expr, types::none_type axis = __builtin__::None,
              dtype d = dtype())
        -> decltype(sum(expr) / typename dtype::type(expr.flat_size()));

    template <class E, class dtype = functor::float64>
    auto mean(E const &expr, long axis, dtype d = dtype())
        -> decltype(sum(expr, axis));

    DECLARE_FUNCTOR(pythonic::numpy, mean);
  }
}

#endif
