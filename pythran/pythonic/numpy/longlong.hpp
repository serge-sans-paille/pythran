#ifndef PYTHONIC_NUMPY_LONGLONG_HPP
#define PYTHONIC_NUMPY_LONGLONG_HPP

#include "pythonic/include/numpy/longlong.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/meta.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include "pythonic/types/numpy_op_helper.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{

  namespace details
  {

    long long longlong()
    {
      return {};
    }

    template <class V>
    long long longlong(V v)
    {
      return v;
    }
  }

#define NUMPY_NARY_FUNC_NAME longlong
#define NUMPY_NARY_FUNC_SYM details::longlong
#include "pythonic/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
