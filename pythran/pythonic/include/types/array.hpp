#ifndef PYTHONIC_INCLUDE_TYPES_ARRAY_HPP
#define PYTHONIC_INCLUDE_TYPES_ARRAY_HPP

#include "pythonic/include/types/list.hpp"

PYTHONIC_NS_BEGIN

namespace types
{
  template <class T>
  using dataarray = list<T>;

} // namespace types

PYTHONIC_NS_END

#endif
