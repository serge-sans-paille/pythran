//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_IS_LESS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_IS_LESS_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/meta/as_logical.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;

   BOOST_DISPATCH_OVERLOAD( is_less_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::double_<A0>, bs::avx_>
                          , bs::pack_<bd::double_<A0>, bs::avx_>
                          )
   {
      using result =  bs::as_logical_t<A0>;
      BOOST_FORCEINLINE result operator()( const A0& a0, const A0& a1) const BOOST_NOEXCEPT
      {
        return _mm256_cmp_pd(a0,a1, _CMP_LT_OQ);
      }
   };

   BOOST_DISPATCH_OVERLOAD( is_less_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::single_<A0>, bs::avx_>
                          , bs::pack_<bd::single_<A0>, bs::avx_>
                          )
   {
      using result =  bs::as_logical_t<A0>;
      BOOST_FORCEINLINE result operator()( const A0& a0, const A0& a1) const BOOST_NOEXCEPT
      {
        return _mm256_cmp_ps(a0,a1, _CMP_LT_OQ);
      }
   };

   BOOST_DISPATCH_OVERLOAD( is_less_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::double_<A0>, bs::sse_>
                          , bs::pack_<bd::double_<A0>, bs::sse_>
                          )
   {
      using result =  bs::as_logical_t<A0>;
      BOOST_FORCEINLINE result operator()( const A0& a0, const A0& a1) const BOOST_NOEXCEPT
      {
        return _mm_cmp_pd(a0,a1, _CMP_LT_OQ);
      }
   };

   BOOST_DISPATCH_OVERLOAD( is_less_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::single_<A0>, bs::sse_>
                          , bs::pack_<bd::single_<A0>, bs::sse_>
                          )
   {
      using result =  bs::as_logical_t<A0>;
      BOOST_FORCEINLINE result operator()( const A0& a0, const A0& a1) const BOOST_NOEXCEPT
      {
        return _mm_cmp_ps(a0,a1, _CMP_LT_OQ);
      }
   };
} } }

#endif
