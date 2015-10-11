#ifndef PYTHONIC_INCLUDE_UTILS_NUMPY_CONVERSION_HPP
#define PYTHONIC_INCLUDE_UTILS_NUMPY_CONVERSION_HPP

#include "pythonic/include/utils/numpy_traits.hpp"

#include <utility>

#define NUMPY_EXPR_TO_NDARRAY0_DECL(fname)                                     \
  template <class E, class... Types>                                           \
  auto fname(E const &expr, Types &&... others)                                \
      ->typename std::enable_if<                                               \
          not types::is_ndarray<E>::value and types::is_array<E>::value,       \
          decltype(fname(types::ndarray<typename E::dtype, E::value>{expr},    \
                         std::forward<Types>(others)...))>::type;

#endif
