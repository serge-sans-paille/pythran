#ifndef PYTHONIC_BUILTIN_CMP_HPP
#define PYTHONIC_BUILTIN_CMP_HPP

#include "pythonic/include/__builtin__/cmp.hpp"

#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {
    template <class T0, class T1>
    long cmp(T0 const &v0, T1 const &v1)
    {
      return v0 == v1 ? 0 : (v0 < v1 ? -1 : 1);
    }

    DEFINE_FUNCTOR(pythonic::__builtin__, cmp);
  }
}

#endif
