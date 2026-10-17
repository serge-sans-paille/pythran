#ifndef PYTHONIC_DISPATCH_ADD_HPP
#define PYTHONIC_DISPATCH_ADD_HPP

#include "pythonic/include/__dispatch__/add.hpp"

#include "pythonic/types/NoneType.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __dispatch__
{

  template <class Any, class Arg>
  types::none_type add(Any &&any, Arg &&arg)
  {
    std::forward<Any>(any).add(std::forward<Arg>(arg));
    return {};
  }
} // namespace __dispatch__
PYTHONIC_NS_END

#endif
