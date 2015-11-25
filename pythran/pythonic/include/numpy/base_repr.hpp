#ifndef PYTHONIC_INCLUDE_NUMPY_BASEREPR_HPP
#define PYTHONIC_INCLUDE_NUMPY_BASEREPR_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {

    types::str base_repr(long number, long base = 2, long padding = 0);

    DECLARE_FUNCTOR(pythonic::numpy, base_repr);
  }
}

#endif
