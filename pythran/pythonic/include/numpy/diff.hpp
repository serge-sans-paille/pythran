#ifndef PYTHONIC_INCLUDE_NUMPY_DIFF_HPP
#define PYTHONIC_INCLUDE_NUMPY_DIFF_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/numpy/asarray.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <class E>
    types::ndarray<typename E::dtype, E::value> diff(E const &expr, long n = 1);

    PROXY_DECL(pythonic::numpy, diff);
  }
}

#endif
