#ifndef PYTHONIC_INCLUDE_NUMPY_ISREALOBJ_HPP
#define PYTHONIC_INCLUDE_NUMPY_ISREALOBJ_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/traits.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E>
    constexpr bool isrealobj(E const &expr);

    PROXY_DECL(pythonic::numpy, isrealobj);
  }
}

#endif
