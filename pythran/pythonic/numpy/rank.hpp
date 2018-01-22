#ifndef PYTHONIC_NUMPY_RANK_HPP
#define PYTHONIC_NUMPY_RANK_HPP

#include "pythonic/include/numpy/rank.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class E>
  size_t rank(E const &expr)
  {
    return E::value;
  }

  DEFINE_FUNCTOR(pythonic::numpy, rank);
}
PYTHONIC_NS_END

#endif
