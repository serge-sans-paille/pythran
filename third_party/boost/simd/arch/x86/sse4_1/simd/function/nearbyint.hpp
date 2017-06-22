//==================================================================================================
/**
    Copyright 2016 Numscale SAS

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE4_1_SIMD_FUNCTION_NEARBYINT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE4_1_SIMD_FUNCTION_NEARBYINT_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;
  BOOST_DISPATCH_OVERLOAD ( nearbyint_
                          , (typename A0)
                          , bs::sse4_1_
                          , bs::pack_<bd::single_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0) const BOOST_NOEXCEPT
    {
      return  _mm_round_ps(a0, _MM_FROUND_TO_NEAREST_INT);
    }
  };
  BOOST_DISPATCH_OVERLOAD ( nearbyint_
                          , (typename A0)
                          , bs::sse4_1_
                          , bs::pack_<bd::double_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0) const BOOST_NOEXCEPT
    {
       return  _mm_round_pd(a0, _MM_FROUND_TO_NEAREST_INT);
    }
  };

} } }

#endif
