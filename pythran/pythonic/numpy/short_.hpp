#ifndef PYTHONIC_NUMPY_SHORT__HPP
#define PYTHONIC_NUMPY_SHORT__HPP

#include "pythonic/include/numpy/short_.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/meta.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include "pythonic/types/numpy_op_helper.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{

  namespace details
  {

    short short_()
    {
      return {};
    }

    template <class V>
    short short_(V v)
    {
      return v;
    }
  }

#define NUMPY_NARY_FUNC_NAME short_
#define NUMPY_NARY_FUNC_SYM details::short_
#include "pythonic/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
