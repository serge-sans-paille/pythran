#ifndef PYTHONIC_BUILTIN_LONG_HPP
#define PYTHONIC_BUILTIN_LONG_HPP

#include "pythonic/include/__builtin__/long_.hpp"

#include "pythonic/types/long.hpp"
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    template <class T>
    pythran_long_t long_(T &&t)
    {
      return t;
    }

    pythran_long_t long_()
    {
      return 0;
    }

    DEFINE_FUNCTOR(pythonic::__builtin__, long_);
  }
}

#endif
