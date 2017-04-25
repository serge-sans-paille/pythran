#ifndef PYTHONIC_INCLUDE_NUMPY_UNWRAP_HPP
#define PYTHONIC_INCLUDE_NUMPY_UNWRAP_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/utils/int_.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/numpy/pi.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E>
    types::ndarray<double, E::value> unwrap(E const &expr, double discont = pi);

    DECLARE_FUNCTOR(pythonic::numpy, unwrap)
  }
}

#endif
