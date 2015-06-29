#ifndef PYTHONIC_INCLUDE_BUILTIN_ASSERT_HPP
#define PYTHONIC_INCLUDE_BUILTIN_ASSERT_HPP

#include "pythonic/include/types/str.hpp"

namespace pythonic
{
  void pythran_assert(bool cond, types::str const &what = "");
}

#endif
