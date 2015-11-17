#ifndef PYTHONIC_INCLUDE_NUMPY_ASFARRAY_HPP
#define PYTHONIC_INCLUDE_NUMPY_ASFARRAY_HPP

#include "pythonic/include/numpy/asarray.hpp"
#include "pythonic/include/numpy/float64.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E, class dtype = proxy::float64>
    auto asfarray(E &&e, dtype d = dtype())
        -> decltype(asarray(std::forward<E>(e), d));
    PROXY_DECL(pythonic::numpy, asfarray);
  }
}

#endif
