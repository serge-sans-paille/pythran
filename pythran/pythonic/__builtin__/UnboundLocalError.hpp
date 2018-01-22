#ifndef PYTHONIC_BUILTIN_UNBOUNDLOCALERROR_HPP
#define PYTHONIC_BUILTIN_UNBOUNDLOCALERROR_HPP

#include "pythonic/include/__builtin__/UnboundLocalError.hpp"

#include "pythonic/types/exceptions.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  PYTHONIC_EXCEPTION_IMPL(UnboundLocalError)
}
PYTHONIC_NS_END

#endif
