//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_XOP_SIMD_FUNCTION_IS_LESS_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_XOP_SIMD_FUNCTION_IS_LESS_EQUAL_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/meta/as_logical.hpp>

#if !defined(_MM_PCOMCTRL_LE)
#define _MM_PCOMCTRL_LE 1
#define BOOST_SIMD_MISSING_MM_PCOMCTRL_LE
#endif

#if BOOST_HW_SIMD_X86_AMD_XOP
namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( is_less_equal_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::int8_<A0>, bs::sse_>
                          , bs::pack_<bd::int8_<A0>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE
    bs::as_logical_t<A0> operator()(const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      #if defined(__clang__)
      return _mm_com_epi8(a0,a1,_MM_PCOMCTRL_LE);
      #else
      return _mm_comle_epi8(a0,a1);
      #endif
    }
  };

  BOOST_DISPATCH_OVERLOAD ( is_less_equal_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::int16_<A0>, bs::sse_>
                          , bs::pack_<bd::int16_<A0>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE
    bs::as_logical_t<A0> operator()(const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      #if defined(__clang__)
      return _mm_com_epi16(a0,a1,_MM_PCOMCTRL_LE);
      #else
      return _mm_comle_epi16(a0,a1);
      #endif
    }
  };

  BOOST_DISPATCH_OVERLOAD ( is_less_equal_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::int32_<A0>, bs::sse_>
                          , bs::pack_<bd::int32_<A0>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE
    bs::as_logical_t<A0> operator()(const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      #if defined(__clang__)
      return _mm_com_epi32(a0,a1,_MM_PCOMCTRL_LE);
      #else
      return _mm_comle_epi32(a0,a1);
      #endif
    }
  };

  BOOST_DISPATCH_OVERLOAD ( is_less_equal_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::int64_<A0>, bs::sse_>
                          , bs::pack_<bd::int64_<A0>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE
    bs::as_logical_t<A0> operator()(const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      #if defined(__clang__)
      return _mm_com_epi64(a0,a1,_MM_PCOMCTRL_LE);
      #else
      return _mm_comle_epi64(a0,a1);
      #endif
    }
  };

  BOOST_DISPATCH_OVERLOAD ( is_less_equal_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::uint8_<A0>, bs::sse_>
                          , bs::pack_<bd::uint8_<A0>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE
    bs::as_logical_t<A0> operator()(const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      #if defined(__clang__)
      return _mm_com_epu8(a0,a1,_MM_PCOMCTRL_LE);
      #else
      return _mm_comle_epu8(a0,a1);
      #endif
    }
  };

  BOOST_DISPATCH_OVERLOAD ( is_less_equal_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::uint16_<A0>, bs::sse_>
                          , bs::pack_<bd::uint16_<A0>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE
    bs::as_logical_t<A0> operator()(const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      #if defined(__clang__)
      return _mm_com_epu16(a0,a1,_MM_PCOMCTRL_LE);
      #else
      return _mm_comle_epu16(a0,a1);
      #endif
    }
  };

  BOOST_DISPATCH_OVERLOAD ( is_less_equal_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::uint32_<A0>, bs::sse_>
                          , bs::pack_<bd::uint32_<A0>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE
    bs::as_logical_t<A0> operator()(const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      #if defined(__clang__)
      return _mm_com_epu32(a0,a1,_MM_PCOMCTRL_LE);
      #else
      return _mm_comle_epu32(a0,a1);
      #endif
    }
  };

  BOOST_DISPATCH_OVERLOAD ( is_less_equal_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::uint64_<A0>, bs::sse_>
                          , bs::pack_<bd::uint64_<A0>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE
    bs::as_logical_t<A0> operator()(const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      #if defined(__clang__)
      return _mm_com_epu64(a0,a1,_MM_PCOMCTRL_LE);
      #else
      return _mm_comle_epu64(a0,a1);
      #endif
    }
  };
} } }
#endif

#if defined(BOOST_SIMD_MISSING_MM_PCOMCTRL_LE)
#undef _MM_PCOMCTRL_LE
#undef BOOST_SIMD_MISSING_MM_PCOMCTRL_LE
#endif

#endif
