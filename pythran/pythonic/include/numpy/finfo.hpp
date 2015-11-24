#ifndef PYTHONIC_INCLUDE_NUMPY_FINFO_HPP
#define PYTHONIC_INCLUDE_NUMPY_FINFO_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/numpy/float64.hpp"
#include "pythonic/include/types/finfo.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class dtype = functor::float64>
    types::finfo<typename dtype::type> finfo(dtype d = dtype());

    DECLARE_FUNCTOR(pythonic::numpy, finfo)
  }
}

#endif
