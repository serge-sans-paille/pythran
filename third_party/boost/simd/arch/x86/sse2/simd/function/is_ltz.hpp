//==================================================================================================
/*!
    @file

    @Copyright 2016 Numscale SAS

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_IS_LTZ_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_IS_LTZ_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/as_logical.hpp>
#include <boost/simd/detail/dispatch/meta/downgrade.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/is_ltz.hpp>


namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;
  BOOST_DISPATCH_OVERLOAD ( is_ltz_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::int64_<A0>, bs::sse_>
                         )
  {
    using result = bs::as_logical_t<A0>;
    BOOST_FORCEINLINE result operator() ( const A0 & a0 ) const BOOST_NOEXCEPT
    {
      using i32type =  bd::downgrade_t<A0>;
      i32type that = _mm_shuffle_epi32( is_ltz(bitwise_cast<i32type>(a0))
                                      , _MM_SHUFFLE(3,3,1,1)
                                      );
      return  bitwise_cast<result>(that);
    }
  };

} } }

#endif
