#ifndef PYTHONIC_INCLUDE_NUMPY_RANK_HPP
#define PYTHONIC_INCLUDE_NUMPY_RANK_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class E>
  long rank(E const &expr);

  DEFINE_FUNCTOR(pythonic::numpy, rank);
}
PYTHONIC_NS_END

#endif
