//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_HMSB_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_HMSB_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/bitset.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( hmsb_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::ints8_<A0>, bs::avx_>
                          )
  {
    BOOST_FORCEINLINE bs::bitset<32> operator()(A0 const& a0) const
    {
      return _mm256_movemask_epi8(a0);
    }
  };
} } }

#endif
