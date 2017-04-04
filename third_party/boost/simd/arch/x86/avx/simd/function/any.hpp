//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_ANY_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_ANY_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/constant/allbits.hpp>
#include <boost/simd/detail/constant/butsign.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;

  BOOST_DISPATCH_OVERLOAD ( any_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::integer_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE bool operator() ( const A0 & a0) const BOOST_NOEXCEPT
    {
      return _mm256_testnzc_si256(a0, Allbits<A0>());
    }
  };

  BOOST_DISPATCH_OVERLOAD ( any_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::floating_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE bool operator() ( const A0 & a0) const BOOST_NOEXCEPT
    {
      using iA0 = bd::as_integer_t<A0>;
      return _mm256_testnzc_si256(bitwise_cast<iA0>(a0), Butsign<iA0>());
    }
  };

} } }

#endif
