#ifndef PYTHONIC_NUMPY_ARCCOS_HPP
#define PYTHONIC_NUMPY_ARCCOS_HPP

#include "pythonic/include/numpy/arccos.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{

  namespace wrapper
  {
    double arccos(long const &v)
    {
      return arccos(static_cast<double>(v));
    }
    template <class T>
    auto arccos(T const &v) -> decltype(boost::simd::acos(v))
    {
      return boost::simd::acos(v);
    }
  }

#define NUMPY_NARY_FUNC_NAME arccos
#define NUMPY_NARY_FUNC_SYM wrapper::arccos
#include "pythonic/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
