#ifndef PYTHONIC_INCLUDE_NUMPY_TRACE_HPP
#define PYTHONIC_INCLUDE_NUMPY_TRACE_HPP

#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <class T>
    typename T::dtype trace(T const &expr, int offset = 0);

    PROXY_DECL(pythonic::numpy, trace)
  }
}

#endif
