#ifndef PYTHONIC_INCLUDE_DISPATCH_CLEAR_HPP
#define PYTHONIC_INCLUDE_DISPATCH_CLEAR_HPP

#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace __dispatch__
  {
    template <class Any>
    auto clear(Any &&any) -> decltype(any.clear())
    {
      return any.clear();
    }

    DECLARE_FUNCTOR(pythonic::__dispatch__, clear);
  }
}

#endif
