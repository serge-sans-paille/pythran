#ifndef PYTHONIC_INCLUDE_NUMPY_ISSCTYPE_HPP
#define PYTHONIC_INCLUDE_NUMPY_ISSCTYPE_HPP

#include "pythonic/include/numpy/isscalar.hpp"

namespace pythonic
{
  namespace types
  {
    struct str;
  }

  namespace numpy
  {
    template <class E>
    constexpr auto issctype(E const &expr) ->
        typename std::enable_if<not types::is_dtype<E>::value and
                                    not std::is_same<E, types::str>::value,
                                bool>::type;

    template <class E>
    constexpr auto issctype(E const &expr) ->
        typename std::enable_if<types::is_dtype<E>::value or
                                    std::is_same<E, types::str>::value,
                                bool>::type;

    DECLARE_FUNCTOR(pythonic::numpy, issctype);
  }
}

#endif
