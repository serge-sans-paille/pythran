#ifndef PYTHONIC_BUILTIN_ALL_HPP
#define PYTHONIC_BUILTIN_ALL_HPP

#include "pythonic/include/builtins/all.hpp"
#include "pythonic/utils/functor.hpp"

#include <algorithm>

PYTHONIC_NS_BEGIN

namespace builtins
{

  template <class Iterable>
  bool all(Iterable &&s)
  {
    return std::all_of(std::begin(s), std::end(s), [](auto const &x) { return bool(x); });
  }
} // namespace builtins
PYTHONIC_NS_END

#endif
