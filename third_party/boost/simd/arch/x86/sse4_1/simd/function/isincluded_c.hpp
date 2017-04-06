//==================================================================================================
/*!
    @file

    @Copyright 2016 Numscale SAS

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE4_1_SIMD_FUNCTION_ISINCLUDED_C_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE4_1_SIMD_FUNCTION_ISINCLUDED_C_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/as_logical.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>


namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;
  BOOST_DISPATCH_OVERLOAD ( isincluded_c_
                          , (typename A0)
                          , bs::sse4_1_
                          , bs::pack_<bd::integer_<A0>, bs::sse_>
                          , bs::pack_<bd::integer_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE bool operator() ( const A0 & a0
                                      , const A0 & a1 ) const BOOST_NOEXCEPT
    {
      return _mm_testz_si128(a1, a0);
    }
  };
  BOOST_DISPATCH_OVERLOAD ( isincluded_c_
                          , (typename A0)
                          , bs::sse4_1_
                          , bs::pack_<bd::floating_<A0>, bs::sse_>
                          , bs::pack_<bd::floating_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE bool operator() ( const A0 & a0
                                      , const A0 & a1 ) const BOOST_NOEXCEPT
    {
      using i_t = bd::as_integer_t<A0>;
      return isincluded_c(bitwise_cast<i_t>(a0), bitwise_cast<i_t>(a1));
    }
  };

} } }

#endif
