#ifndef PYTHONIC_BUILTIN_SLICE_HPP
#define PYTHONIC_BUILTIN_SLICE_HPP

#include "pythonic/include/__builtin__/slice.hpp"
#include "pythonic/types/slice.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace anonymous
  {
    types::contiguous_slice<types::none_type, long> slice(long stop)
    {
      return {{}, stop};
    }
    types::contiguous_slice<types::none_type, types::none_type>
    slice(types::none_type stop)
    {
      return {{}, {}};
    }
    types::contiguous_slice<types::none_type, long>
    slice(types::none<long> stop)
    {
      return {{}, stop.is_none ? std::numeric_limits<long>::max() : (long)stop};
    }

    types::contiguous_slice<types::none_type, long>
    slice(types::none_type start, long stop)
    {
      return {{}, stop};
    }
    types::contiguous_slice<types::none_type, types::none_type>
    slice(types::none_type start, types::none_type stop)
    {
      return {{}, {}};
    }
    types::contiguous_slice<types::none_type, long>
    slice(types::none_type start, types::none<long> stop)
    {
      return {{}, stop.is_none ? std::numeric_limits<long>::max() : (long)stop};
    }
    types::contiguous_slice<long, long> slice(long start, long stop)
    {
      return {start, stop};
    }
    types::contiguous_slice<long, types::none_type> slice(long start,
                                                          types::none_type stop)
    {
      return {start, {}};
    }
    types::contiguous_slice<long, long> slice(long start,
                                              types::none<long> stop)
    {
      return {start,
              stop.is_none ? std::numeric_limits<long>::max() : (long)stop};
    }
    types::contiguous_slice<long, long> slice(types::none<long> start,
                                              long stop)
    {
      return {start.is_none ? 0L : (long)start, stop};
    }
    types::contiguous_slice<long, types::none_type>
    slice(types::none<long> start, types::none_type stop)
    {
      return {start.is_none ? 0L : (long)start, stop};
    }
    types::contiguous_slice<long, long> slice(types::none<long> start,
                                              types::none<long> stop)
    {
      return {start.is_none ? 0L : (long)start,
              stop.is_none ? std::numeric_limits<long>::max() : (long)stop};
    }

    types::contiguous_slice<types::none_type, long>
    slice(types::none_type start, long stop, types::none_type)
    {
      return {{}, stop};
    }
    types::contiguous_slice<types::none_type, types::none_type>
    slice(types::none_type start, types::none_type stop, types::none_type)
    {
      return {{}, {}};
    }
    types::contiguous_slice<types::none_type, long>
    slice(types::none_type start, types::none<long> stop, types::none_type)
    {
      return {{}, stop.is_none ? std::numeric_limits<long>::max() : (long)stop};
    }
    types::contiguous_slice<long, long> slice(long start, long stop,
                                              types::none_type)
    {
      return {start, stop};
    }
    types::contiguous_slice<long, types::none_type>
    slice(long start, types::none_type stop, types::none_type)
    {
      return {start, {}};
    }
    types::contiguous_slice<long, long>
    slice(long start, types::none<long> stop, types::none_type)
    {
      return {start,
              stop.is_none ? std::numeric_limits<long>::max() : (long)stop};
    }
    types::contiguous_slice<long, long> slice(types::none<long> start,
                                              long stop, types::none_type)
    {
      return {start.is_none ? 0L : (long)start, stop};
    }
    types::contiguous_slice<long, types::none_type>
    slice(types::none<long> start, types::none_type stop, types::none_type)
    {
      return {start.is_none ? 0L : (long)start, stop};
    }
    types::contiguous_slice<long, long>
    slice(types::none<long> start, types::none<long> stop, types::none_type)
    {
      return {start.is_none ? 0L : (long)start,
              stop.is_none ? std::numeric_limits<long>::max() : (long)stop};
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
