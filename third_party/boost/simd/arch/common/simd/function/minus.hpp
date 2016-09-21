//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_MINUS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_MINUS_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/constant/valmax.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/function/bitwise_and.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/bitwise_xor.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/if_else_zero.hpp>
#include <boost/simd/function/is_less_equal.hpp>
#include <boost/simd/function/is_ltz.hpp>
#include <boost/simd/function/minus.hpp>
#include <boost/simd/function/plus.hpp>
#include <boost/simd/function/shr.hpp>
#include <boost/simd/function/splat.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD_IF(minus_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bs::pack_<bd::floating_<A0>, X>
                          , bs::pack_<bd::floating_<A0>, X>
                          )
   {
     BOOST_FORCEINLINE A0 operator()(const saturated_tag &,  const A0& a0, const A0& a1
                                    ) const BOOST_NOEXCEPT
     {
       return a0-a1;
     }
   };
  BOOST_DISPATCH_OVERLOAD_IF(minus_
                         , (typename A0, typename X)
                         , (detail::is_native<X>)
                         , bd::cpu_
                         , bs::saturated_tag
                         , bs::pack_<bd::uint_<A0>, X>
                         , bs::pack_<bd::uint_<A0>, X>
                         )
  {
    BOOST_FORCEINLINE A0 operator()(const saturated_tag &,  const A0& a0, const A0& a1
                                   ) const BOOST_NOEXCEPT
    {
      A0 a0ma1 = a0-a1;
      return if_else_zero(is_less_equal(a0ma1, a0), a0ma1);
    }
  };
  BOOST_DISPATCH_OVERLOAD_IF(minus_
                         , (typename A0, typename X)
                         , (detail::is_native<X>)
                         , bd::cpu_
                         , bs::saturated_tag
                         , bs::pack_<bd::int_<A0>, X>
                         , bs::pack_<bd::int_<A0>, X>
                         )
  {
    BOOST_FORCEINLINE A0 operator()(const saturated_tag &,  const A0& a0, const A0& a1
                                   ) const BOOST_NOEXCEPT
    {
      using utype = bd::as_unsigned_t<A0>;
      using stype = bd::scalar_of_t<A0>;
      utype ux = bitwise_cast<utype>(a0);
      utype uy = bitwise_cast<utype>(a1);
      utype res = ux - uy;
      ux = shr(ux, sizeof(stype)*CHAR_BIT-1) + splat<utype>(Valmax<stype>());
      return bitwise_cast<A0>(if_else(is_ltz(bitwise_cast<A0>(bitwise_and(bitwise_xor(ux,uy)
                                                                         , (bitwise_xor(ux,res))))
                                            )
                                     , ux
                                     , res)
                             );
    }
  };
} } }

#endif
