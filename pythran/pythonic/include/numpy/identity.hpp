#ifndef PYTHONIC_INCLUDE_NUMPY_IDENTITY_HPP
#define PYTHONIC_INCLUDE_NUMPY_IDENTITY_HPP

#include "pythonic/include/numpy/eye.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <class dtype = double>
    auto identity(long n, dtype d = dtype()) -> decltype(eye(n, n, 0, d));

    PROXY_DECL(pythonic::numpy, identity);
  }
}

#endif
