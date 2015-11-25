#ifndef PYTHONIC_INCLUDE_NUMPY_FROMSTRING_HPP
#define PYTHONIC_INCLUDE_NUMPY_FROMSTRING_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/numpy/float64.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/list.hpp"

#include <limits>
#include <sstream>

namespace pythonic
{

  namespace numpy
  {
    template <class dtype = functor::float64>
    types::ndarray<typename dtype::type, 1>
    fromstring(types::str const &string, dtype d = dtype(), long count = -1,
               types::str const &sep = "");

    DECLARE_FUNCTOR(pythonic::numpy, fromstring);
  }
}

#endif
