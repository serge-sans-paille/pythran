//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_INTERLEAVE_EVEN_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_INTERLEAVE_EVEN_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;

  BOOST_DISPATCH_OVERLOAD ( interleave_even_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::double_<A0>, bs::sse_>
                          , bs::pack_<bd::double_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A0 operator()(const A0 & a0, const A0 & a1) const BOOST_NOEXCEPT
    {
      return _mm_unpacklo_pd(a0,a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( interleave_even_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::ints32_<A0>, bs::sse_>
                          , bs::pack_<bd::ints32_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A0 operator()(const A0 & a0, const A0 & a1) const BOOST_NOEXCEPT
    {
      return _mm_unpacklo_epi32 ( _mm_castps_si128(_mm_shuffle_ps ( _mm_castsi128_ps(a0)
                                                                  , _mm_castsi128_ps(a0)
                                                                  , _MM_SHUFFLE(2,0,2,0)
                                                                  )
                                                  )
                                , _mm_castps_si128(_mm_shuffle_ps ( _mm_castsi128_ps(a1)
                                                                  , _mm_castsi128_ps(a1)
                                                                  , _MM_SHUFFLE(2,0,2,0)
                                                                  )
                                                  )
                                );
    }
  };

  BOOST_DISPATCH_OVERLOAD ( interleave_even_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::ints64_<A0>, bs::sse_>
                          , bs::pack_<bd::ints64_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A0 operator()(const A0 & a0, const A0 & a1) const BOOST_NOEXCEPT
    {
      return _mm_unpacklo_epi64(a0,a1);
    }
  };
} } }

#endif
