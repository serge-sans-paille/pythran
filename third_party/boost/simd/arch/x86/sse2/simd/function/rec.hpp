//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_REC_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_REC_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/raw.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;

  BOOST_DISPATCH_OVERLOAD ( rec_
                          , (typename A0)
                          , bs::sse2_
                          , bs::raw_tag
                          , bs::pack_<bd::double_<A0>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE A0 operator()(raw_tag const&, const A0 & a0) const BOOST_NOEXCEPT
    {
      return  _mm_cvtps_pd(_mm_rcp_ps(_mm_cvtpd_ps(a0))); //The maximum error for this approximation is 1.5e-12
    }
  };

} } }


#endif
