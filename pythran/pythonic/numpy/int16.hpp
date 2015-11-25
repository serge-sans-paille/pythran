#ifndef PYTHONIC_NUMPY_INT16_HPP
#define PYTHONIC_NUMPY_INT16_HPP

#include "pythonic/include/numpy/int16.hpp"

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

      int16_t int16()
      {
        return int16_t();
      }

      template <class V>
      int16_t int16(V v)
      {
        return v;
      }
    }

#define NUMPY_NARY_FUNC_NAME int16
#define NUMPY_NARY_FUNC_SYM details::int16
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
