#ifndef PYTHONIC_INCLUDE_NUMPY_LINSPACE_HPP
#define PYTHONIC_INCLUDE_NUMPY_LINSPACE_HPP

#include "pythonic/include/numpy/arange.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{

  types::ndarray<double, types::pshape<long>>
  linspace(double start, double stop, long num = 50, bool endpoint = true);

  DEFINE_FUNCTOR(pythonic::numpy, linspace);
}
PYTHONIC_NS_END

#endif
