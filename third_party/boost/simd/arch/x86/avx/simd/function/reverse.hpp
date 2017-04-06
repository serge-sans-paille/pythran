//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_REVERSE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_REVERSE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/combine.hpp>
#include <boost/simd/function/slice.hpp>
#include <boost/simd/detail/dispatch/meta/as_floating.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;

  BOOST_DISPATCH_OVERLOAD ( reverse_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::type64_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE A0 operator()( const A0 & a0 ) const BOOST_NOEXCEPT
    {
      using f_t = bd::as_floating_t<A0>;
      auto const b0 = bitwise_cast<f_t>(a0);
      return bitwise_cast<A0>(f_t(_mm256_permute_pd( _mm256_permute2f128_pd(b0,b0,1), 5 )));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( reverse_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::type32_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE A0 operator()( const A0 & a0 ) const BOOST_NOEXCEPT
    {
      using f_t = bd::as_floating_t<A0>;
      auto const b0 = bitwise_cast<f_t>(a0);
      auto const tmp = _mm256_permute_ps(b0, _MM_SHUFFLE(0,1,2,3) );
      return bitwise_cast<A0>(f_t(_mm256_permute2f128_ps(tmp,tmp,1)));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( reverse_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::fundamental_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE A0 operator()( const A0 & a0 ) const BOOST_NOEXCEPT
    {
      return combine( reverse(slice_high(a0)), reverse(slice_low(a0)) );
    }
  };
} } }

#endif
