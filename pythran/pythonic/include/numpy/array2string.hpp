#ifndef PYTHONIC_INCLUDE_NUMPY_ARRAY2STRING_HPP
#define PYTHONIC_INCLUDE_NUMPY_ARRAY2STRING_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/str.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E>
    types::str array2string(E &&a);

    DECLARE_FUNCTOR(pythonic::numpy, array2string);
  }
}

#endif
