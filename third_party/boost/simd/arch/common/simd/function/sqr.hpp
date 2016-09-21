//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SQR_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SQR_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/constant/sqrtvalmax.hpp>
#include <boost/simd/constant/valmax.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/is_greater.hpp>
#include <boost/simd/function/sqr.hpp>

#ifdef USE_UBSAN
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/detail/dispatch/meta/as_unsigned.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF ( sqr_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_< bd::arithmetic_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 const& a0) const BOOST_NOEXCEPT
    {
      return bs::multiplies(a0, a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF(sqr_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::saturated_tag
                            , bs::pack_<bd::int_<A0>, X>
                            )
  {
    BOOST_FORCEINLINE A0 operator()(const saturated_tag &,  const A0& a0
                                   ) const BOOST_NOEXCEPT
    {
      // workaround for UBSan
#ifdef USE_UBSAN
      using utype = bs::as_unsigned_t<A0>;
      return if_else(is_greater(saturated_(abs)(a0), bs::Sqrtvalmax<A0>()),
                     bs::Valmax<A0>(), bitwise_cast<A0>(sqr(bitwise_cast<utype>(a0))));
#else
      return if_else(is_greater(saturated_(abs)(a0), bs::Sqrtvalmax<A0>()),
                     bs::Valmax<A0>(), sqr(a0));
#endif
    }
  };
  BOOST_DISPATCH_OVERLOAD_IF(sqr_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::saturated_tag
                            , bs::pack_<bd::uint_<A0>, X>
                            )
  {
    BOOST_FORCEINLINE A0 operator()(const saturated_tag &,  const A0& a0
                                   ) const BOOST_NOEXCEPT
    {
      return if_else(is_greater(a0, bs::Sqrtvalmax<A0>()),
                     bs::Valmax<A0>(), sqr(a0));
    }
  };
  BOOST_DISPATCH_OVERLOAD_IF(sqr_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::saturated_tag
                            , bs::pack_<bd::floating_<A0>, X>
                            )
  {
    BOOST_FORCEINLINE A0 operator()(const saturated_tag &,  const A0& a0
                                   ) const BOOST_NOEXCEPT
    {
      return sqr(a0);
    }
  };

} } }

#endif

