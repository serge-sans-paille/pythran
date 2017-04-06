//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_INTERLEAVE_SECOND_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_INTERLEAVE_SECOND_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/slice_high.hpp>
#include <boost/simd/function/combine.hpp>
#include <boost/simd/function/slide.hpp>
#include <boost/simd/detail/dispatch/meta/as_floating.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;

  BOOST_DISPATCH_OVERLOAD ( interleave_second_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::type64_<A0>, bs::avx_>
                          , bs::pack_<bd::type64_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE A0 operator()(const A0 & a0, const A0 & a1 ) const BOOST_NOEXCEPT
    {
      using f_t = bd::as_floating_t<A0>;
      auto b0 = bitwise_cast<f_t>(a0);
      auto b1 = bitwise_cast<f_t>(a1);

      // 0x31 is SCR1[128:255]|SRC2[128:255] according to Intel AVX manual
      // The result of unpack_*_ps puts parts in the proper pairs beforehand
      return  bitwise_cast<A0>(f_t( _mm256_permute2f128_pd( _mm256_unpacklo_pd(b0,b1)
                                                      , _mm256_unpackhi_pd(b0,b1)
                                                      , 0x31
                                                      )
                                  )
                              );
    }
  };

  BOOST_DISPATCH_OVERLOAD ( interleave_second_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::type32_<A0>, bs::avx_>
                          , bs::pack_<bd::type32_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE A0 operator()(const A0 & a0, const A0 & a1 ) const BOOST_NOEXCEPT
    {
      using f_t = bd::as_floating_t<A0>;
      auto b0 = bitwise_cast<f_t>(a0);
      auto b1 = bitwise_cast<f_t>(a1);

      // 0x31 is SCR1[128:255]|SRC2[128:255] according to Intel AVX manual
      // The result of unpack_*_ps puts parts in the proper pairs beforehand
      return  bitwise_cast<A0>(f_t( _mm256_permute2f128_ps( _mm256_unpacklo_ps(b0,b1)
                                                      , _mm256_unpackhi_ps(b0,b1)
                                                      , 0x31
                                                      )
                                  )
                              );
    }
  };

  BOOST_DISPATCH_OVERLOAD ( interleave_second_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::integer_<A0>, bs::avx_>
                          , bs::pack_<bd::integer_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE A0 operator()(const A0 & a0, const A0 & a1 ) const BOOST_NOEXCEPT
    {
      auto x0 = slice_high(a0);
      auto y0 = slice_high(a1);

      return  combine ( interleave_first(x0,y0)
                      , interleave_first(slide<A0::static_size/4>(x0), slide<A0::static_size/4>(y0))
                      );
    }
  };
} } }

#endif
