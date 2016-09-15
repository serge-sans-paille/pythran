//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE1_SIMD_FUNCTION_SUM_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE1_SIMD_FUNCTION_SUM_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/splatted.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;

  BOOST_DISPATCH_OVERLOAD ( sum_
                          , (typename A0)
                          , bs::sse1_
                          , bs::pack_<bd::single_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE float operator() ( const A0 & a0 ) const BOOST_NOEXCEPT
    {
      // We optimize this by saving a movaps and 2-3 uops by using movehl instead of second shuffle
      __m128  shuf  = _mm_shuffle_ps(a0, a0, _MM_SHUFFLE(2, 3, 0, 1));
      __m128  sums  = _mm_add_ps(a0, shuf);

      return _mm_cvtss_f32(_mm_add_ss(sums, _mm_movehl_ps(shuf, sums)));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( sum_
                          , (typename A0)
                          , bs::sse1_
                          , bs::splatted_tag
                          , bs::pack_<bd::arithmetic_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A0 operator()(bs::splatted_tag const&, const A0 & a0 ) const BOOST_NOEXCEPT
    {
      return A0(sum(a0));
    }
  };
} } }

#endif
