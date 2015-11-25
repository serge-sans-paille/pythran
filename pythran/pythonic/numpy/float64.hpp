#ifndef PYTHONIC_NUMPY_FLOAT64_HPP
#define PYTHONIC_NUMPY_FLOAT64_HPP

#include "pythonic/include/numpy/float64.hpp"

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

      double float64()
      {
        return double();
      }

      template <class V>
      double float64(V v)
      {
        return v;
      }
    }

#define NUMPY_NARY_FUNC_NAME float64
#define NUMPY_NARY_FUNC_SYM details::float64
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
