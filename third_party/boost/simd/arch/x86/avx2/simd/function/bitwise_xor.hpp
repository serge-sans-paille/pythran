//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_BITWISE_XOR_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_BITWISE_XOR_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;

   BOOST_DISPATCH_OVERLOAD( bitwise_xor_
                          , (typename A0, typename A1)
                          , bs::avx2_
                          , bs::pack_< bd::integer_<A0>, bs::avx_>
                          , bs::pack_< bd::integer_<A1>, bs::avx_>
                          )
   {
      BOOST_FORCEINLINE A0 operator()(A0 const& a0, A1 const& a1) const BOOST_NOEXCEPT
      {
        return _mm256_xor_si256(a0, a1);
      }
   };
} } }

#endif
