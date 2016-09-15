//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_SHIFT_RIGHT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_SHIFT_RIGHT_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;

   BOOST_DISPATCH_OVERLOAD( shift_right_
                          , (typename A0, typename A1)
                          , bs::avx2_
                          , bs::pack_<bd::uint16_<A0>, bs::avx_>
                          , bd::scalar_<bd::integer_<A1>>
                          )
   {
      BOOST_FORCEINLINE A0 operator()(A0 const& a0, A1 a1) const BOOST_NOEXCEPT
      {
        return _mm256_srli_epi16(a0, int(a1));
      }
   };

   BOOST_DISPATCH_OVERLOAD( shift_right_
                          , (typename A0, typename A1)
                          , bs::avx2_
                          , bs::pack_<bd::int16_<A0>, bs::avx_>
                          , bd::scalar_< bd::integer_<A1>>
                          )
   {
      BOOST_FORCEINLINE A0 operator()(A0 const& a0, A1 a1) const BOOST_NOEXCEPT
      {
        return _mm256_srai_epi16(a0, int(a1));
      }
   };

   BOOST_DISPATCH_OVERLOAD( shift_right_
                          , (typename A0, typename A1)
                          , bs::avx2_
                          , bs::pack_<bd::uint32_<A0>, bs::avx_>
                          , bd::scalar_<bd::integer_<A1>>
                          )
   {
      BOOST_FORCEINLINE A0 operator()(A0 const& a0, A1 a1) const BOOST_NOEXCEPT
      {
        return _mm256_srli_epi32(a0, int(a1));
      }
   };

   BOOST_DISPATCH_OVERLOAD( shift_right_
                          , (typename A0, typename A1)
                          , bs::avx2_
                          , bs::pack_<bd::int32_<A0>, bs::avx_>
                          , bd::scalar_<bd::integer_<A1>>
                          )
   {
      BOOST_FORCEINLINE A0 operator()(A0 const& a0, A1 a1) const BOOST_NOEXCEPT
      {
        return _mm256_srai_epi32(a0, int(a1));
      }
   };

   BOOST_DISPATCH_OVERLOAD( shift_right_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::uint32_<A0>, bs::avx_>
                          , bs::pack_<bd::ints32_<A0>, bs::avx_>
                          )
   {
      BOOST_FORCEINLINE A0 operator()(A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
      {
        return _mm256_srlv_epi32(a0, a1);
      }
   };

   BOOST_DISPATCH_OVERLOAD( shift_right_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::int32_<A0>, bs::avx_>
                          , bs::pack_<bd::ints32_<A0>, bs::avx_>
                          )
   {
     BOOST_FORCEINLINE A0 operator()(A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
      {
        return _mm256_srav_epi32(a0, a1);
      }
   };

   BOOST_DISPATCH_OVERLOAD( shift_right_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::uint32_<A0>, bs::sse_>
                          , bs::pack_<bd::ints32_<A0>, bs::sse_>
                          )
   {
      BOOST_FORCEINLINE A0 operator()(A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
      {
        return _mm_srlv_epi32(a0, a1);
      }
   };

   BOOST_DISPATCH_OVERLOAD( shift_right_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::int32_<A0>, bs::sse_>
                          , bs::pack_<bd::ints32_<A0>, bs::sse_>
                          )
   {
      BOOST_FORCEINLINE A0 operator()(A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
      {
        return _mm_srav_epi32(a0, a1);
      }
   };

   BOOST_DISPATCH_OVERLOAD( shift_right_
                          , (typename A0, typename A1)
                          , bs::avx2_
                          , bs::pack_<bd::uint64_<A0>, bs::avx_>
                          , bd::scalar_<bd::integer_<A1>>
                          )
   {
     BOOST_FORCEINLINE A0 operator()(A0 const& a0, A1 a1) const BOOST_NOEXCEPT
      {
        return _mm256_srli_epi64(a0, int(a1));
      }
   };

   BOOST_DISPATCH_OVERLOAD( shift_right_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::uint64_<A0>, bs::avx_>
                          , bs::pack_<bd::ints64_<A0>, bs::avx_>
                          )
   {
      BOOST_FORCEINLINE A0 operator()(A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
      {
        return _mm256_srlv_epi64(a0, a1);
      }
   };

   BOOST_DISPATCH_OVERLOAD( shift_right_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::uint64_<A0>, bs::sse_>
                          , bs::pack_<bd::ints64_<A0>, bs::sse_>
                          )
   {
      BOOST_FORCEINLINE A0 operator()(A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
      {
        return _mm_srlv_epi64(a0, a1);
      }
   };
} } }

#endif
