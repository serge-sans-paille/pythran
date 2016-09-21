//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_INTERLEAVE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_INTERLEAVE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/slice.hpp>
#include <boost/simd/function/combine.hpp>
#include <boost/simd/function/interleave_first.hpp>
#include <boost/simd/function/interleave_second.hpp>
#include <boost/simd/detail/dispatch/meta/as_floating.hpp>
#include <array>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;

  BOOST_DISPATCH_OVERLOAD ( interleave_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::type64_<A0>, bs::avx_>
                          , bs::pack_<bd::type64_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE std::array<A0,2> operator()(A0 const& a0, A0 const& a1 ) const BOOST_NOEXCEPT
    {
      auto b0 = bitwise_cast<bd::as_floating_t<A0>>(a0);
      auto b1 = bitwise_cast<bd::as_floating_t<A0>>(a1);
      auto lo = _mm256_unpacklo_pd(b0,b1);
      auto hi = _mm256_unpackhi_pd(b0,b1);
      auto f  =  bitwise_cast<A0>( _mm256_permute2f128_pd( lo, hi, 0x20 ) );
      auto s  =  bitwise_cast<A0>( _mm256_permute2f128_pd( lo, hi, 0x31 ) );

      return {f,s};
    }
  };

  BOOST_DISPATCH_OVERLOAD ( interleave_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::type32_<A0>, bs::avx_>
                          , bs::pack_<bd::type32_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE std::array<A0,2> operator()(A0 const& a0, A0 const& a1 ) const BOOST_NOEXCEPT
    {
      auto b0 = bitwise_cast<bd::as_floating_t<A0>>(a0);
      auto b1 = bitwise_cast<bd::as_floating_t<A0>>(a1);
      auto lo = _mm256_unpacklo_ps(b0,b1);
      auto hi = _mm256_unpackhi_ps(b0,b1);
      auto f  =  bitwise_cast<A0>( _mm256_permute2f128_ps( lo, hi, 0x20 ) );
      auto s  =  bitwise_cast<A0>( _mm256_permute2f128_ps( lo, hi, 0x31 ) );

      return {f,s};
    }
  };

  BOOST_DISPATCH_OVERLOAD ( interleave_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::integer_<A0>, bs::avx_>
                          , bs::pack_<bd::integer_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE std::array<A0,2> operator()(A0 const& a0, A0 const& a1 ) const BOOST_NOEXCEPT
    {
      auto x0 = slice_low(a0);
      auto y0 = slice_low(a1);
      auto f  = combine ( interleave_first(x0,y0)
                      , interleave_first( slide<A0::static_size/4>(x0)
                                        , slide<A0::static_size/4>(y0)
                                        )
                      );

      x0 = slice_high(a0);
      y0 = slice_high(a1);

      auto s =  combine ( interleave_first(x0,y0)
                        , interleave_first( slide<A0::static_size/4>(x0)
                                          , slide<A0::static_size/4>(y0)
                                          )
                        );

      return {f,s};
    }
  };
} } }

#endif
