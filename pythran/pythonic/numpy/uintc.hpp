#ifndef PYTHONIC_NUMPY_UINTC_HPP
#define PYTHONIC_NUMPY_UINTC_HPP

#include "pythonic/include/numpy/uintc.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/meta.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include "pythonic/types/numpy_op_helper.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{

  namespace details
  {

    unsigned uintc()
    {
      return {};
    }

    template <class V>
    unsigned uintc(V v)
    {
      return v;
    }
  }

#define NUMPY_NARY_FUNC_NAME uintc
#define NUMPY_NARY_FUNC_SYM details::uintc
#include "pythonic/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
