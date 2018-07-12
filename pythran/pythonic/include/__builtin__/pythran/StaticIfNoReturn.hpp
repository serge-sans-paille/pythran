#ifndef PYTHONIC_INCLUDE_BUILTIN_PYTHRAN_STATICIFNORETURN_HPP
#define PYTHONIC_INCLUDE_BUILTIN_PYTHRAN_STATICIFNORETURN_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/static_if.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace pythran
  {
    template <class T>
    types::StaticIfNoReturn<T> StaticIfNoReturn(T const &arg);

    DEFINE_FUNCTOR(pythonic::__builtin__::pythran, StaticIfNoReturn);
  }
}

PYTHONIC_NS_END

#endif
