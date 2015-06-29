#ifndef PYTHONIC_BUILTIN_COMPLEX_CONJUGATE_HPP
#define PYTHONIC_BUILTIN_COMPLEX_CONJUGATE_HPP

#include "pythonic/include/builtins/complex/conjugate.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/numpy/conjugate.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace complex
    {

      ALIAS(conjugate, numpy::proxy::conjugate{});

      PROXY_IMPL(pythonic::builtins::complex, conjugate);
    }
  }
}
#endif
