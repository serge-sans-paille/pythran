#ifndef PYTHONIC_BUILTIN_MIN_HPP
#define PYTHONIC_BUILTIN_MIN_HPP

#include "pythonic/include/__builtin__/min.hpp"
#include "pythonic/__builtin__/minmax.hpp"

#include "pythonic/operator_/gt.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  template <class... Types>
  auto min(Types &&... values)
      -> decltype(details::minmax(operator_::functor::gt{},
                                  std::forward<Types>(values)...))
  {
    return details::minmax(operator_::functor::gt{},
                           std::forward<Types>(values)...);
  }
}
PYTHONIC_NS_END

#endif
