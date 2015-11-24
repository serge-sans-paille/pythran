#ifndef PYTHONIC_NUMPY_COMPLEX_HPP
#define PYTHONIC_NUMPY_COMPLEX_HPP

#include "pythonic/include/numpy/complex.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/complex.hpp"

namespace pythonic
{

  namespace numpy
  {

    std::complex<double> complex()
    {
      return std::complex<double>();
    }

    DEFINE_FUNCTOR(pythonic::numpy, complex);
  }
}

#endif
