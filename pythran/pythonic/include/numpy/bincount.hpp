#ifndef PYTHONIC_INCLUDE_NUMPY_BINCOUNT_HPP
#define PYTHONIC_INCLUDE_NUMPY_BINCOUNT_HPP

#include "pythonic/include/numpy/max.hpp"
#include "pythonic/include/utils/numpy_conversion.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class T>
  types::ndarray<long, 1>
      bincount(types::ndarray<T, 1> const &expr,
               types::none_type weights = __builtin__::None,
               types::none<long> minlength = __builtin__::None);

  template <class T, class E>
  types::ndarray<
      decltype(std::declval<long>() * std::declval<typename E::dtype>()), 1>
      bincount(types::ndarray<T, 1> const &expr, E const &weights,
               types::none<long> minlength = __builtin__::None);

  NUMPY_EXPR_TO_NDARRAY0_DECL(bincount);

  DECLARE_FUNCTOR(pythonic::numpy, bincount);
}
PYTHONIC_NS_END

#endif
