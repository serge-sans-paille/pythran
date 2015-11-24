#ifndef PYTHONIC_NUMPY_UINT64_HPP
#define PYTHONIC_NUMPY_UINT64_HPP

#include "pythonic/include/numpy/uint64.hpp"

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

      uint64_t uint64()
      {
        return uint64_t();
      }

      template <class V>
      uint64_t uint64(V v)
      {
        return v;
      }
    }

#define NUMPY_NARY_FUNC_NAME uint64
#define NUMPY_NARY_FUNC_SYM details::uint64
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
