#ifndef PYTHONIC_NUMPY_UINT16_HPP
#define PYTHONIC_NUMPY_UINT16_HPP

#include "pythonic/include/numpy/uint16.hpp"

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

      uint16_t uint16()
      {
        return uint16_t();
      }

      template <class V>
      uint16_t uint16(V v)
      {
        return v;
      }
    }

#define NUMPY_NARY_FUNC_NAME uint16
#define NUMPY_NARY_FUNC_SYM details::uint16
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
