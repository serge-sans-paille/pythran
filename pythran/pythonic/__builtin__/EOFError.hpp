#ifndef PYTHONIC_BUILTIN_EOFERROR_HPP
#define PYTHONIC_BUILTIN_EOFERROR_HPP

#include "pythonic/include/__builtin__/EOFError.hpp"

#include "pythonic/types/exceptions.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  PYTHONIC_EXCEPTION_IMPL(EOFError)
}
PYTHONIC_NS_END

#endif
