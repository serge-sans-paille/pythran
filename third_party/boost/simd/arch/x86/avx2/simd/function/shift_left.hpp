//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_SHIFT_LEFT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_SHIFT_LEFT_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;

   BOOST_DISPATCH_OVERLOAD( shift_left_
                          , (typename A0, typename A1)
                          , bs::avx2_
                          , bs::pack_<bd::ints16_<A0>, bs::avx_>
                          , bd::scalar_<bd::integer_<A1>>
                          )
   {
      BOOST_FORCEINLINE A0 operator()(A0 const& a0, A1 a1) const BOOST_NOEXCEPT
      {
        return _mm256_slli_epi16(a0, int(a1));
      }
   };

   BOOST_DISPATCH_OVERLOAD( shift_left_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::ints32_<A0>, bs::avx_>
                          , bs::pack_<bd::ints32_<A0>, bs::avx_>
                          )
   {
      BOOST_FORCEINLINE A0 operator()(A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
      {
        return _mm256_sllv_epi32(a0, a1);
      }
   };

   BOOST_DISPATCH_OVERLOAD( shift_left_
                          , (typename A0, typename A1)
                          , bs::avx2_
                          , bs::pack_<bd::ints32_<A0>, bs::avx_>
                          , bd::scalar_<bd::integer_<A1>>
                          )
   {
      BOOST_FORCEINLINE A0 operator()(A0 const& a0, A1 a1) const BOOST_NOEXCEPT
      {
        return _mm256_slli_epi32(a0, int(a1));
      }
   };

   BOOST_DISPATCH_OVERLOAD( shift_left_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::ints32_<A0>, bs::sse_>
                          , bs::pack_<bd::ints32_<A0>, bs::sse_>
                          )
   {
      BOOST_FORCEINLINE A0 operator()(A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
      {
        return _mm_sllv_epi32(a0, a1);
      }
   };

   BOOST_DISPATCH_OVERLOAD( shift_left_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::ints64_<A0>, bs::avx_>
                          , bs::pack_<bd::ints64_<A0>, bs::avx_>
                          )
   {
      BOOST_FORCEINLINE A0 operator()(A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
      {
        return _mm256_sllv_epi64(a0, a1);
      }
   };

   BOOST_DISPATCH_OVERLOAD( shift_left_
                          , (typename A0, typename A1)
                          , bs::avx2_
                          , bs::pack_<bd::ints64_<A0>, bs::avx_>
                          , bd::scalar_<bd::integer_<A1>>
                          )
   {
      BOOST_FORCEINLINE A0 operator()(A0 const& a0, A1 a1) const BOOST_NOEXCEPT
      {
        return _mm256_slli_epi64(a0, int(a1));
      }
   };

   BOOST_DISPATCH_OVERLOAD( shift_left_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::ints64_<A0>, bs::sse_>
                          , bs::pack_<bd::ints64_<A0>, bs::sse_>
                          )
   {
     BOOST_FORCEINLINE A0 operator()(A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
      {
        return _mm_sllv_epi64(a0, a1);
      }
   };
} } }

#endif
