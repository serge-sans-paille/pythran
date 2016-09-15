//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_MIN_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_MIN_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD( min_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::int32_<A0>, bs::avx_>
                          , bs::pack_<bd::int32_<A0>, bs::avx_>
                          )
   {
      BOOST_FORCEINLINE A0 operator()(A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
      {
        return _mm256_min_epi32(a0,a1);
      }
   };

   BOOST_DISPATCH_OVERLOAD( min_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::int16_<A0>, bs::avx_>
                          , bs::pack_<bd::int16_<A0>, bs::avx_>
                          )
   {
      BOOST_FORCEINLINE A0 operator()(A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
      {
        return _mm256_min_epi16(a0,a1);
      }
   };

   BOOST_DISPATCH_OVERLOAD( min_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::int8_<A0>, bs::avx_>
                          , bs::pack_<bd::int8_<A0>, bs::avx_>
                          )
   {
      BOOST_FORCEINLINE A0 operator()(A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
      {
        return _mm256_min_epi8(a0,a1);
      }
   };

   BOOST_DISPATCH_OVERLOAD( min_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::uint32_<A0>, bs::avx_>
                          , bs::pack_<bd::uint32_<A0>, bs::avx_>
                          )
   {
      BOOST_FORCEINLINE A0 operator()(A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
      {
        return _mm256_min_epu32(a0,a1);
      }
   };

   BOOST_DISPATCH_OVERLOAD( min_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::uint16_<A0>, bs::avx_>
                          , bs::pack_<bd::uint16_<A0>, bs::avx_>
                          )
   {
      BOOST_FORCEINLINE A0 operator()(A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
      {
        return _mm256_min_epu16(a0,a1);
      }
   };

   BOOST_DISPATCH_OVERLOAD( min_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::uint8_<A0>, bs::avx_>
                          , bs::pack_<bd::uint8_<A0>, bs::avx_>
                          )
   {
      BOOST_FORCEINLINE A0 operator()(A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
      {
        return _mm256_min_epu8(a0,a1);
      }
   };
} } }

#endif
