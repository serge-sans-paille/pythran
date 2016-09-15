//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE3_SIMD_FUNCTION_SUM_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE3_SIMD_FUNCTION_SUM_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;

  BOOST_DISPATCH_OVERLOAD ( sum_
                          , (typename A0)
                          , bs::sse3_
                          , bs::pack_<bd::single_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE float operator() ( const A0 & a0 ) const BOOST_NOEXCEPT
    {
      // Use hdup to be faster than shuffle in SSE2
      __m128  bf   = _mm_movehdup_ps(a0);
      __m128  sums = _mm_add_ps(a0, bf);
      return _mm_cvtss_f32(_mm_add_ss(sums, _mm_movehl_ps(bf, sums)));
    }
  };
} } }

#endif
