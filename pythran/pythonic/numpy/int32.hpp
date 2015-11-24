#ifndef PYTHONIC_NUMPY_INT32_HPP
#define PYTHONIC_NUMPY_INT32_HPP

#include "pythonic/include/numpy/int32.hpp"

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

      int32_t int32()
      {
        return int32_t();
      }

      template <class V>
      int32_t int32(V v)
      {
        return v;
      }
    }

#define NUMPY_NARY_FUNC_NAME int32
#define NUMPY_NARY_FUNC_SYM details::int32
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
