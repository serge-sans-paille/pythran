//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_REC_RAW_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_REC_RAW_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/raw.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( rec_
                          , (typename A0)
                          , bs::avx_
                          , bs::raw_tag
                          , bs::pack_<bd::single_<A0>, bs::avx_>
                          )
  {
    BOOST_FORCEINLINE A0 operator()(raw_tag const&, A0 const& a0) const BOOST_NOEXCEPT
    {
      return _mm256_rcp_ps( a0 );
    }
  };
  BOOST_DISPATCH_OVERLOAD ( rec_
                          , (typename A0)
                          , bs::avx_
                          , bs::raw_tag
                          , bs::pack_<bd::double_<A0>, bs::avx_>
                          )
  {
    BOOST_FORCEINLINE A0 operator()(raw_tag const&, A0 const& a0) const BOOST_NOEXCEPT
    {
      return _mm256_cvtps_pd(_mm_rcp_ps( _mm256_cvtpd_ps(a0) ));//The error for this approximation is no more than 1.5.e-12
    }
  };

} } }

#endif
