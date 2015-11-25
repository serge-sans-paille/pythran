#ifndef PYTHONIC_INCLUDE_BUILTIN_BIN_HPP
#define PYTHONIC_INCLUDE_BUILTIN_BIN_HPP

#include "pythonic/include/utils/functor.hpp"

#include "pythonic/include/types/str.hpp"

namespace pythonic
{

  namespace __builtin__
  {
    template <class T>
    types::str bin(T const &v);

    DECLARE_FUNCTOR(pythonic::__builtin__, bin);
  }
}

#endif
