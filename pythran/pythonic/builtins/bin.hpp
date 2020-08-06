#ifndef PYTHONIC_BUILTIN_BIN_HPP
#define PYTHONIC_BUILTIN_BIN_HPP

#include "pythonic/include/builtins/bin.hpp"

#include "pythonic/types/str.hpp"
#include "pythonic/utils/functor.hpp"

#include <algorithm>
#include <cmath>

PYTHONIC_NS_BEGIN

namespace builtins
{
  template <class T>
  typename std::enable_if<std::is_scalar<T>::value, types::str>::type
  bin(T const &v)
  {
    using UT = typename std::make_unsigned<T>::type;
    if (v == T{0})
      return "0b0";
    else {
      // Due to rounding errors, we cannot use std::log2(v)
      // to accuratly find length.
      size_t len = (8 * sizeof(UT)) - 1;
      UT i{UT{1} << len};
      while (!(i & v)) {
        i >>= 1;
        len--;
      }
      types::str res;
      res.reserve(2 + len);
      auto &backend = res.chars();
      backend.append("0b");
      for (; i; i >>= 1)
        if (v & i)
          backend.append("1");
        else
          backend.append("0");
      return res;
    }
  }
}
PYTHONIC_NS_END

#endif
