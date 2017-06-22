//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_XOP_SIMD_FUNCTION_MULTIPLIES_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_XOP_SIMD_FUNCTION_MULTIPLIES_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/function/saturated.hpp>

#if BOOST_HW_SIMD_X86_AMD_XOP
namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( multiplies_
                          , (typename A0)
                          , bs::avx_
                          , bs::saturated_tag
                          , bs::pack_<bd::int16_<A0>, bs::sse_>
                          , bs::pack_<bd::int16_<A0>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE A0 operator()( const saturated_tag &
                                   , const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      return _mm_maccs_epi16(a0,a1,Zero<A0>());
    }
  };

  BOOST_DISPATCH_OVERLOAD ( multiplies_
                          , (typename A0)
                          , bs::avx_
                          , bs::saturated_tag
                          , bs::pack_<bd::int32_<A0>, bs::sse_>
                          , bs::pack_<bd::int32_<A0>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE A0 operator()( const saturated_tag &
                                   , const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      return _mm_maccs_epi32(a0,a1,Zero<A0>());
    }
  };
} } }
#endif

#endif
