#ifndef PYTHONIC_DISPATCH_COPY_HPP
#define PYTHONIC_DISPATCH_COPY_HPP

#include "pythonic/include/__dispatch__/copy.hpp"

#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __dispatch__
  {
    template <class Any>
    auto copy(Any const &any) -> decltype(any.copy())
    {
      return any.copy();
    }

    DEFINE_FUNCTOR(pythonic::__dispatch__, copy);
  }
}

#endif
