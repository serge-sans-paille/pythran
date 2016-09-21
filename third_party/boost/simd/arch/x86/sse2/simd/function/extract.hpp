//==================================================================================================
/*!
  @file


  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_EXTRACT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_EXTRACT_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/dispatch/adapted/std/integral_constant.hpp>
#include <boost/predef/architecture.h>

namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;

  //------------------------------------------------------------------------------------------------
  BOOST_DISPATCH_OVERLOAD ( extract_
                          , (typename A0, typename A1)
                          , bs::sse2_
                          , bs::pack_<bd::ints8_<A0>, bs::sse_>
                          , bd::constant_<bd::integer_<A1>>
                          )
  {
    BOOST_FORCEINLINE bd::scalar_of_t<A0> operator()(A0 const & a0, A1 const &) const
    {
      int v = _mm_extract_epi16(a0, A1::value / 2);
      return (v >> (8*(A1::value % 2)))& 0xFF;
    }
  };

  //------------------------------------------------------------------------------------------------
  BOOST_DISPATCH_OVERLOAD ( extract_
                          , (typename A0, typename A1)
                          , bs::sse2_
                          , bs::pack_<bd::ints16_<A0>, bs::sse_>
                          , bd::constant_<bd::integer_<A1>>
                          )
  {
    BOOST_FORCEINLINE bd::scalar_of_t<A0> operator()(A0 const & a0, A1 const &) const
    {
      return static_cast<bd::scalar_of_t<A0>>(_mm_extract_epi16(a0, A1::value));
    }
  };

  //------------------------------------------------------------------------------------------------
  BOOST_DISPATCH_OVERLOAD ( extract_
                          , (typename A0, typename A1)
                          , bs::sse2_
                          , bs::pack_<bd::ints32_<A0>, bs::sse_>
                          , bd::constant_<bd::integer_<A1>>
                          )
  {
    BOOST_FORCEINLINE bd::scalar_of_t<A0> operator()(A0 const & a0, A1 const &) const
    {
      return _mm_cvtsi128_si32(_mm_srli_si128(a0, A1::value * 4));
    }
  };

#if BOOST_ARCH_X86_64
  //------------------------------------------------------------------------------------------------
  BOOST_DISPATCH_OVERLOAD ( extract_
                          , (typename A0, typename A1)
                          , bs::sse2_
                          , bs::pack_<bd::ints64_<A0>, bs::sse_>
                          , bd::constant_<bd::integer_<A1>>
                          )
  {
    BOOST_FORCEINLINE bd::scalar_of_t<A0> operator()(A0 const & a0, A1 const &) const
    {
      return _mm_cvtsi128_si64(_mm_srli_si128(a0, A1::value * 8));
    }
  };
#endif

  //------------------------------------------------------------------------------------------------
  BOOST_DISPATCH_OVERLOAD ( extract_
                          , (typename A0, typename A1)
                          , bs::sse2_
                          , bs::pack_<bd::single_<A0>, bs::sse_>
                          , bd::constant_<bd::integer_<A1>>
                          )
  {
    BOOST_FORCEINLINE bd::scalar_of_t<A0> operator()(A0 const & a0, A1 const &) const
    {
      return _mm_cvtss_f32(_mm_castsi128_ps(_mm_srli_si128(_mm_castps_si128(a0), A1::value * 4)));
    }
  };

  //------------------------------------------------------------------------------------------------
  BOOST_DISPATCH_OVERLOAD ( extract_
                          , (typename A0, typename A1)
                          , bs::sse2_
                          , bs::pack_<bd::double_<A0>, bs::sse_>
                          , bd::constant_<bd::integer_<A1>>
                          )
  {
    BOOST_FORCEINLINE bd::scalar_of_t<A0> operator()(A0 const & a0, A1 const &) const
    {
      return _mm_cvtsd_f64(_mm_castsi128_pd(_mm_srli_si128(_mm_castpd_si128(a0), A1::value * 8)));
    }
  };
} } }

#endif
