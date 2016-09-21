//==================================================================================================
/*!
    @file

    @Copyright 2016 Numscale SAS

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE4_1_SIMD_FUNCTION_IF_ELSE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE4_1_SIMD_FUNCTION_IF_ELSE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/genmask.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;

  BOOST_DISPATCH_OVERLOAD ( if_else_
                          , (typename A0, typename A1)
                          , bs::sse4_1_
                          , bs::pack_<bs::logical_<A0>, bs::sse_>
                          , bs::pack_<bd::single_<A1>, bs::sse_>
                          , bs::pack_<bd::single_<A1>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A1 operator() ( const A0 & a0
                                    , const A1 & a1
                                    , const A1 & a2) const BOOST_NOEXCEPT
    {
      return _mm_blendv_ps(a2, a1, bitwise_cast<A1>(genmask(a0)));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( if_else_
                          , (typename A0, typename A1)
                          , bs::sse4_1_
                          , bs::pack_<bs::logical_<A0>, bs::sse_>
                          , bs::pack_<bd::double_<A1>, bs::sse_>
                          , bs::pack_<bd::double_<A1>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A1 operator() ( const A0 & a0
                                    , const A1 & a1
                                    , const A1 & a2) const BOOST_NOEXCEPT
    {
      return _mm_blendv_pd(a2, a1, bitwise_cast<A1>(genmask(a0)));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( if_else_
                          , (typename A0, typename A1)
                          , bs::sse4_1_
                          , bs::pack_<bs::logical_<A0>, bs::sse_>
                          , bs::pack_<bd::integer_<A1>, bs::sse_>
                          , bs::pack_<bd::integer_<A1>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A1 operator() ( const A0 & a0
                                    , const A1 & a1
                                    , const A1 & a2) const BOOST_NOEXCEPT
    {
      return _mm_blendv_epi8(a2, a1, bitwise_cast<A1>(genmask(a0)));
    }
  };
} } }

#endif
