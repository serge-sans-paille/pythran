#ifndef PYTHONIC_BUILTIN_DEPRECATIONWARNING_HPP
#define PYTHONIC_BUILTIN_DEPRECATIONWARNING_HPP

#include "pythonic/include/__builtin__/DeprecationWarning.hpp"

#include "pythonic/types/exceptions.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  PYTHONIC_EXCEPTION_IMPL(DeprecationWarning)
}
PYTHONIC_NS_END

#endif
