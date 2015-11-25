#ifndef PYTHONIC_NUMPY_UINT32_HPP
#define PYTHONIC_NUMPY_UINT32_HPP

#include "pythonic/include/numpy/uint32.hpp"

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

      uint32_t uint32()
      {
        return uint32_t();
      }

      template <class V>
      uint32_t uint32(V v)
      {
        return v;
      }
    }

#define NUMPY_NARY_FUNC_NAME uint32
#define NUMPY_NARY_FUNC_SYM details::uint32
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
