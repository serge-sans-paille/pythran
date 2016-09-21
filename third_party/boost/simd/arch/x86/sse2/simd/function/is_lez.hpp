//==================================================================================================
/*!
    @file

    @Copyright 2016 Numscale SAS

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_IS_LEZ_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_IS_LEZ_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/as_logical.hpp>
#include <boost/simd/function/logical_or.hpp>
#include <boost/simd/function/is_ltz.hpp>
#include <boost/simd/function/is_eqz.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( is_lez_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::int64_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE bs::as_logical_t<A0> operator() ( const A0 & a0 ) const BOOST_NOEXCEPT
    {
      return logical_or(is_eqz(a0), is_ltz(a0));
    }
  };

} } }

#endif
