#ifndef PYTHONIC_NUMPY_BOOL_HPP
#define PYTHONIC_NUMPY_BOOL_HPP

#include "pythonic/include/numpy/bool_.hpp"

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

      bool bool_()
      {
        return bool();
      }

      template <class V>
      bool bool_(V v)
      {
        return v;
      }
    }

#define NUMPY_NARY_FUNC_NAME bool_
#define NUMPY_NARY_FUNC_SYM details::bool_
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
