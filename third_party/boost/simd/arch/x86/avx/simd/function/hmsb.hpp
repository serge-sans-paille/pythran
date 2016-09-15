//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_HMSB_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_HMSB_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/slice.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/detail/dispatch/meta/as_floating.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;

   BOOST_DISPATCH_OVERLOAD( hmsb_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::type32_<A0>, bs::avx_>
                          )
   {
     BOOST_FORCEINLINE std::size_t operator()(A0 const& a0) const
      {
        return _mm256_movemask_ps(bitwise_cast<bd::as_floating_t<A0>>(a0));
      }
   };

   BOOST_DISPATCH_OVERLOAD( hmsb_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::type64_<A0>, bs::avx_>
                          )
   {
     BOOST_FORCEINLINE std::size_t operator()(A0 const& a0) const
      {
        return _mm256_movemask_pd(bitwise_cast<bd::as_floating_t<A0>>(a0));
      }
   };

   BOOST_DISPATCH_OVERLOAD( hmsb_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::ints8_<A0>, bs::avx_>
                          )
   {
     BOOST_FORCEINLINE std::size_t operator()(A0 const& a0) const
      {
        auto const s = slice(a0);
        return std::uint32_t(_mm_movemask_epi8(s[0]) | (_mm_movemask_epi8(s[1]) << 16));
      }
   };

   BOOST_DISPATCH_OVERLOAD( hmsb_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::ints16_<A0>, bs::avx_>
                          )
   {
     BOOST_FORCEINLINE std::size_t operator()(A0 const& a0) const
      {
        auto const s = slice(a0);
        return hmsb(s[0]) | (hmsb(s[1]) << 8);
      }
   };
} } }

#endif
