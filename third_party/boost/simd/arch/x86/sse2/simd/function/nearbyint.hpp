//==================================================================================================
/*!
    Copyright 2016 Numscale SAS

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_NEARBYINT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_NEARBYINT_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/tofloat.hpp>
#include <boost/simd/function/inearbyint.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;

  BOOST_DISPATCH_OVERLOAD ( nearbyint_
                          , (typename A0)
                          , bs::sse2_
                          , bs::raw_tag
                          , bs::pack_<bd::floating_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A0 operator()(raw_tag const&, const A0 & a0) const BOOST_NOEXCEPT
    {
      return tofloat(inearbyint(a0));
    }
  };
} } }

#endif
