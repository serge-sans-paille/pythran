//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_REPEAT_LOWER_HALF_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_REPEAT_LOWER_HALF_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/interleave_first.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;

  BOOST_DISPATCH_OVERLOAD ( repeat_lower_half_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::ints32_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0 ) const BOOST_NOEXCEPT
    {
      return _mm_shuffle_epi32(a0, _MM_SHUFFLE(1,0,1,0) );
    }
  };

  BOOST_DISPATCH_OVERLOAD ( repeat_lower_half_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::type64_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0 ) const BOOST_NOEXCEPT
    {
      return interleave_first(a0,a0);
    }
  };
} } }

#endif

