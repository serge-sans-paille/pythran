//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_INTERLEAVE_EVEN_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_INTERLEAVE_EVEN_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/bitwise_cast.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;

  BOOST_DISPATCH_OVERLOAD ( interleave_even_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::type64_<A0>, bs::avx_>
                          , bs::pack_<bd::type64_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE A0 operator()(const A0 & a0, const A0 & a1 ) const BOOST_NOEXCEPT
    {
      using f_t = bd::as_floating_t<A0>;
      return  bitwise_cast<A0>(f_t( _mm256_unpacklo_pd( bitwise_cast<f_t>(a0)
                                                  , bitwise_cast<f_t>(a1)
                                                  )
                                  )
                              );
    }
  };

  BOOST_DISPATCH_OVERLOAD ( interleave_even_
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
      return  bitwise_cast<A0>(f_t( _mm256_unpacklo_ps( _mm256_shuffle_ps(b0, b0, _MM_SHUFFLE(3,1,2,0))
                                                  , _mm256_shuffle_ps(b1, b1, _MM_SHUFFLE(3,1,2,0))
                                                  )
                                  )
                              );
    }
  };

  BOOST_DISPATCH_OVERLOAD ( interleave_even_
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
      return  combine(interleave_even(s0[0],s1[0]), interleave_even(s0[1],s1[1]));
    }
  };
} } }

#endif
