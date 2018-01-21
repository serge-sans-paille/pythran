#ifndef PYTHONIC_BUILTIN_LOOKUPERROR_HPP
#define PYTHONIC_BUILTIN_LOOKUPERROR_HPP

#include "pythonic/include/__builtin__/LookupError.hpp"

#include "pythonic/types/exceptions.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  PYTHONIC_EXCEPTION_IMPL(LookupError)
}
PYTHONIC_NS_END

#endif
