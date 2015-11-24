#ifndef PYTHONIC_BUILTIN_NEXT_HPP
#define PYTHONIC_BUILTIN_NEXT_HPP

#include "pythonic/include/__builtin__/next.hpp"

#include "pythonic/__builtin__/StopIteration.hpp"
#include "pythonic/utils/functor.hpp"

#include <utility>

namespace pythonic
{

  namespace __builtin__
  {

    template <class T>
    auto next(T &&y) -> decltype(*y)
    {
      if ((decltype(y.begin()))y != y.end()) {
        auto &&tmp = *y;
        ++y;
        return tmp;
      } else
        throw types::StopIteration();
    }

    DEFINE_FUNCTOR(pythonic::__builtin__, next);
  }
}

#endif
