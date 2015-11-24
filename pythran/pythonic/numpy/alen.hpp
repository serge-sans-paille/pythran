#ifndef PYTHONIC_NUMPY_ALEN_HPP
#define PYTHONIC_NUMPY_ALEN_HPP

#include "pythonic/include/numpy/alen.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T>
    long alen(T &&expr)
    {
      return expr.shape()[0];
    }

    DEFINE_FUNCTOR(pythonic::numpy, alen);
  }
}

#endif
