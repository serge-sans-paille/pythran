#ifndef PYTHONIC_BUILTIN_COMPLEX_HPP
#define PYTHONIC_BUILTIN_COMPLEX_HPP

#include "pythonic/include/__builtin__/complex.hpp"

#include "pythonic/types/complex.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace anonymous
    {
      std::complex<double> complex(double v0, double v1)
      {
        return {v0, v1};
      }
    }

    PROXY_IMPL(pythonic::__builtin__::anonymous, complex);
  }
}

#endif
