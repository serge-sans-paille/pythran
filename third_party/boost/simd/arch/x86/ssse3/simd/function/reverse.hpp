
//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSSE3_SIMD_FUNCTION_REVERSE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSSE3_SIMD_FUNCTION_REVERSE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;
  BOOST_DISPATCH_OVERLOAD ( reverse_
                          , (typename A0)
                          , bs::ssse3_
                          , bs::pack_<bd::int8_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0) const BOOST_NOEXCEPT
    {
      return _mm_shuffle_epi8(a0, _mm_set_epi8( 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( reverse_
                          , (typename A0)
                          , bs::ssse3_
                          , bs::pack_<bd::int16_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0) const BOOST_NOEXCEPT
    {
      return _mm_shuffle_epi8(a0, _mm_set_epi8( 1, 0, 3, 2, 5, 4, 7, 6, 9, 8,11,10,13,12,15,14));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( reverse_
                          , (typename A0)
                          , bs::ssse3_
                          , bs::pack_<bd::int32_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0) const BOOST_NOEXCEPT
    {
      return _mm_shuffle_epi8(a0, _mm_set_epi8(3, 2, 1, 0, 7, 6,  5, 4,11,10, 9, 8,15,14,13,12));
    }
  };
  BOOST_DISPATCH_OVERLOAD ( reverse_
                          , (typename A0)
                          , bs::ssse3_
                          , bs::pack_<bd::int64_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0) const BOOST_NOEXCEPT
    {
      return _mm_shuffle_epi8(a0, _mm_set_epi8(7, 6,  5, 4, 3, 2, 1, 0,15,14,13,12,11,10, 9, 8));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( reverse_
                          , (typename A0)
                          , bs::ssse3_
                          , bs::pack_<bd::unsigned_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0) const BOOST_NOEXCEPT
    {
      return bitwise_cast<A0>(reverse(bitwise_cast<bd::as_integer_t<A0, signed>>(a0)));
    }
  };
} } }

#endif
