//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_RSQRT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_RSQRT_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/sqr.hpp>
#include <boost/simd/function/fnms.hpp>
#include <boost/simd/constant/half.hpp>
#include <boost/simd/constant/three.hpp>
#include <boost/simd/function/fast.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD( rsqrt_
                         , (typename A0)
                         , bs::avx_
                         , bs::fast_tag
                         , bs::pack_< bd::single_<A0>, bs::avx_>
                         )
   {
     BOOST_FORCEINLINE A0 operator()( const bs::fast_tag &, A0 const& a0) const
      {
        return _mm256_rsqrt_ps( a0 );
      }
   };

  BOOST_DISPATCH_OVERLOAD( rsqrt_
                         , (typename A0)
                         , bs::avx_
                         , bs::pack_< bd::single_<A0>, bs::avx_>
                         )
   {
     BOOST_FORCEINLINE A0 operator()(A0 const& a0) const
      {
        A0 const nr  = _mm256_rsqrt_ps( a0 );
        return nr * Half<A0>() * fnms(a0, sqr(nr), Three<A0>());
      }
   };
} } }

#endif
