#ifndef PYTHONIC_INCLUDE_NUMPY_TRACE_HPP
#define PYTHONIC_INCLUDE_NUMPY_TRACE_HPP

#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <class T>
    typename T::dtype trace(T const &expr, int offset = 0);

    DECLARE_FUNCTOR(pythonic::numpy, trace)
  }
}

#endif
