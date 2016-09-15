//==================================================================================================
/*!
    @file

    @Copyright 2016 Numscale SAS

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_AVERAGE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_AVERAGE_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( average_
                          , (typename A0, typename A1)
                          , bs::avx2_
                          , bs::pack_<bd::uint8_<A0>, bs::avx_>
                          , bs::pack_<bd::uint8_<A1>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE A0 operator()( const A0 & a0, const A1 & a1 ) const BOOST_NOEXCEPT
    {
      return _mm256_avg_epu8(a0, a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( average_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::uint16_<A0>, bs::avx_>
                          , bs::pack_<bd::uint16_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE A0 operator()( const A0 & a0, const A0 & a1 ) const BOOST_NOEXCEPT
    {
      return _mm256_avg_epu16(a0, a1);
    }
  };
} } }

#endif
