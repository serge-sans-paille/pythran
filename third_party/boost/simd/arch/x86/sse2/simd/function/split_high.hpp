//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_SPLIT_HIGH_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_SPLIT_HIGH_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/is_ltz.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/detail/dispatch/meta/upgrade.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_OVERLOAD ( split_high_, (typename A0), bs::sse2_
                          , bs::pack_<bd::single_<A0>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE bd::upgrade_t<A0> operator()(const A0& a0) const BOOST_NOEXCEPT
    {
      return _mm_cvtps_pd(_mm_movehl_ps(a0, a0));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( split_high_, (typename A0), bs::sse2_
                          , bs::pack_<bd::int8_<A0>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE bd::upgrade_t<A0> operator()(const A0& a0) const BOOST_NOEXCEPT
    {
      return _mm_unpackhi_epi8(a0, is_ltz(a0));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( split_high_, (typename A0), bs::sse2_
                          , bs::pack_<bd::uint8_<A0>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE bd::upgrade_t<A0> operator()(const A0& a0) const BOOST_NOEXCEPT
    {
      return _mm_unpackhi_epi8(a0, Zero<A0>());
    }
  };

  BOOST_DISPATCH_OVERLOAD ( split_high_, (typename A0), bs::sse2_
                          , bs::pack_<bd::int16_<A0>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE bd::upgrade_t<A0> operator()(const A0& a0) const BOOST_NOEXCEPT
    {
      return _mm_unpackhi_epi16(a0, is_ltz(a0));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( split_high_, (typename A0), bs::sse2_
                          , bs::pack_<bd::uint16_<A0>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE bd::upgrade_t<A0> operator()(const A0& a0) const BOOST_NOEXCEPT
    {
      return _mm_unpackhi_epi16(a0, Zero<A0>());
    }
  };

  BOOST_DISPATCH_OVERLOAD ( split_high_, (typename A0), bs::sse2_
                          , bs::pack_<bd::int32_<A0>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE bd::upgrade_t<A0> operator()(const A0& a0) const BOOST_NOEXCEPT
    {
      return _mm_unpackhi_epi32(a0, is_ltz(a0));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( split_high_, (typename A0), bs::sse2_
                          , bs::pack_<bd::uint32_<A0>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE bd::upgrade_t<A0> operator()(const A0& a0) const BOOST_NOEXCEPT
    {
      return _mm_unpackhi_epi32(a0, Zero<A0>());
    }
  };
} } }

#endif
