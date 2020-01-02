#ifndef PYTHONIC_INCLUDE_BUILTIN_SLICE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SLICE_HPP

#include "pythonic/include/types/slice.hpp"
#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace builtins
{

  namespace anonymous
  {
    types::contiguous_slice slice(types::none<long> stop);
    types::contiguous_slice slice(types::none<long> start,
                                  types::none<long> stop);
    types::slice slice(types::none<long> start, types::none<long> stop,
                       types::none<long> step);
  }

  DEFINE_FUNCTOR(pythonic::builtins::anonymous, slice);
}
PYTHONIC_NS_END

#endif
