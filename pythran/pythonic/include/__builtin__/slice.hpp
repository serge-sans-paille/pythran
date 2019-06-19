#ifndef PYTHONIC_INCLUDE_BUILTIN_SLICE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SLICE_HPP

#include "pythonic/include/types/slice.hpp"
#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace anonymous
  {
    types::contiguous_slice<types::none_type, long> slice(long stop);
    types::contiguous_slice<types::none_type, types::none_type>
    slice(types::none_type stop);
    types::contiguous_slice<types::none_type, long>
    slice(types::none<long> stop);

    types::contiguous_slice<types::none_type, long>
    slice(types::none_type start, long stop);
    types::contiguous_slice<types::none_type, types::none_type>
    slice(types::none_type start, types::none_type stop);
    types::contiguous_slice<types::none_type, long>
    slice(types::none_type start, types::none<long> stop);
    types::contiguous_slice<long, long> slice(long start, long stop);
    types::contiguous_slice<long, types::none_type>
    slice(long start, types::none_type stop);
    types::contiguous_slice<long, long> slice(long start,
                                              types::none<long> stop);
    types::contiguous_slice<long, long> slice(types::none<long> start,
                                              long stop);
    types::contiguous_slice<long, types::none_type>
    slice(types::none<long> start, types::none_type stop);
    types::contiguous_slice<long, long> slice(types::none<long> start,
                                              types::none<long> stop);

    types::contiguous_slice<types::none_type, long>
    slice(types::none_type start, long stop, types::none_type);
    types::contiguous_slice<types::none_type, types::none_type>
    slice(types::none_type start, types::none_type stop, types::none_type);
    types::contiguous_slice<types::none_type, long>
    slice(types::none_type start, types::none<long> stop, types::none_type);
    types::contiguous_slice<long, long> slice(long start, long stop,
                                              types::none_type);
    types::contiguous_slice<long, types::none_type>
    slice(long start, types::none_type stop, types::none_type);
    types::contiguous_slice<long, long>
    slice(long start, types::none<long> stop, types::none_type);
    types::contiguous_slice<long, long> slice(types::none<long> start,
                                              long stop, types::none_type);
    types::contiguous_slice<long, types::none_type>
    slice(types::none<long> start, types::none_type stop, types::none_type);
    types::contiguous_slice<long, long>
    slice(types::none<long> start, types::none<long> stop, types::none_type);

    types::slice slice(types::none<long> start, types::none<long> stop,
                       types::none<long> step);
  }

  DEFINE_FUNCTOR(pythonic::__builtin__::anonymous, slice);
}
PYTHONIC_NS_END

#endif
