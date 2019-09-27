#ifndef PYTHONIC_BUILTIN_MAX_HPP
#define PYTHONIC_BUILTIN_MAX_HPP

#include "pythonic/include/__builtin__/max.hpp"
#include "pythonic/__builtin__/minmax.hpp"

#include "pythonic/operator_/lt.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  template <class... Types>
  auto max(Types &&... values)
      -> decltype(details::minmax(operator_::functor::lt{},
                                  std::forward<Types>(values)...))
  {
    return details::minmax(operator_::functor::lt{},
                           std::forward<Types>(values)...);
  }
}
PYTHONIC_NS_END

#endif
