#ifndef PYTHONIC_INCLUDE_BUILTIN_MIN_HPP
#define PYTHONIC_INCLUDE_BUILTIN_MIN_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/__builtin__/minmax.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{
  template <class... Types>
  typename details::minmax<sizeof...(Types) == 1, Types...>::result_type
  min(Types &&... values);

  DECLARE_FUNCTOR(pythonic::__builtin__, min);
}
PYTHONIC_NS_END

#endif
