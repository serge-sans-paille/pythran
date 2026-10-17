#ifndef PYTHONIC_INCLUDE_DISPATCH_ADD_HPP
#define PYTHONIC_INCLUDE_DISPATCH_ADD_HPP

#include "pythonic/include/types/NoneType.hpp"
#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __dispatch__
{

  template <class Any, class Arg>
  types::none_type add(Any &&any, Arg &&arg0);

  DEFINE_FUNCTOR(pythonic::__dispatch__, add);
} // namespace __dispatch__
PYTHONIC_NS_END

#endif
