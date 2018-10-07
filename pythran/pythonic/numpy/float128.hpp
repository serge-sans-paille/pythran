#ifndef PYTHONIC_NUMPY_FLOAT128_HPP
#define PYTHONIC_NUMPY_FLOAT128_HPP

#include "pythonic/include/numpy/float128.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/meta.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include "pythonic/types/numpy_op_helper.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace details
  {

    long double float128()
    {
      return {};
    }

    template <class V>
    long double float128(V v)
    {
      return static_cast<long double>(v);
    }
  }

#define NUMPY_NARY_FUNC_NAME float128
#define NUMPY_NARY_FUNC_SYM details::float128
#include "pythonic/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
