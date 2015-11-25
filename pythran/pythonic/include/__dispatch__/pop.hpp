#ifndef PYTHONIC_INCLUDE_DISPATCH_POP_HPP
#define PYTHONIC_INCLUDE_DISPATCH_POP_HPP

#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace __dispatch__
  {
    template <class Any, class... Arg0>
    auto pop(Any &&any, Arg0 &&... arg0)
        -> decltype(any.pop(std::forward<Arg0>(arg0)...));

    DECLARE_FUNCTOR(pythonic::__dispatch__, pop);
  }
}

#endif
