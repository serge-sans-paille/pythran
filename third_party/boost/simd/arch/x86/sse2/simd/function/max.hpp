//==================================================================================================
/*!
    @file

    @Copyright 2016 Numscale SAS

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_MAX_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_MAX_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( max_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::double_<A0>, bs::sse_>
                          , bs::pack_<bd::double_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0
                                    , const A0 & a1 ) const BOOST_NOEXCEPT
    {
      return _mm_max_pd(a1,a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( max_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::int16_<A0>, bs::sse_>
                          , bs::pack_<bd::int16_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0
                                    , const A0 & a1 ) const BOOST_NOEXCEPT
    {
      return _mm_max_epi16(a0,a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( max_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::uint8_<A0>, bs::sse_>
                          , bs::pack_<bd::uint8_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0
                                    , const A0 & a1 ) const BOOST_NOEXCEPT
    {
      return _mm_max_epu8(a0,a1);
    }
  };

} } }

#endif
