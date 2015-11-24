#ifndef PYTHONIC_INCLUDE_NUMPY_COMPLEX_HPP
#define PYTHONIC_INCLUDE_NUMPY_COMPLEX_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/complex.hpp"

namespace pythonic
{

  namespace numpy
  {

    std::complex<double> complex();

    DECLARE_FUNCTOR(pythonic::numpy, complex);
  }
}

#endif
