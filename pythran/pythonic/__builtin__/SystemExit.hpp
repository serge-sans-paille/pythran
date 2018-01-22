#ifndef PYTHONIC_BUILTIN_SYSTEMEXIT_HPP
#define PYTHONIC_BUILTIN_SYSTEMEXIT_HPP

#include "pythonic/include/__builtin__/SystemExit.hpp"

#include "pythonic/types/exceptions.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  PYTHONIC_EXCEPTION_IMPL(SystemExit)
}
PYTHONIC_NS_END

#endif
