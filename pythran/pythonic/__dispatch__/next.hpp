#ifndef PYTHONIC_DISPATCH_NEXT_HPP
#define PYTHONIC_DISPATCH_NEXT_HPP

#include "pythonic/include/__dispatch__/next.hpp"

#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __dispatch__
{

  template <class Any>
  auto next(Any &&any) -> decltype(any.next())
  {
    return any.next();
  }

  DEFINE_FUNCTOR(pythonic::__dispatch__, next);
}
PYTHONIC_NS_END

#endif
