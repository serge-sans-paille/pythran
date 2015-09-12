#ifndef PYTHONIC_INCLUDE_NUMPY_COMPLEX_HPP
#define PYTHONIC_INCLUDE_NUMPY_COMPLEX_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/complex.hpp"

namespace pythonic
{

  namespace numpy
  {

    std::complex<double> complex();

    PROXY_DECL(pythonic::numpy, complex);
  }
}

#endif
