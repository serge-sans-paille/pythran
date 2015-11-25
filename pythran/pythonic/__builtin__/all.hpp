#ifndef PYTHONIC_BUILTIN_ALL_HPP
#define PYTHONIC_BUILTIN_ALL_HPP

#include "pythonic/utils/functor.hpp"
#include "pythonic/include/__builtin__/all.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    template <class Iterable>
    bool all(Iterable &&s)
    {
      auto iend = s.end();
      for (auto iter = s.begin(); iter != iend; ++iter)
        if (not*iter)
          return false;
      return true;
    }
    DEFINE_FUNCTOR(pythonic::__builtin__, all);
  }
}

#endif
