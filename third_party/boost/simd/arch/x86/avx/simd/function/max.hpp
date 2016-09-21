//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_MAX_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_MAX_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/is_unord.hpp>
#include <boost/predef/compiler.h>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD( max_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::double_<A0>, bs::avx_>
                          , bs::pack_<bd::double_<A0>, bs::avx_>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0, const A0& a1) const BOOST_NOEXCEPT
      {
        return _mm256_max_pd(a1,a0);
      }
   };

   BOOST_DISPATCH_OVERLOAD( max_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::single_<A0>, bs::avx_>
                          , bs::pack_<bd::single_<A0>, bs::avx_>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0, const A0& a1) const BOOST_NOEXCEPT
      {
        return _mm256_max_ps(a1,a0);
      }
   };
} } }

#endif
