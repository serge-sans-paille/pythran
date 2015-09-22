#ifndef PYTHONIC_INCLUDE_NUMPY_REAL_HPP
#define PYTHONIC_INCLUDE_NUMPY_REAL_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E>
    auto real(E &&expr) -> decltype(
        __builtin__::getattr<types::attr::REAL>(std::forward<E>(expr)));

    PROXY_DECL(pythonic::numpy, real);
  }
}

#endif
