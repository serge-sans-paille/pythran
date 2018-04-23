#ifndef PYTHONIC_NUMPY_UINTP_HPP
#define PYTHONIC_NUMPY_UINTP_HPP

#include "pythonic/include/numpy/uintp.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/meta.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include "pythonic/types/numpy_op_helper.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{

  namespace details
  {

    uintptr_t uintp()
    {
      return uintptr_t();
    }

    template <class V>
    uintptr_t uintp(V v)
    {
      return v;
    }
  }

#define NUMPY_NARY_FUNC_NAME uintp
#define NUMPY_NARY_FUNC_SYM details::uintp
#include "pythonic/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
