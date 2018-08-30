#ifndef PYTHONIC_BUILTIN_SLICE_HPP
#define PYTHONIC_BUILTIN_SLICE_HPP

#include "pythonic/include/__builtin__/slice.hpp"
#include "pythonic/types/slice.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace anonymous
  {
    types::contiguous_slice slice(types::none<long> stop)
    {
      return {types::none<long>(), stop};
    }
    types::contiguous_slice slice(types::none<long> start,
                                  types::none<long> stop)
    {
      return {start, stop};
    }
    types::slice slice(types::none<long> start, types::none<long> stop,
                       types::none<long> step)
    {
      return {start, stop, step};
    }
  }
}
PYTHONIC_NS_END

#endif
