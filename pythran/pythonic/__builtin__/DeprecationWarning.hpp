#ifndef PYTHONIC_BUILTIN_DEPRECATIONWARNING_HPP
#define PYTHONIC_BUILTIN_DEPRECATIONWARNING_HPP

#include "pythonic/include/__builtin__/DeprecationWarning.hpp"

#include "pythonic/types/exceptions.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    PYTHONIC_EXCEPTION_IMPL(DeprecationWarning)
  }
}

#endif
