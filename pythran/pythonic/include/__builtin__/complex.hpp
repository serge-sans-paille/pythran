#ifndef PYTHONIC_INCLUDE_BUILTIN_COMPLEX_HPP
#define PYTHONIC_INCLUDE_BUILTIN_COMPLEX_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/complex.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace anonymous
    {
      // TODO: do not handle string as first argument
      std::complex<double> complex(double v0 = 0, double v1 = 0);
    }

    PROXY_DECL(pythonic::__builtin__::anonymous, complex);
  }
}

#endif
