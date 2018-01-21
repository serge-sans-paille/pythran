#ifndef PYTHONIC_INCLUDE_DISPATCH_NEXT_HPP
#define PYTHONIC_INCLUDE_DISPATCH_NEXT_HPP

#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __dispatch__
{

  template <class Any>
  auto next(Any &&any) -> decltype(any.next());

  DECLARE_FUNCTOR(pythonic::__dispatch__, next);
}
PYTHONIC_NS_END

#endif
