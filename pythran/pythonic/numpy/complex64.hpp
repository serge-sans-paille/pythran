#ifndef PYTHONIC_NUMPY_COMPLEX64_HPP
#define PYTHONIC_NUMPY_COMPLEX64_HPP

#include "pythonic/include/numpy/complex64.hpp"

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

      std::complex<float> complex64()
      {
        return {};
      }

      template <class V>
      std::complex<float> complex64(V v)
      {
        return v;
      }
    }

#define NUMPY_NARY_FUNC_NAME complex64
#define NUMPY_NARY_FUNC_SYM details::complex64
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
