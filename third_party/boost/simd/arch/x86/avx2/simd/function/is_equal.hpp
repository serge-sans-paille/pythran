//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_IS_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_IS_EQUAL_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/meta/as_logical.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;

   BOOST_DISPATCH_OVERLOAD( is_equal_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::ints64_<A0>, bs::avx_>
                          , bs::pack_<bd::ints64_<A0>, bs::avx_>
                          )
   {
      BOOST_FORCEINLINE
      bs::as_logical_t<A0> operator()(A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
      {
        return _mm256_cmpeq_epi64(a0,a1);
      }
   };

   BOOST_DISPATCH_OVERLOAD( is_equal_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::ints32_<A0>, bs::avx_>
                          , bs::pack_<bd::ints32_<A0>, bs::avx_>
                          )
   {
      BOOST_FORCEINLINE
      bs::as_logical_t<A0> operator()(A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
      {
        return _mm256_cmpeq_epi32(a0,a1);
      }
   };

   BOOST_DISPATCH_OVERLOAD( is_equal_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::ints16_<A0>, bs::avx_>
                          , bs::pack_<bd::ints16_<A0>, bs::avx_>
                          )
   {
      BOOST_FORCEINLINE
      bs::as_logical_t<A0> operator()(A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
      {
        return _mm256_cmpeq_epi16(a0,a1);
      }
   };

   BOOST_DISPATCH_OVERLOAD( is_equal_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::ints8_<A0>, bs::avx_>
                          , bs::pack_<bd::ints8_<A0>, bs::avx_>
                          )
   {
      BOOST_FORCEINLINE
      bs::as_logical_t<A0> operator()(A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
      {
        return _mm256_cmpeq_epi8(a0,a1);
      }
   };
} } }

#endif
