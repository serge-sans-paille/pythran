#ifndef PYTHONIC_BUILTIN_PYTHRAN_STATICIFRETURN_HPP
#define PYTHONIC_BUILTIN_PYTHRAN_STATICIFRETURN_HPP

#include "pythonic/include/__builtin__/pythran/StaticIfReturn.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{
  namespace pythran
  {

    template <class T>
    types::StaticIfReturn<T> StaticIfReturn(T const &arg)
    {
      return {arg};
    }
    DEFINE_FUNCTOR(pythonic::__builtin__::pythran, StaticIfReturn);
  }
}
PYTHONIC_NS_END

#endif
