#ifndef PYTHONIC_BUILTIN_ASSERT_HPP
#define PYTHONIC_BUILTIN_ASSERT_HPP

#include "pythonic/include/__builtin__/assert.hpp"

#include "pythonic/types/exceptions.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic
{

  void pythran_assert(bool cond, types::str const &what)
  {
#ifndef NDEBUG
    if (not cond)
      throw types::AssertionError(what);
#endif
  }
}

#endif
