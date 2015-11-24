#ifndef PYTHONIC_INCLUDE_BUILTIN_LONG_HPP
#define PYTHONIC_INCLUDE_BUILTIN_LONG_HPP

#include "pythonic/include/types/long.hpp"
#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    template <class T>
    pythran_long_t long_(T &&t);

    pythran_long_t long_();

    DECLARE_FUNCTOR(pythonic::__builtin__, long_);
  }
}

#endif
