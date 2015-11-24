#ifndef PYTHONIC_NUMPY_LINSPACE_HPP
#define PYTHONIC_NUMPY_LINSPACE_HPP

#include "pythonic/include/numpy/linspace.hpp"

#include "pythonic/numpy/arange.hpp"

namespace pythonic
{

  namespace numpy
  {
    types::ndarray<double, 1> linspace(double start, double stop, long num,
                                       bool endpoint)
    {
      double step = (stop - start) / (num - (endpoint ? 1 : 0));
      return arange(start, stop + (endpoint ? step * .5 : 0), step);
    }

    DEFINE_FUNCTOR(pythonic::numpy, linspace);
  }
}

#endif
