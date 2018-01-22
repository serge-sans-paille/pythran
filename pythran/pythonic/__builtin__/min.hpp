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
  typename details::minmax<sizeof...(Types) == 1, Types...>::result_type
  min(Types &&... values)
  {
    return details::minmax<sizeof...(Types) == 1, Types...>()(
        operator_::functor::gt{}, std::forward<Types>(values)...);
  }

  DEFINE_FUNCTOR(pythonic::__builtin__, min);
}
PYTHONIC_NS_END

#endif
