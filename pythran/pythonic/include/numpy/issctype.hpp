#ifndef PYTHONIC_INCLUDE_NUMPY_ISSCTYPE_HPP
#define PYTHONIC_INCLUDE_NUMPY_ISSCTYPE_HPP

#include "pythonic/include/numpy/isscalar.hpp"

PYTHONIC_NS_BEGIN
namespace types
{
  class str;
}

namespace numpy
{
  template <class E>
  constexpr auto issctype(E const &expr)
      -> std::enable_if_t<!types::is_dtype<E>::value && !std::is_same_v<E, types::str>, bool>;

  template <class E>
  constexpr auto issctype(E const &expr)
      -> std::enable_if_t<types::is_dtype<E>::value || std::is_same_v<E, types::str>, bool>;

  DEFINE_FUNCTOR(pythonic::numpy, issctype);
} // namespace numpy
PYTHONIC_NS_END

#endif
