#ifndef PYTHONIC_INCLUDE_BUILTIN_MIN_HPP
#define PYTHONIC_INCLUDE_BUILTIN_MIN_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/operator_/gt.hpp"
#include "pythonic/include/__builtin__/minmax.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{
  template <class... Types>
  auto min(Types &&... values)
      -> decltype(details::minmax(operator_::functor::gt{},
                                  std::forward<Types>(values)...));

  DEFINE_FUNCTOR(pythonic::__builtin__, min);
}
PYTHONIC_NS_END

#endif
