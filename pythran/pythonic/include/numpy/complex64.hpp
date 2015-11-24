#ifndef PYTHONIC_INCLUDE_NUMPY_COMPLEX64_HPP
#define PYTHONIC_INCLUDE_NUMPY_COMPLEX64_HPP

#include "pythonic/include/types/complex.hpp"
#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/utils/meta.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include "pythonic/include/types/numpy_op_helper.hpp"

namespace pythonic
{

  namespace numpy
  {
    namespace details
    {
      std::complex<float> complex64();
      template <class V>
      std::complex<float> complex64(V v);
    }

#define NUMPY_NARY_FUNC_NAME complex64
#define NUMPY_NARY_FUNC_SYM details::complex64
#define NUMPY_NARY_EXTRA_METHOD using type = std::complex<float>;
#include "pythonic/include/types/numpy_nary_expr.hpp"
  }
}

#endif
