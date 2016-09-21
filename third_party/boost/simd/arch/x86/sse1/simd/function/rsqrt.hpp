//==================================================================================================
/*!
    @file

    @Copyright 2016 Numscale SAS

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE1_SIMD_FUNCTION_RSQRT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE1_SIMD_FUNCTION_RSQRT_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/fnma.hpp>
#include <boost/simd/function/sqr.hpp>
#include <boost/simd/function/fast.hpp>
#include <boost/simd/constant/half.hpp>
#include <boost/simd/constant/mthree.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;
  BOOST_DISPATCH_OVERLOAD ( rsqrt_
                          , (typename A0)
                          , bs::sse1_
                          , bs::fast_tag
                          , bs::pack_<bd::single_<A0>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE A0 operator() (fast_tag const&
                                    , const A0 & a0) const BOOST_NOEXCEPT
    {
      return  _mm_rsqrt_ps(a0);
    }
  };
} } }

#endif

