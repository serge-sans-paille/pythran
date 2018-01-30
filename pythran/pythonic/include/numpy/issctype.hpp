#ifndef PYTHONIC_INCLUDE_NUMPY_ISSCTYPE_HPP
#define PYTHONIC_INCLUDE_NUMPY_ISSCTYPE_HPP

#include "pythonic/include/numpy/isscalar.hpp"

PYTHONIC_NS_BEGIN
namespace types
{
  struct str;
}

namespace numpy
{
  template <class E>
  constexpr auto issctype(E const &expr) ->
      typename std::enable_if<!types::is_dtype<E>::value &&
                                  !std::is_same<E, types::str>::value,
                              bool>::type;

  template <class E>
  constexpr auto issctype(E const &expr) ->
      typename std::enable_if<types::is_dtype<E>::value ||
                                  std::is_same<E, types::str>::value,
                              bool>::type;

  DECLARE_FUNCTOR(pythonic::numpy, issctype);
}
PYTHONIC_NS_END

#endif
