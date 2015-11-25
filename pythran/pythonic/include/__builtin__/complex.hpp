#ifndef PYTHONIC_INCLUDE_BUILTIN_COMPLEX_HPP
#define PYTHONIC_INCLUDE_BUILTIN_COMPLEX_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/complex.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace functor
    {
      struct complex {
        using callable = void;
        using type = std::complex<double>;
        // TODO: do not handle string as first argument
        type operator()(double v0 = 0, double v1 = 0);
      };
    }
  }
}

#endif
