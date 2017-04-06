//==================================================================================================
/*!
    @file

    @Copyright 2016 Numscale SAS

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE1_SCALAR_FUNCTION_RSQRT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE1_SCALAR_FUNCTION_RSQRT_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/function/raw.hpp>
#include <boost/simd/function/pedantic.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/if_nan_else.hpp>
#include <boost/simd/function/if_zero_else.hpp>
#include <boost/simd/function/is_eqz.hpp>
#include <boost/simd/function/is_ltz.hpp>
#include <boost/simd/function/refine_rsqrt.hpp>
#include <boost/simd/constant/inf.hpp>
#include <boost/simd/detail/constant/denormalfactor.hpp>
#include <boost/simd/detail/constant/denormalsqrtfactor.hpp>
#include <boost/simd/constant/smallestposval.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/constant/inf.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;
  BOOST_DISPATCH_OVERLOAD ( rsqrt_
                          , (typename A0)
                          , bs::sse1_
                          , bs::raw_tag
                          , bd::scalar_<bd::single_<A0>>
                          )
  {
    BOOST_FORCEINLINE A0 operator() (raw_tag const&
                                    , const A0 & a0) const BOOST_NOEXCEPT
    {
      float inv;
      _mm_store_ss( &inv, _mm_rsqrt_ss( _mm_load_ss( &a0 ) ) );
      return inv;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( rsqrt_
                          , (typename A0)
                          , bs::sse1_
                          , bs::raw_tag
                          , bd::scalar_<bd::double_<A0>>
                          )
  {
    BOOST_FORCEINLINE A0 operator() (raw_tag const&
                                    , const A0 & a0) const BOOST_NOEXCEPT
    {
      float inv = a0;
      _mm_store_ss( &inv, _mm_rsqrt_ss( _mm_load_ss( &inv ) ) );
      return double(inv);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( rsqrt_
                          , (typename A0)
                          , bs::sse1_
                          , bd::scalar_<bd::single_<A0>>
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const A0 & a00) const BOOST_NOEXCEPT
    {
      if (is_eqz(a00)) return Inf<A0>();
      #ifndef BOOST_SIMD_NO_INFINITIES
      if (a00 == Inf<A0>()) return Zero<A0>();
      #endif
      A0 a0 =  raw_(rsqrt)(a00);
      A0 y = sqr(a0)*a00;
      return a0*Ratio<A0, 1, 8>()*fnms(y, fnms(A0(3), y, A0(10)), A0(15)); //this is Halley cubically convergent iteration
    }
  };

  BOOST_DISPATCH_OVERLOAD ( rsqrt_
                          , (typename A0)
                          , bs::sse1_
                          , bs::pedantic_tag
                          , bd::scalar_<bd::single_<A0>>
                          )
  {
    BOOST_FORCEINLINE A0 operator() (pedantic_tag const&
                                    ,const A0 & a00) const BOOST_NOEXCEPT
    {
      if (is_eqz(a00)) return Inf<A0>();
      #ifndef BOOST_SIMD_NO_INFINITIES
      if (a00 == Inf<A0>()) return Zero<A0>();
      #endif
      A0 a0 = a00;
      auto is_den = bs::abs(a00) < Smallestposval<A0>();
      #ifndef BOOST_SIMD_NO_DENORMALS
      a0 *= if_else(is_den, Denormalfactor<A0>(), One<A0>());
      #endif
      a0 = refine_rsqrt(a0, refine_rsqrt(a0, raw_(rsqrt)(a0)));// Two Newton is sometimes better than one halley
      #ifndef BOOST_SIMD_NO_DENORMALS
      a0 *= if_else(is_den, Denormalsqrtfactor<A0>(), One<A0>());
      #endif
      return a0;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( rsqrt_
                          , (typename A0)
                          , bs::sse1_
                          , bs::pedantic_tag
                          , bd::scalar_<bd::double_<A0>>
                          )
  {
    BOOST_FORCEINLINE A0 operator() (pedantic_tag const&
                                    ,const A0 & a00) const BOOST_NOEXCEPT
    {
      if (is_eqz(a00)) return Inf<A0>();
      #ifndef BOOST_SIMD_NO_INFINITIES
      if (a00 == Inf<A0>()) return Zero<A0>();
      #endif
      A0 a01 =  a00;
      auto is_den = bs::abs(a00) < Smallestposval<A0>();
      #ifndef BOOST_SIMD_NO_DENORMALS
      a01 *= if_else(is_den, Denormalfactor<A0>(), One<A0>());
      #endif
      A0 a0 =  raw_(rsqrt)(a01);
      A0 y = sqr(a0)*a01;
      a0 = a0*Ratio<A0, 1, 8>()*fnms(y, fnms(A0(3), y, A0(10)), A0(15)); //this is Halley cubically convergent iteration
      a0 = refine_rsqrt(a00, a0);//this is Newton iteration
      #ifndef BOOST_SIMD_NO_DENORMALS
      a0 *= if_else(is_den, Denormalsqrtfactor<A0>(), One<A0>());
      #endif
      return a0;
    }
  };
} } }

#endif

