#ifndef PYTHONIC_NUMPY_FLOAT_HPP
#define PYTHONIC_NUMPY_FLOAT_HPP

#include "pythonic/include/numpy/float_.hpp"

#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace numpy
  {

    double float_()
    {
      return 0.;
    }

    PROXY_IMPL(pythonic::numpy, float_);
  }
}

#endif
