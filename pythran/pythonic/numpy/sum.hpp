#ifndef PYTHONIC_NUMPY_SUM_HPP
#define PYTHONIC_NUMPY_SUM_HPP

#include "pythonic/include/numpy/sum.hpp"
#include "pythonic/numpy/reduce.hpp"
#include "pythonic/operator_/iadd.hpp"
#include "pythonic/utils/functor.hpp"

#include <algorithm>

PYTHONIC_NS_BEGIN

namespace numpy
{

  template <class... Args>
  auto sum(Args &&... args)
      -> decltype(reduce<operator_::functor::iadd>(std::forward<Args>(args)...))
  {
    return reduce<operator_::functor::iadd>(std::forward<Args>(args)...);
  }

  DEFINE_FUNCTOR(pythonic::numpy, sum);
}
PYTHONIC_NS_END

#endif
