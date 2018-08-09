#ifndef PYTHONIC_INCLUDE_NUMPY_LOG2_HPP
#define PYTHONIC_INCLUDE_NUMPY_LOG2_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace wrapper
  {
    template <class T>
    auto log2(T const &val) -> decltype(std::log(val) / std::log(2))
    {
      return std::log(val) / std::log(2);
    }
  }
#define NUMPY_NARY_FUNC_NAME log2
#define NUMPY_NARY_FUNC_SYM wrapper::log2
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
