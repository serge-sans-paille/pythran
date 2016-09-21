//==================================================================================================
/*!
    @file

    @Copyright 2016 Numscale SAS

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_IS_NEZ_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_IS_NEZ_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/as_logical.hpp>
#include <boost/simd/detail/dispatch/meta/downgrade.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/is_ltz.hpp>
#include <boost/simd/function/is_nez.hpp>
#include <boost/simd/function/logical_or.hpp>
#include <boost/simd/function/shuffle.hpp>
#include <boost/simd/detail/dispatch/meta/downgrade.hpp>


namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;
  BOOST_DISPATCH_OVERLOAD ( is_nez_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::int64_<A0>, bs::sse_>
                         )
  {
    using result = bs::as_logical_t<A0>;
    BOOST_FORCEINLINE result operator() ( const A0 & a0 ) const BOOST_NOEXCEPT
    {
      using i32type = bd::downgrade_t<A0>;
      auto tmp1 = is_nez(boost::simd::bitwise_cast<i32type>(a0));
      auto tmp2 = shuffle<1,0,3,2>(tmp1);
      return bs::bitwise_cast<result>(logical_or(tmp1, tmp2));
    }
  };

} } }

#endif
