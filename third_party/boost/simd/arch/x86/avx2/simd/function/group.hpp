//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_GROUP_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_GROUP_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/constant/constant.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/shr.hpp>
#include <boost/simd/function/saturated.hpp>
#include <boost/simd/detail/dispatch/meta/downgrade.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;

  BOOST_DISPATCH_OVERLOAD ( group_
                          , (typename A0)
                          , bs::avx2_
                          , bs::saturated_tag
                          , bs::pack_<bd::ints8_<A0>, bs::avx_>
                          , bs::pack_<bd::ints8_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE bd::downgrade_t<A0>
    operator()(saturated_tag const&, const A0 & a0, const A0 & a1 ) const BOOST_NOEXCEPT
    {
      return group(a0,a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( group_
                          , (typename A0)
                          , bs::avx2_
                          , bs::saturated_tag
                          , bs::pack_<bd::int16_<A0>, bs::avx_>
                          , bs::pack_<bd::int16_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE bd::downgrade_t<A0>
    operator()(bs::saturated_tag const&, const A0 & a0, const A0 & a1 ) const BOOST_NOEXCEPT
    {
      return _mm256_permute4x64_epi64(_mm256_packs_epi16(a0, a1), 0xD8);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( group_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::uint16_<A0>, bs::avx_>
                          , bs::pack_<bd::uint16_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE bd::downgrade_t<A0>
    operator()(const A0 & a0, const A0 & a1 ) const BOOST_NOEXCEPT
    {
      return _mm256_permute4x64_epi64(_mm256_packus_epi16( (a0 & 0x7FFF) | shr(a0 & 0xF000, 1)
                                                         , (a1 & 0x7FFF) | shr(a1 & 0xF000, 1)
                                                         )
                                     , 0xD8
                                     );
    }
  };

  BOOST_DISPATCH_OVERLOAD ( group_
                          , (typename A0)
                          , bs::avx2_
                          , bs::saturated_tag
                          , bs::pack_<bd::int32_<A0>, bs::avx_>
                          , bs::pack_<bd::int32_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE bd::downgrade_t<A0>
    operator()(bs::saturated_tag const&, const A0 & a0, const A0 & a1 ) const BOOST_NOEXCEPT
    {
      return _mm256_permute4x64_epi64(_mm256_packs_epi32(a0, a1), 0xD8);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( group_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::uint32_<A0>, bs::avx_>
                          , bs::pack_<bd::uint32_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE bd::downgrade_t<A0>
    operator()(const A0 & a0, const A0 & a1 ) const BOOST_NOEXCEPT
    {
      return _mm256_permute4x64_epi64(_mm256_packus_epi32( (a0 & 0x7FFFFFFF) | shr(a0 & 0xF0000000, 1)
                                                         , (a1 & 0x7FFFFFFF) | shr(a1 & 0xF0000000, 1)
                                                         )
                                     , 0xD8
                                     );
    }
  };
} } }

#include <boost/simd/arch/x86/avx2/simd/function/groups.hpp>

#endif
