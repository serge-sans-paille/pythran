#ifndef PYTHONIC_INCLUDE_BUILTIN_COMPLEX_CONJUGATE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_COMPLEX_CONJUGATE_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/numpy/conjugate.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace complex
    {

      ALIAS_DECL(conjugate, numpy::proxy::conjugate{});

      PROXY_DECL(pythonic::__builtin__::complex, conjugate);
    }
  }
}
#endif
