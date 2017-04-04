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
#include <boost/simd/detail/bitset.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( hmsb_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::type32_<A0>, bs::avx_>
                          )
  {
    BOOST_FORCEINLINE bs::bitset<8> operator()(A0 const& a0) const
    {
      return _mm256_movemask_ps(bitwise_cast<bd::as_floating_t<A0>>(a0));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( hmsb_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::type64_<A0>, bs::avx_>
                          )
  {
    BOOST_FORCEINLINE bs::bitset<4> operator()(A0 const& a0) const
    {
      return _mm256_movemask_pd(bitwise_cast<bd::as_floating_t<A0>>(a0));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( hmsb_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::ints8_<A0>, bs::avx_>
                          )
  {
    BOOST_FORCEINLINE bs::bitset<32> operator()(A0 const& a0) const
    {
      auto h = _mm_movemask_epi8(slice_high(a0));
      auto l = _mm_movemask_epi8(slice_low (a0));
      return l | (h << 16);
    }
  };

  BOOST_DISPATCH_OVERLOAD( hmsb_
                      , (typename A0)
                      , bs::avx_
                      , bs::pack_<bd::ints16_<A0>, bs::avx_>
                      )
  {
    BOOST_FORCEINLINE bs::bitset<16> operator()(A0 const& a0) const
    {
      using s8type = typename A0::template retype<int8_t, 16>;
      s8type mask = {1,3,5,7,9,11,13,15,-128,-128,-128,-128,-128,-128,-128,-128};

      auto l = _mm_movemask_epi8(_mm_shuffle_epi8(bitwise_cast<s8type>(slice_low(a0)), mask));
      auto h = _mm_movemask_epi8(_mm_shuffle_epi8(bitwise_cast<s8type>(slice_high(a0)), mask));

      return l | (h << 8);
    }
  };
} } }

#endif
