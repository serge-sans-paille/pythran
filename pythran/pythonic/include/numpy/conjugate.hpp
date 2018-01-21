#ifndef PYTHONIC_INCLUDE_NUMPY_CONJUGATE_HPP
#define PYTHONIC_INCLUDE_NUMPY_CONJUGATE_HPP

#include "pythonic/include/types/numpy_op_helper.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace wrapper
  {
    template <class T>
    std::complex<T> conjugate(std::complex<T> const &v)
    {
      return std::conj(v);
    }
    template <class T>
    T conjugate(T const &v)
    {
      return v;
    }
  }
#define NUMPY_NARY_FUNC_NAME conjugate
#define NUMPY_NARY_FUNC_SYM wrapper::conjugate
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
