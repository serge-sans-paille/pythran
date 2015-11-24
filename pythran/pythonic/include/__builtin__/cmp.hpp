#ifndef PYTHONIC_INCLUDE_BUILTIN_CMP_HPP
#define PYTHONIC_INCLUDE_BUILTIN_CMP_HPP

#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {
    template <class T0, class T1>
    long cmp(T0 const &v0, T1 const &v1);

    DECLARE_FUNCTOR(pythonic::__builtin__, cmp);
  }
}

#endif
