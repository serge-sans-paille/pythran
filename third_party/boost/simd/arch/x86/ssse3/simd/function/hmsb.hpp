//==================================================================================================
/*!
    @file

    @Copyright 2016 Numscale SAS

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSSE3_SIMD_FUNCTION_HMSB_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSSE3_SIMD_FUNCTION_HMSB_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/bitwise_cast.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bs =  boost::simd;
  namespace bd =  boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( hmsb_
                          , (typename A0)
                          , bs::ssse3_
                          , bs::pack_<bd::ints16_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE std::size_t operator() ( const A0 & a0) const BOOST_NOEXCEPT
    {
      using s8type = bs::pack<int8_t, 16>;
      s8type mask = {0x01,0x03,0x05,0x07,0x09,0x0B,0x0D,0x0F
                                       ,-128,-128,-128,-128,-128,-128,-128,-128
                                       };
      return _mm_movemask_epi8( _mm_shuffle_epi8(bitwise_cast<s8type>(a0), mask));
    }
  };

} } }

#endif
