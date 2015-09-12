#ifndef PYTHONIC_INCLUDE_NUMPY_RANK_HPP
#define PYTHONIC_INCLUDE_NUMPY_RANK_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E>
    size_t rank(E const &expr);

    PROXY_DECL(pythonic::numpy, rank);
  }
}

#endif
