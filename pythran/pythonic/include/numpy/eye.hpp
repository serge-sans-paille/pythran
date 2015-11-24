#ifndef PYTHONIC_INCLUDE_NUMPY_EYE_HPP
#define PYTHONIC_INCLUDE_NUMPY_EYE_HPP

#include "pythonic/include/numpy/zeros.hpp"
#include "pythonic/include/numpy/float64.hpp"
#include "pythonic/include/__builtin__/None.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <class dtype = functor::float64>
    types::ndarray<typename dtype::type, 2> eye(long N, long M, long k = 0,
                                                dtype d = dtype());

    template <class dtype = functor::float64>
    types::ndarray<typename dtype::type, 2>
    eye(long N, types::none_type M = __builtin__::None, long k = 0,
        dtype d = dtype());

    DECLARE_FUNCTOR(pythonic::numpy, eye);
  }
}

#endif
