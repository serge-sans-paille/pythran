#ifndef PYTHONIC_NUMPY_COMPLEX128_HPP
#define PYTHONIC_NUMPY_COMPLEX128_HPP

#include "pythonic/include/numpy/complex128.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/meta.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include "pythonic/types/numpy_op_helper.hpp"

namespace pythonic
{

  namespace numpy
  {
    namespace details
    {

      std::complex<double> complex128()
      {
        return {};
      }

      template <class V>
      std::complex<double> complex128(V v)
      {
        return v;
      }
    }

#define NUMPY_NARY_FUNC_NAME complex128
#define NUMPY_NARY_FUNC_SYM details::complex128
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
