//==================================================================================================
/*!
    @file

    @Copyright 2016 Numscale SAS

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE4_2_SIMD_FUNCTION_IS_GEZ_HH_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE4_2_SIMD_FUNCTION_IS_GEZ_HH_INCLUDED

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/function/simd/is_greater.hpp>
#include <boost/simd/function/simd/logical_not.hpp>
#include <boost/simd/constant/zero.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;
  BOOST_DISPATCH_OVERLOAD ( is_gez_
                          , (typename A0)
                          , bs::sse4_1_
                          , bs::pack_<bd::int64_<A0>, bs::sse_>
                         )
  {

    BOOST_FORCEINLINE A0 /*as_logical_t<A0>*/result operator() ( const A0 & a0) const BOOST_NOEXCEPT
    {
      return logical_not(is_greater(Zero<A0>(), a0));
    }
  };

} } }

#endif
