#ifndef PYTHONIC_NUMPY_COMPLEX_HPP
#define PYTHONIC_NUMPY_COMPLEX_HPP

#include "pythonic/include/numpy/complex.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/complex.hpp"

namespace pythonic
{

  namespace numpy
  {

    namespace details
    {

      std::complex<double> complex()
      {
        return std::complex<double>();
      }

      std::complex<double> complex(double v, double v2)
      {
        return {v, v2};
      }
    }

#define NUMPY_NARY_FUNC_NAME complex
#define NUMPY_NARY_FUNC_SYM details::complex
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
