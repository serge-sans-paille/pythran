#ifndef PYTHONIC_INCLUDE_NUMPY_TRIMZEROS_HPP
#define PYTHONIC_INCLUDE_NUMPY_TRIMZEROS_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/numpy_gexpr.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T>

    types::numpy_gexpr<T, types::contiguous_slice>
    trim_zeros(T const &expr, types::str const &trim = "fb");

    PROXY_DECL(pythonic::numpy, trim_zeros)
  }
}

#endif
