//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_DEINTERLEAVE_SECOND_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_DEINTERLEAVE_SECOND_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/slice.hpp>
#include <boost/simd/function/combine.hpp>
#include <boost/simd/detail/dispatch/meta/as_floating.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;

  BOOST_DISPATCH_OVERLOAD ( deinterleave_second_
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

      return  bitwise_cast<A0>(f_t( _mm256_unpackhi_pd( _mm256_permute2f128_pd(b0,b1,0x20)
                                                      , _mm256_permute2f128_pd(b0,b1,0x31)
                                                      )
                                  )
                              );
    }
  };

  BOOST_DISPATCH_OVERLOAD ( deinterleave_second_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::type32_<A0>, bs::avx_>
                          , bs::pack_<bd::type32_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE A0 operator()(const A0 & a0, const A0 & a1 ) const BOOST_NOEXCEPT
    {
      using f_t = bd::as_floating_t<A0>;
      auto const b0 = bitwise_cast<f_t>(a0);
      auto const b1 = bitwise_cast<f_t>(a1);

      auto const  x = _mm256_permute2f128_ps(b0,b1,0x20)
                , y = _mm256_permute2f128_ps(b0,b1,0x31);

      return  bitwise_cast<A0>(f_t( _mm256_unpackhi_ps( _mm256_unpacklo_ps(x,y)
                                                  , _mm256_unpackhi_ps(x,y)
                                                  )
                                  )
                              );
    }
  };

  BOOST_DISPATCH_OVERLOAD ( deinterleave_second_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::integer_<A0>, bs::avx_>
                          , bs::pack_<bd::integer_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE A0 operator()(const A0 & a0, const A0 & a1 ) const BOOST_NOEXCEPT
    {
      auto s0 = slice(a0);
      auto s1 = slice(a1);
      return combine( deinterleave_second(std::get<0>(s0),std::get<1>(s0))
                    , deinterleave_second(std::get<0>(s1),std::get<1>(s1))
                    );
    }
  };
} } }

#endif
