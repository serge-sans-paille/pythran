#ifndef PYTHONIC_NUMPY_IDENTITY_HPP
#define PYTHONIC_NUMPY_IDENTITY_HPP

#include "pythonic/include/numpy/identity.hpp"

#include "pythonic/numpy/eye.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class dtype>
    auto identity(long n, dtype d) -> decltype(eye(n, n, 0, d))
    {
      return eye(n, n, 0, d);
    }

    DEFINE_FUNCTOR(pythonic::numpy, identity);
  }
}

#endif
