#ifndef PYTHONIC_BUILTIN_STOPITERATION_HPP
#define PYTHONIC_BUILTIN_STOPITERATION_HPP

#include "pythonic/include/__builtin__/StopIteration.hpp"

#include "pythonic/types/exceptions.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  PYTHONIC_EXCEPTION_IMPL(StopIteration)
}
PYTHONIC_NS_END

#endif
