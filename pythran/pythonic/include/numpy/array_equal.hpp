#ifndef PYTHONIC_INCLUDE_NUMPY_ARRAYEQUAL_HPP
#define PYTHONIC_INCLUDE_NUMPY_ARRAYEQUAL_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/numpy/all.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <class U, class V>
    bool array_equal(U const &u, V const &v);

    PROXY_DECL(pythonic::numpy, array_equal);
  }
}

#endif
