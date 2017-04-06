//==================================================================================================
/*!
  @file

  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_BITWISE_XOR_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_BITWISE_XOR_HPP_INCLUDED

#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/traits.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/hierarchy.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;

  BOOST_DISPATCH_OVERLOAD ( bitwise_xor_
                          , (typename T)
                          ,  bd::cpu_
                          ,  bd::scalar_<bd::unspecified_<T>>
                          ,  bd::scalar_<bd::unspecified_<T>>
                          )
  {
    BOOST_FORCEINLINE auto operator()(T const& a, T const& b) const BOOST_NOEXCEPT -> decltype(a^b)
    {
      return a^b;
    }
  };

   BOOST_DISPATCH_OVERLOAD_IF( bitwise_xor_
                            , (typename A0, typename A1)
                            , (detail::same_sizeof<A0,A1>)
                            , bd::cpu_
                            , bd::scalar_<bd::fundamental_<A0>>
                            , bd::scalar_<bd::fundamental_<A1>>
                            )
  {
    BOOST_FORCEINLINE A0 operator()(A0 a0, A1 a1) const BOOST_NOEXCEPT
    {
      using b_t = bd::as_integer_t<A0, unsigned>;
      return bitwise_cast<A0>(b_t(bitwise_cast<b_t>(a0) ^ bitwise_cast<b_t>(a1)));
    }
  };
} } }

#endif

