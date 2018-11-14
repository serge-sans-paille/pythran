#ifndef PYTHONIC_INCLUDE_NUMPY_ARGSORT_HPP
#define PYTHONIC_INCLUDE_NUMPY_ARGSORT_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class T, class pS>
  types::ndarray<long, pS> argsort(types::ndarray<T, pS> const &a);

  NUMPY_EXPR_TO_NDARRAY0_DECL(argsort);

  DEFINE_FUNCTOR(pythonic::numpy, argsort);
}
PYTHONIC_NS_END

#endif
