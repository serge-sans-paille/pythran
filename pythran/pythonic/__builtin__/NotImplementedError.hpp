#ifndef PYTHONIC_BUILTIN_NOTIMPLEMENTEDERROR_HPP
#define PYTHONIC_BUILTIN_NOTIMPLEMENTEDERROR_HPP

#include "pythonic/include/__builtin__/NotImplementedError.hpp"

#include "pythonic/types/exceptions.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  PYTHONIC_EXCEPTION_IMPL(NotImplementedError)
}
PYTHONIC_NS_END

#endif
