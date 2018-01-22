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
  typename details::minmax<sizeof...(Types) == 1, Types...>::result_type
  max(Types &&... values)
  {
    return details::minmax<sizeof...(Types) == 1, Types...>()(
        operator_::functor::lt{}, std::forward<Types>(values)...);
  }

  DEFINE_FUNCTOR(pythonic::__builtin__, max);
}
PYTHONIC_NS_END

#endif
