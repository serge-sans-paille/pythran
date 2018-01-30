#ifndef PYTHONIC_BUILTIN_ASSERT_HPP
#define PYTHONIC_BUILTIN_ASSERT_HPP

#include "pythonic/include/__builtin__/assert.hpp"

#include "pythonic/types/exceptions.hpp"
#include "pythonic/types/str.hpp"

PYTHONIC_NS_BEGIN

void pythran_assert(bool cond, types::str const &what)
{
#ifndef NDEBUG
  if (!cond)
    throw types::AssertionError(what);
#endif
}
PYTHONIC_NS_END

#endif
