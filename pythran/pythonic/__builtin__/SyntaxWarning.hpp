#ifndef PYTHONIC_BUILTIN_SYNTAXWARNING_HPP
#define PYTHONIC_BUILTIN_SYNTAXWARNING_HPP

#include "pythonic/include/__builtin__/SyntaxWarning.hpp"

#include "pythonic/types/exceptions.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  PYTHONIC_EXCEPTION_IMPL(SyntaxWarning)
}
PYTHONIC_NS_END

#endif
