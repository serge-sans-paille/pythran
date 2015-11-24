#ifndef PYTHONIC_NUMPY_INT8_HPP
#define PYTHONIC_NUMPY_INT8_HPP

#include "pythonic/include/numpy/int8.hpp"

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

      int8_t int8()
      {
        return int8_t();
      }

      template <class V>
      int8_t int8(V v)
      {
        return v;
      }
    }

#define NUMPY_NARY_FUNC_NAME int8
#define NUMPY_NARY_FUNC_SYM details::int8
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
