#ifndef PYTHONIC_NUMPY_UINT8_HPP
#define PYTHONIC_NUMPY_UINT8_HPP

#include "pythonic/include/numpy/uint8.hpp"

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

      uint8_t uint8()
      {
        return uint8_t();
      }

      template <class V>
      uint8_t uint8(V v)
      {
        return v;
      }
    }

#define NUMPY_NARY_FUNC_NAME uint8
#define NUMPY_NARY_FUNC_SYM details::uint8
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
