//==================================================================================================
/*!
    @file

    @Copyright 2016 Numscale SAS

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_RSQRT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_RSQRT_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/raw.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/if_nan_else.hpp>
#include <boost/simd/function/if_zero_else.hpp>
#include <boost/simd/function/is_eqz.hpp>
#include <boost/simd/function/is_ltz.hpp>
#include <boost/simd/function/refine_rsqrt.hpp>
#include <boost/simd/constant/inf.hpp>
#include <boost/simd/constant/ratio.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;
  BOOST_DISPATCH_OVERLOAD ( rsqrt_
                          , (typename A0)
                          , bs::sse2_
                          , bs::raw_tag
                          , bs::pack_<bd::double_<A0>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE A0 operator() (raw_tag const&
                                    , const A0 & a0) const BOOST_NOEXCEPT
    {
      return _mm_cvtps_pd(_mm_rsqrt_ps(_mm_cvtpd_ps(a0))); //The maximum error for this approximation is 1.5e-12
    }
  };

   BOOST_DISPATCH_OVERLOAD ( rsqrt_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::double_<A0>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const A0 & a00) const BOOST_NOEXCEPT
    {
      // To obtain accuracy we need 3 Newton steps or one Halley step followed by one Newton from the raw estimate
      // the second method is a bit faster by half a cycle
      A0 a0 =  raw_(rsqrt)(a00);
      A0 y = sqr(a0)*a00;
      a0 = a0*Ratio<A0, 1, 8>()*fnms(y, fnms(A0(3), y, A0(10)), A0(15)); //this is Halley cubically convergent iteration
      a0 = refine_rsqrt(a00, a0);
#ifndef BOOST_SIMD_NO_INFINITIES
      a0 = if_zero_else(a00 == Inf<A0>(),a0);
#endif
      return if_else(is_eqz(a00), Inf<A0>(), a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( rsqrt_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pedantic_tag
                          , bs::pack_<bd::double_<A0>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE A0 operator() (pedantic_tag const&
                                    ,const A0 & a00) const BOOST_NOEXCEPT
    {
      A0 a01 =  a00;
      auto is_den = bs::abs(a00) < Smallestposval<A0>();
      #ifndef BOOST_SIMD_NO_DENORMALS
      a01 *= if_else(is_den, Denormalfactor<A0>(), One<A0>());
      #endif
      A0 a0 =  raw_(rsqrt)(a01);
      A0 y = sqr(a0)*a01;
      a0 = a0*Ratio<A0, 1, 8>()*fnms(y, fnms(A0(3), y, A0(10)), A0(15)); //this is Halley cubically convergent iteration
      a0 = refine_rsqrt(a00, a0);
      #ifndef BOOST_SIMD_NO_DENORMALS
      a0 *= if_else(is_den, Denormalsqrtfactor<A0>(), One<A0>());
      #endif

      #ifndef BOOST_SIMD_NO_INFINITIES
      a0 = if_zero_else(a00 == Inf<A0>(),a0);
      #endif
      return if_else(is_eqz(a00), Inf<A0>(), a0);
    }
  };
} } }

#endif

