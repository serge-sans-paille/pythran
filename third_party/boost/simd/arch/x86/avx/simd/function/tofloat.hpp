//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_TOFLOAT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_TOFLOAT_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/bitwise_notand.hpp>
#include <boost/simd/function/if_plus.hpp>
#include <boost/simd/constant/signmask.hpp>
#include <boost/simd/constant/twoto31.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/simd/detail/dispatch/meta/as_floating.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( tofloat_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::int32_<A0>, bs::avx_>
                          )
  {
    BOOST_FORCEINLINE bd::as_floating_t<A0> operator()(const A0& a0) const BOOST_NOEXCEPT
    {
      return _mm256_cvtepi32_ps(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( tofloat_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::uint32_<A0>, bs::avx_>
                          )
  {
    BOOST_FORCEINLINE bd::as_floating_t<A0> operator()(const A0& a0) const BOOST_NOEXCEPT
    {
      using si_type = bd::as_integer_t<A0, signed>;
      si_type signed_a = bitwise_cast<si_type>(a0);
      si_type fixed_a  = bitwise_notand(Signmask<si_type>(), a0);
      return if_plus(is_ltz(signed_a), tofloat(fixed_a), Twoto31<bd::as_floating_t<A0>>());
    }
  };
} } }

#endif
