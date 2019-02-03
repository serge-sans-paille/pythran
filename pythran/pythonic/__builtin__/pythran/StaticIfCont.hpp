#ifndef PYTHONIC_BUILTIN_PYTHRAN_STATICIFCONT_HPP
#define PYTHONIC_BUILTIN_PYTHRAN_STATICIFCONT_HPP

#include "pythonic/include/__builtin__/pythran/StaticIfCont.hpp"
#include "pythonic/utils/functor.hpp"
#include "pythonic/types/static_if.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace pythran
  {
    template <class T>
    types::StaticIfCont<T> StaticIfCont(T const &arg)
    {
      return {arg};
    }
  }
}
PYTHONIC_NS_END

#endif
