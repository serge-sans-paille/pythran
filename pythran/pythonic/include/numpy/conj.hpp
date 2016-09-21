#ifndef PYTHONIC_INCLUDE_NUMPY_CONJ_HPP
#define PYTHONIC_INCLUDE_NUMPY_CONJ_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/numpy/conjugate.hpp"

namespace pythonic
{

  namespace numpy
  {
    USING_FUNCTOR(conj, numpy::functor::conjugate);
  }
}

#endif
