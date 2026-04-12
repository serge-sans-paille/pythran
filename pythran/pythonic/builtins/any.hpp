#ifndef PYTHONIC_BUILTIN_ANY_HPP
#define PYTHONIC_BUILTIN_ANY_HPP

#include "pythonic/include/builtins/any.hpp"

#include "pythonic/utils/functor.hpp"

#include <algorithm>

PYTHONIC_NS_BEGIN

namespace builtins
{
  template <class Iterable>
  bool any(Iterable &&s)
  {
    return std::any_of(std::begin(s), std::end(s), [](auto const &v) { return bool(v); });
  }
} // namespace builtins
PYTHONIC_NS_END

#endif
