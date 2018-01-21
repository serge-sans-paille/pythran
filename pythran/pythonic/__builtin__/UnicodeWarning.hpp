#ifndef PYTHONIC_BUILTIN_UNICODEWARNING_HPP
#define PYTHONIC_BUILTIN_UNICODEWARNING_HPP

#include "pythonic/include/__builtin__/UnicodeWarning.hpp"

#include "pythonic/types/exceptions.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  PYTHONIC_EXCEPTION_IMPL(UnicodeWarning)
}
PYTHONIC_NS_END

#endif
