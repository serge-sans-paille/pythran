//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_IS_GREATER_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_IS_GREATER_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/meta/as_logical.hpp>
#include <boost/simd/constant/signmask.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/minus.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;

   BOOST_DISPATCH_OVERLOAD( is_greater_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::unsigned_<A0>, bs::avx_>
                          , bs::pack_<bd::unsigned_<A0>, bs::avx_>
                          )
   {
      using result = bs::as_logical_t<A0>;
      BOOST_FORCEINLINE result operator()( const A0& a0, const A0& a1) const BOOST_NOEXCEPT
      {
        using stype =  bd::as_integer_t<A0, signed>;
        auto const m = Signmask<stype>();
        return bitwise_cast<result>((bitwise_cast<stype>(a0) - m) > (bitwise_cast<stype>(a1) - m));
      }
   };

   BOOST_DISPATCH_OVERLOAD( is_greater_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_< bd::int64_<A0>, bs::avx_>
                          , bs::pack_< bd::int64_<A0>, bs::avx_>
                          )
   {
      BOOST_FORCEINLINE bs::as_logical_t<A0>
      operator()(A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
      {
        return _mm256_cmpgt_epi64(a0,a1);
      }
   };

   BOOST_DISPATCH_OVERLOAD( is_greater_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_< bd::int32_<A0>, bs::avx_>
                          , bs::pack_< bd::int32_<A0>, bs::avx_>
                          )
   {
      BOOST_FORCEINLINE bs::as_logical_t<A0>
      operator()(A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
      {
        return _mm256_cmpgt_epi32(a0,a1);
      }
   };

   BOOST_DISPATCH_OVERLOAD( is_greater_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_< bd::int16_<A0>, bs::avx_>
                          , bs::pack_< bd::int16_<A0>, bs::avx_>
                          )
   {
      BOOST_FORCEINLINE bs::as_logical_t<A0>
      operator()(A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
      {
        return _mm256_cmpgt_epi16(a0,a1);
      }
   };

   BOOST_DISPATCH_OVERLOAD( is_greater_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_< bd::int8_<A0>, bs::avx_>
                          , bs::pack_< bd::int8_<A0>, bs::avx_>
                          )
   {
      BOOST_FORCEINLINE bs::as_logical_t<A0>
      operator()(A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
      {
        return _mm256_cmpgt_epi8(a0,a1);
      }
   };
} } }

#endif
