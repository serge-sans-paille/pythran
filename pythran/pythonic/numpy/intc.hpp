#ifndef PYTHONIC_NUMPY_INTC_HPP
#define PYTHONIC_NUMPY_INTC_HPP

#include "pythonic/include/numpy/intc.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/meta.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include "pythonic/types/numpy_op_helper.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{

  namespace details
  {

    int intc()
    {
      return {};
    }

    template <class V>
    int intc(V v)
    {
      return v;
    }
  }

#define NUMPY_NARY_FUNC_NAME intc
#define NUMPY_NARY_FUNC_SYM details::intc
#include "pythonic/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
