//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_SPLIT_LOW_HPP_INCLUDED
#define BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_SPLIT_LOW_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/bitwise_and.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/detail/dispatch/meta/as_signed.hpp>
#include <boost/simd/detail/dispatch/meta/upgrade.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( split_low_
                          , (typename A0)
                          , bs::vmx_
                          , bs::pack_< bd::int8_<A0>, bs::vmx_>
                          )
  {
    BOOST_FORCEINLINE bd::upgrade_t<A0> operator()(const A0& a0) const
    {
      return vec_unpackh( a0.storage() );
    }
  };

  BOOST_DISPATCH_OVERLOAD ( split_low_
                          , (typename A0)
                          , bs::vmx_
                          , bs::pack_< bd::uint8_<A0>, bs::vmx_>
                          )
  {
    using result =  bd::upgrade_t<A0>;
    BOOST_FORCEINLINE result operator()(const A0& a0) const
    {
      using s_t = bd::as_signed_t<A0>;
      return  bitwise_cast<result>(vec_unpackh( bitwise_cast<s_t>(a0).storage() ))
            & result(0x00FF);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( split_low_
                          , (typename A0)
                          , bs::vmx_
                          , bs::pack_< bd::int16_<A0>, bs::vmx_>
                          )
  {
    BOOST_FORCEINLINE bd::upgrade_t<A0> operator()(const A0& a0) const
    {
      return vec_unpackh( a0.storage() );
    }
  };

  BOOST_DISPATCH_OVERLOAD ( split_low_
                      , (typename A0)
                      , bs::vmx_
                      , bs::pack_< bd::uint16_<A0>, bs::vmx_>
                      )
  {
    using result =  bd::upgrade_t<A0>;

    BOOST_FORCEINLINE result operator()(const A0& a0) const
    {
      using s_t = bd::as_signed_t<A0>;
      return  bitwise_cast<result>(vec_unpackh( bitwise_cast<s_t>(a0).storage() ))
            & result(0x0000FFFF);
    }
  };
} } }

#endif
