//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_IF_ELSE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_IF_ELSE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/genmask.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;

   BOOST_DISPATCH_OVERLOAD( if_else_
                          , (typename A0, typename A1)
                          , bs::avx2_
                          , bs::pack_<bs::logical_<A0>, bs::avx_>
                          , bs::pack_<bd::integer_<A1>, bs::avx_>
                          , bs::pack_<bd::integer_<A1>, bs::avx_>
                          )
   {
      BOOST_FORCEINLINE A1 operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
      {
        return _mm256_blendv_epi8(a2, a1, bitwise_cast<A1>(genmask(a0)));
      }
   };

   BOOST_DISPATCH_OVERLOAD( if_else_
                          , (typename A0, typename A1)
                          , bs::avx2_
                          , bs::pack_<bs::logical_<A0>, bs::avx_>
                          , bs::pack_<bd::ints32_<A1>, bs::avx_>
                          , bs::pack_<bd::ints32_<A1>, bs::avx_>
                          )
   {
      BOOST_FORCEINLINE A1 operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
      {
        return _mm256_blendv_epi8(a2, a1, bitwise_cast<A1>(genmask(a0)));
      }
   };

   BOOST_DISPATCH_OVERLOAD( if_else_
                          , (typename A0, typename A1)
                          , bs::avx2_
                          , bs::pack_<bs::logical_<A0>, bs::avx_>
                          , bs::pack_<bd::ints64_<A1>, bs::avx_>
                          , bs::pack_<bd::ints64_<A1>, bs::avx_>
                          )
   {
      BOOST_FORCEINLINE A1 operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
      {
        return _mm256_blendv_epi8(a2, a1, bitwise_cast<A1>(genmask(a0)));
      }
   };
} } }

#endif
