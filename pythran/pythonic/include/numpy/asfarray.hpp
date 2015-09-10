#ifndef PYTHONIC_INCLUDE_NUMPY_ASFARRAY_HPP
#define PYTHONIC_INCLUDE_NUMPY_ASFARRAY_HPP

#include "pythonic/include/numpy/asarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E, class dtype = double>
    auto asfarray(E &&e, dtype d = dtype())
        -> decltype(asarray(std::forward<E>(e), d));
    PROXY_DECL(pythonic::numpy, asfarray);
  }
}

#endif
