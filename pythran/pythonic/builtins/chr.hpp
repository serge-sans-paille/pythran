#ifndef PYTHONIC_BUILTIN_CHR_HPP
#define PYTHONIC_BUILTIN_CHR_HPP

#include "pythonic/include/builtins/chr.hpp"

#include "pythonic/types/str.hpp"
#include "pythonic/utils/functor.hpp"

#include <type_traits>

PYTHONIC_NS_BEGIN

namespace builtins
{
  template <class T>
  types::str chr(T const &v)
  {
    if constexpr (std::is_integral_v<T>) {
      return types::str((char)v);
    } else {
      static_assert(std::is_void_v<T> && "TypeError: object cannot be interpreted as an integer");
    }
  }
} // namespace builtins

PYTHONIC_NS_END

#endif
