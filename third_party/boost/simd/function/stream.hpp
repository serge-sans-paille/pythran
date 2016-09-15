//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_FUNCTION_STREAM_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_STREAM_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @brief Stream a value in memory

    Store a given value into an arbitrary memory location referenced by either
    a pointer or a pointer and an offset without polluting the caches.

    @par Semantic:

    stream semantic is similar to store semantic except for the fact that no
    cache pollution occurs on architecture that support such memory operations.
    On other architecture, stream is simply an alias for store.

    @param val    Value to stream
    @param ptr    Memory location to stream @c val to
    @param offset Optional memory offset.
  **/
  template<typename Value, typename Pointer, typename Offset>
  void stream(Value const& val, Pointer const& ptr, Offset const& offset)
  {}

  /// @overload
  template<typename Value, typename Pointer>
  void stream(Value const& val, Pointer const& ptr)
  {}
} }
#endif

#include <boost/simd/function/scalar/stream.hpp>
#include <boost/simd/function/simd/stream.hpp>

#endif
