#ifndef PYTHONIC_BUILTIN_ANY_HPP
#define PYTHONIC_BUILTIN_ANY_HPP

#include "pythonic/include/__builtin__/any.hpp"

#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {
    template <class Iterable>
    bool any(Iterable &&s)
    {
      auto iend = s.end();
      for (auto iter = s.begin(); iter != iend; ++iter)
        if (*iter)
          return true;
      return false;
    }

    DEFINE_FUNCTOR(pythonic::__builtin__, any);
  }
}

#endif
