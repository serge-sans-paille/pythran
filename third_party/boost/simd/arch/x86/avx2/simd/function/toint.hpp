//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_TOINT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_TOINT_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;

   BOOST_DISPATCH_OVERLOAD( toint_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_< bd::double_<A0>, bs::avx_>
                          )
   {
      BOOST_FORCEINLINE bd::as_integer_t<A0>
      operator()(const A0& a0) const BOOST_NOEXCEPT
      {
        return _mm256_cvtepi32_epi64( _mm256_cvttpd_epi32(a0));
      }
   };
} } }

#endif
