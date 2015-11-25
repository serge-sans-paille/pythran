#ifndef PYTHONIC_INCLUDE_NUMPY_ALEN_HPP
#define PYTHONIC_INCLUDE_NUMPY_ALEN_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T>
    long alen(T &&expr);

    DECLARE_FUNCTOR(pythonic::numpy, alen);
  }
}

#endif
