#ifndef PYTHONIC_INCLUDE_BUILTIN_CHR_HPP
#define PYTHONIC_INCLUDE_BUILTIN_CHR_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/str.hpp"

namespace pythonic
{

  namespace __builtin__
  {
    template <class T>
    types::str chr(T const &v);

    DECLARE_FUNCTOR(pythonic::__builtin__, chr);
  }
}

#endif
