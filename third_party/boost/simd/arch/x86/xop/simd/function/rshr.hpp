//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_XOP_SIMD_FUNCTION_RSHR_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_XOP_SIMD_FUNCTION_RSHR_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/rshl.hpp>

#if BOOST_HW_SIMD_X86_AMD_XOP
namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF( rshr_
                            , (typename A0, typename A1)
                            , (nsm::bool_<A0::static_size == A1::static_size>)
                            , bs::avx_
                            , bs::pack_< bd::uint_<A0>, bs::sse_>
                            , bs::pack_< bd::integer_<A1>, bs::sse_>
                            )
  {
    BOOST_FORCEINLINE A0 operator()(A0 const& a0,A1 const& a1) const
    {
      return rshl(a0,-a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( rshr_
                          , (typename A0, typename A1)
                          , bs::avx_
                          , bs::pack_< bd::int8_<A0>, bs::sse_>
                          , bs::pack_< bd::ints8_<A1>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE A0 operator()(A0 const& a0,A1 const& a1) const
    {
      return _mm_sha_epi8(a0,-a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( rshr_
                          , (typename A0, typename A1)
                          , bs::avx_
                          , bs::pack_< bd::int16_<A0>, bs::sse_>
                          , bs::pack_< bd::ints16_<A1>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE A0 operator()(A0 const& a0,A1 const& a1) const
    {
      return _mm_sha_epi16(a0,-a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( rshr_
                          , (typename A0, typename A1)
                          , bs::avx_
                          , bs::pack_< bd::int32_<A0>, bs::sse_>
                          , bs::pack_< bd::ints32_<A1>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE A0 operator()(A0 const& a0,A1 const& a1) const
    {
      return _mm_sha_epi32(a0,-a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( rshr_
                          , (typename A0, typename A1)
                          , bs::avx_
                          , bs::pack_< bd::int64_<A0>, bs::sse_>
                          , bs::pack_< bd::ints64_<A1>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE A0 operator()(A0 const& a0,A1 const& a1) const
    {
      return _mm_sha_epi64(a0,-a1);
    }
  };
} } }
#endif

#endif
