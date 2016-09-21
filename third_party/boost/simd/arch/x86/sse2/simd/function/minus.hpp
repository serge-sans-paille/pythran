//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_MINUS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_MINUS_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;

  BOOST_DISPATCH_OVERLOAD ( minus_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::double_<A0>, bs::sse_>
                          , bs::pack_<bd::double_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0
                                    , const A0 & a1 ) const BOOST_NOEXCEPT
    {
      return _mm_sub_pd(a0,a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( minus_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::ints16_<A0>, bs::sse_>
                          , bs::pack_<bd::ints16_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0
                                    , const A0 & a1 ) const BOOST_NOEXCEPT
    {
      return _mm_sub_epi16(a0,a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( minus_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::ints8_<A0>, bs::sse_>
                          , bs::pack_<bd::ints8_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0
                                    , const A0 & a1 ) const BOOST_NOEXCEPT
    {
      return _mm_sub_epi8(a0,a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( minus_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::ints32_<A0>, bs::sse_>
                          , bs::pack_<bd::ints32_<A0>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0
                                    , const A0 & a1 ) const BOOST_NOEXCEPT
    {
      return _mm_sub_epi32(a0,a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( minus_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::ints64_<A0>, bs::sse_>
                          , bs::pack_<bd::ints64_<A0>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0
                                    , const A0 & a1 ) const BOOST_NOEXCEPT
    {
      return _mm_sub_epi64(a0,a1);
    }
  };
} } }

#include <boost/simd/arch/x86/sse2/simd/function/minus_s.hpp>

#endif
